/*
   *1.本程序适用微雪4.2寸三色屏,如果是其它品牌的三色屏，修改对应的三色屏display对象及对应接线方式即可。
   *2.通用驱动板接线：
     *busy---4
     *res---rx2
     *dc---tx2
     *cs---5
     *clk---18
     *din---23
     *gnd---gnd
     *vcc---3.3v
    *Version:2.0
    *Author：夏襄居士
    *UploadTime：2022年1月24日15:47
    *已知bug
    * 1.轻度休眠重启后有概率导致联网失败，可采取delay方式延迟，但相应的，功耗会增加
    * 2.强制门户认证有概率无法正常进入，可能跟手机有关
    * 3.知乎热榜有概率显示过线，这个与接口返回的json数据有关，后期将更新接口以修复
*/
#include <U8g2_for_Adafruit_GFX.h>
#include <GxEPD2_3C.h>
#include <ArduinoJson.h>
#include <Timezone.h>
GxEPD2_3C<GxEPD2_420c, GxEPD2_420c::HEIGHT> display(GxEPD2_420c(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW042Z15
#include "gb2312.c"
#include "imagedata.h"
#include "Webserver.h"
#include "NTP.h"
#include <dht11.h>
extern const uint8_t chinese_city_gb2312[239032] U8G2_FONT_SECTION("chinese_city_gb2312");
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
//****** HTTP服务器配置 ******
String language = "zh-Hans"; // 请求语言
String url_yiyan = "https://v1.hitokoto.cn/";//一言获取地址
String url_ActualWeather;   //实况天气地址
String url_FutureWeather;   //未来天气地址
//****** 天气数据
//我们要从此网页中提取的数据的类型
struct ActualWeather
{
  char status_code[64];  //错误代码
  char city[16];         //城市名称
  char weather_name[16]; //天气现象名称
  char weather_code[4];  //天气现象代码
  char temp[5];          //温度
  char last_update[25];  //最后更新时间
};
ActualWeather actual;  //创建结构体变量 目前的

struct FutureWeather
{
  char status_code[64];       //错误代码

  char date0[14];             //今天日期
  char date0_text_day[20];    //白天天气现象名称
  char date0_code_day[4];     //白天天气现象代码
  char date0_text_night[16];  //晚上天气现象名称
  char date0_code_night[4];   //晚上天气现象代码
  char date0_high[5];         //最高温度
  char date0_low[5];          //最低温度
  char date0_humidity[5];     //相对湿度
  char date0_wind_scale[5];   //风力等级

  char date1[14];             //明天日期
  char date1_text_day[20];    //白天天气现象名称
  char date1_code_day[4];     //白天天气现象代码
  char date1_text_night[16];  //晚上天气现象名称
  char date1_code_night[4];   //晚上天气现象代码
  char date1_high[5];         //最高温度
  char date1_low[5];          //最低温度
  //char date1_humidity[5];     //相对湿度

  char date2[14];             //后天日期
  char date2_text_day[20];    //白天天气现象名称
  char date2_code_day[4];     //白天天气现象代码
  char date2_text_night[16];  //晚上天气现象名称
  char date2_code_night[4];   //晚上天气现象代码
  char date2_high[5];         //最高温度
  char date2_low[5];          //最低温度
  //char date2_humidity[5];     //相对湿度
};
FutureWeather future; //创建结构体变量 未来
struct LifeIndex //生活指数
{
  char status_code[64];  //错误代码
  char uvi[10];          //紫外线指数
}; LifeIndex life_index; //创建结构体变量 未来
struct News  //新闻API
{
  char status_code[64]; //错误代码
  char title[11][64];
};
struct Hitokoto  //一言API
{
  char status_code[64]; //错误代码
  char hitokoto[64];
};
//****** 一些变量 ******
String webServer_news = " ";
uint8_t client_count = 0;  //连接服务器的超时计数,暂未使用
uint8_t client_error = 0;  //错误代码,暂未使用
boolean night_updated = 1; //夜间更新 1-不更新 0-更新
//RTC临时数据
#define RTC_hour_dz 0           //小时地址
#define RTC_night_count_dz 1    //夜间计数地址
#define RTC_peiwang_state_dz 2  //配网状态地址
uint32_t RTC_hour = 100;        //小时
uint32_t RTC_night_count = 0;   //24-6点，夜间不更新计数
int32_t night_count_max = 0;    //需要跳过几次
uint32_t RTC_peiwang_state = 0; //配网状态 1-需要
//int daydate;//当天日期
Hitokoto yiyan; //创建结构体变量 一言
News xinwen; //创建结构体变量 新闻
int udc=0;//更新次数记录

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(4096);
  display.init();
  u8g2Fonts.begin(display);//将u8g2连接到display
  display.firstPage();
  display.display(1); 
  wifi_init();
}

void loop() {
  /*后台配置*/
  if (settingMode) {
    dnsServer.processNextRequest();
  }
  webServer.handleClient();
  if (!settingMode) {
    GetData();
    initNTP();
    display.fillScreen(GxEPD_WHITE);
    get_weather();
    updatetime();
    hitokoto();
    newsdisplay();
    gettem();
    udc++;
    display.nextPage();
    /* 1.轻度休眠会关闭WiFi蓝牙以降低功耗，所以唤醒后需要重新联网
     * 2.之所以不用功耗更低的深度休眠，因为深度休眠只保留RTC，内存
     *   中的数据会丢失
     * 3.休眠函数中时间单位是微秒，所以数据要X1000000
    */
    /*esp_sleep_enable_timer_wakeup(300000000);//5分钟刷新一次
    esp_light_sleep_start();
    delay(1000);
    wifi_init();//休眠后需要重新联网*/
    delay(300000);//5分钟更新一次
  }
      /*深度睡眠会导致内存中数据丢失让新闻切换出问题，故弃用
       * esp_sleep_enable_timer_wakeup(20000000);
      esp_deep_sleep_start();
      */
  };
