/*天气信息*/
void get_weather(void){
    String tubiao = actual.weather_name;
    Serial.println(tubiao);
    if(tubiao=="多云"||tubiao=="晴间多云"||tubiao=="大部多云"){
      display.drawInvertedBitmap(280, 15, duoyun, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="晴"){
      display.drawInvertedBitmap(280, 15, qing, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="阴"){
      display.drawInvertedBitmap(280, 15, yin, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="阵雨"){
      display.drawInvertedBitmap(280, 15, zhenyu, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="雷阵雨"){
      display.drawInvertedBitmap(280, 15, leizhenyu, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="雷阵雨伴有冰雹"){
      display.drawInvertedBitmap(280, 15, leizhenyubanyoubingbao, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="小雨"){
      display.drawInvertedBitmap(280, 15, xiaoyu, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="中雨"){
      display.drawInvertedBitmap(280, 15, zhongyu, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="大雨"){
      display.drawInvertedBitmap(280, 15, dayu, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="暴雨"||tubiao=="大暴雨"||tubiao=="特大暴雨"){
      display.drawInvertedBitmap(280, 15, baoyu, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="冻雨"){
      display.drawInvertedBitmap(280, 15, dongyu, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="雨夹雪"){
      display.drawInvertedBitmap(280, 15, yujiaxue, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="阵雪"){
      display.drawInvertedBitmap(280, 15, zhenxue, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="小雪"){
      display.drawInvertedBitmap(280, 15, xiaoxue, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="中雪"){
      display.drawInvertedBitmap(280, 15, zhongxue, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="大雪"){
      display.drawInvertedBitmap(280, 15, daxue, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="暴雪"){
      display.drawInvertedBitmap(280, 15, baoxue, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="浮尘"){
      display.drawInvertedBitmap(280, 15, fuchen, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="扬沙"||tubiao=="沙尘暴"||tubiao=="强沙尘暴"){
      display.drawInvertedBitmap(280, 15, shachenbao, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="雾"){
      display.drawInvertedBitmap(280, 15, dawu, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="霾"){
      display.drawInvertedBitmap(280, 15, mai, 128, 128, GxEPD_BLACK);//画图
    }else if(tubiao=="未知"){
      display.drawInvertedBitmap(280, 15, weizhi, 128, 128, GxEPD_BLACK);//画图
    }
    
    /*位置+温度*/
  display.drawInvertedBitmap(280, 128, weizhi, 32, 28, GxEPD_RED);//画图
  u8g2Fonts.setCursor(312, 150);
  u8g2Fonts.setFont(chinese_city_gb2312);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // 设置前景色
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // 设置背景色
  u8g2Fonts.print(String(actual.city));
//  u8g2Fonts.setCursor(283,222);
    u8g2Fonts.setCursor(272,242);
    u8g2Fonts.print("今天");
    u8g2Fonts.setCursor(272,262);
    u8g2Fonts.print("明天");
    u8g2Fonts.setCursor(272,282);
    u8g2Fonts.print("后天");
    String text_day0, text_night0, dn0_s;
    String text_day1, text_night1, dn1_s;
    String text_day2, text_night2, dn2_s;
    const char* dn0; const char* dn1; const char* dn2;

    if (strcmp(future.date0_text_day, future.date0_text_night) != 0) //今天
    {
      text_day0 = future.date0_text_day;
      text_night0 = future.date0_text_night;
      dn0_s = text_day0 + "转" + text_night0;
      dn0 = dn0_s.c_str();
      u8g2Fonts.setCursor(300, 242);
      u8g2Fonts.print(dn0);
    }
    else
    {
      dn0 = future.date0_text_night;
      u8g2Fonts.setCursor(300, 242);
      u8g2Fonts.print(dn0);
    }

    if (strcmp(future.date1_text_day, future.date1_text_night) != 0) //明天
    {
      text_day1 = future.date1_text_day;
      text_night1 = future.date1_text_night;
      dn1_s = text_day1 + "转" + text_night1;
      dn1 = dn1_s.c_str();
      u8g2Fonts.setCursor(300, 262);
      u8g2Fonts.print(dn1);
    }
    else
    {
      dn1 = future.date1_text_night;
      u8g2Fonts.setCursor(300, 262);
      u8g2Fonts.print(dn1);
    }

    if (strcmp(future.date2_text_day, future.date2_text_night) != 0) //后天
    {
      text_day2 = future.date2_text_day;
      text_night2 = future.date2_text_night;
      dn2_s = text_day2 + "转" + text_night2;
      dn2 = dn2_s.c_str();
      u8g2Fonts.setCursor(300, 282);
      u8g2Fonts.print(dn2);
    }
    else
    {
      dn2 = future.date2_text_night;
      u8g2Fonts.setCursor(300, 282);
      u8g2Fonts.print(dn2);
    }
  //显示高低温
    String  high0, high1, high2, low0, low1, low2, hl0_s, hl1_s, hl2_s;
    high0 = future.date0_high; high1 = future.date1_high; high2 = future.date2_high;
    low0 = future.date0_low; low1 = future.date1_low; low2 = future.date2_low;
    hl0_s = high0 + "/" + low0;
    hl1_s = high1 + "/" + low1;
    hl2_s = high2 + "/" + low2;
    const char* hl0 = hl0_s.c_str();
    const char* hl1 = hl1_s.c_str();
    const char* hl2 = hl2_s.c_str();
    u8g2Fonts.setCursor(373,242);
    u8g2Fonts.print(hl0);
    u8g2Fonts.setCursor(373,262);
    u8g2Fonts.print(hl1);
    u8g2Fonts.setCursor(373,282);
    u8g2Fonts.print(hl2);
  
}
#define STD_TIMEZONE_OFFSET +8 
/*get time*/

/*时间日期数字格式化*/
  String pressNum(int num) {
    if (num < 10 )
      return "0" + String(num);
    else
      return String(num);
  }
void updatetime() {
  String timedate,timetim="";
  int weekdays, days, months,years,minutes,hours; 
  TimeChangeRule *tcr;        // Pointer to the time change rule
  time_t utc = now();
  TimeChangeRule mySTD = {"", First,  Sun, Jan, 0, STD_TIMEZONE_OFFSET * 60};
  Timezone myTZ(mySTD, mySTD);
  time_t localTime = myTZ.toLocal(utc, &tcr);
  weekdays = weekday(localTime);
  Serial.print("周");
  Serial.println(weekdays);
//  if(weekdays!=7){
//    weekdays-=1;
//  }else{
//    weekdays=1;
//  }
  days = day(localTime);
  months = month(localTime);
  years = year(localTime);
  timedate+=String(pressNum(months)) ;
  timedate+= "月" ;
  
//  if(weekdays==0) weekdays=7;
  minutes =   minute(localTime);
  hours   =   hour(localTime) ;   //12 hour format use : hourFormat12(localTime)  isPM()/isAM()
  timetim="星期";
  if(weekdays==2)timetim+="一"; 
  else if(weekdays==3)timetim+="二"; 
  else if(weekdays==4)timetim+="三"; 
  else if(weekdays==5)timetim+="四"; 
  else if(weekdays==6)timetim+="五"; 
  else if(weekdays==7)timetim+="六"; 
  else if(weekdays==1)timetim+="天"; 
  timetim+=" ";
  timetim+=String(hours);
  timetim+=" 点 ";
  if(minutes<10){
    timetim+="0";
   }
  timetim+=String(minutes);
  Serial.print(String(years)+"-"+String(months)+"-"+String(days)+"-");
  Serial.println(timetim);
  
  if(days<10){
    display.drawInvertedBitmap(301, 144, ling, 48, 66, GxEPD_RED);//画图
    if(days==1){
      display.drawInvertedBitmap(349, 144, yi, 18, 66, GxEPD_RED);//画图
    }else if(days==2){
      display.drawInvertedBitmap(349, 144, er, 48, 66, GxEPD_RED);//画图
    }else if(days==3){
      display.drawInvertedBitmap(349, 144, san, 48, 66, GxEPD_RED);//画图
    }else if(days==4){
      display.drawInvertedBitmap(349, 144, si, 48, 66, GxEPD_RED);//画图
    }else if(days==5){
      display.drawInvertedBitmap(349, 144, wu, 48, 66, GxEPD_RED);//画图
    }else if(days==6){
      display.drawInvertedBitmap(349, 144, liu, 48, 66, GxEPD_RED);//画图
    }else if(days==7){
      display.drawInvertedBitmap(349, 144, qi, 48, 66, GxEPD_RED);//画图
    }else if(days==8){
      display.drawInvertedBitmap(349, 144, ba, 48, 66, GxEPD_RED);//画图
    }else if(days==9){
      display.drawInvertedBitmap(349, 144, jiu, 48, 66, GxEPD_RED);//画图
    }
    
  }else if(days>=10&&days<20){
      display.drawInvertedBitmap(301, 144, yi, 18, 66, GxEPD_RED);//画图
    if(days==10){
      display.drawInvertedBitmap(349, 144, ling, 48, 66, GxEPD_RED);//画图
    }else if(days==11){
      display.drawInvertedBitmap(349, 144, yi, 18, 66, GxEPD_RED);//画图
    }else if(days==12){
      display.drawInvertedBitmap(349, 144, er, 48, 66, GxEPD_RED);//画图
    }else if(days==13){
      display.drawInvertedBitmap(349, 144, san, 48, 66, GxEPD_RED);//画图
    }else if(days==14){
      display.drawInvertedBitmap(349, 144, si, 48, 66, GxEPD_RED);//画图
    }else if(days==15){
      display.drawInvertedBitmap(349, 144, wu, 48, 66, GxEPD_RED);//画图
    }else if(days==16){
      display.drawInvertedBitmap(349, 144, liu, 48, 66, GxEPD_RED);//画图
    }else if(days==17){
      display.drawInvertedBitmap(349, 144, qi, 48, 66, GxEPD_RED);//画图
    }else if(days==18){
      display.drawInvertedBitmap(349, 144, ba, 48, 66, GxEPD_RED);//画图
    }else if(days==19){
      display.drawInvertedBitmap(349, 144, jiu, 48, 66, GxEPD_RED);//画图
    }
  }else if(days>=20&&days<30){
    display.drawInvertedBitmap(301, 144, er, 48, 66, GxEPD_RED);//画图
    if(days==20){
      display.drawInvertedBitmap(349, 144, ling, 48, 66, GxEPD_RED);//画图
    }else if(days==21){
      display.drawInvertedBitmap(349, 144, yi, 18, 66, GxEPD_RED);//画图
    }else if(days==22){
      display.drawInvertedBitmap(349, 144, er, 48, 66, GxEPD_RED);//画图
    }else if(days==23){
      display.drawInvertedBitmap(349, 144, san, 48, 66, GxEPD_RED);//画图
    }else if(days==24){
      display.drawInvertedBitmap(349, 144, si, 48, 66, GxEPD_RED);//画图
    }else if(days==25){
      display.drawInvertedBitmap(349, 144, wu, 48, 66, GxEPD_RED);//画图
    }else if(days==26){
      display.drawInvertedBitmap(349, 144, liu, 48, 66, GxEPD_RED);//画图
    }else if(days==27){
      display.drawInvertedBitmap(349, 144, qi, 48, 66, GxEPD_RED);//画图
    }else if(days==28){
      display.drawInvertedBitmap(349, 144, ba, 48, 66, GxEPD_RED);//画图
    }else if(days==29){
      display.drawInvertedBitmap(349, 144, jiu, 48, 66, GxEPD_RED);//画图
    }
  }else{
      display.drawInvertedBitmap(301, 144, san, 48, 66, GxEPD_RED);//画图
    if(days==30){
      display.drawInvertedBitmap(349, 144, ling, 48, 66, GxEPD_RED);//画图
    }else if(days==31){
      display.drawInvertedBitmap(349, 144, yi, 18, 66, GxEPD_RED);//画图
    }
  }
  u8g2Fonts.setFont(chinese_city_gb2312);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // 设置前景色
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // 设置背景色
  u8g2Fonts.setCursor(300, 30);//标记：位置需要修改
  u8g2Fonts.print(timetim);
}
void hitokoto(){
//  display.drawRect(0, 0, 38, 12,1);
  u8g2Fonts.setFont(chinese_city_gb2312);
  u8g2Fonts.setForegroundColor(GxEPD_RED);  // 设置前景色
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // 设置背景色
  u8g2Fonts.setCursor(42, 12);
  u8g2Fonts.print(String(yiyan.hitokoto));
  display.drawInvertedBitmap(0, 0, yiyanp, 38, 12, GxEPD_RED);//画图
  
  
}
void newsdisplay(){
  display.drawLine(269, 25, 269, 296, 0);
  u8g2Fonts.setFont(chinese_city_gb2312);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // 设置前景色
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // 设置背景色
  if(udc%3==0){
    display.drawInvertedBitmap(75, 16, weibo, 32, 32, GxEPD_BLACK);//画图
    u8g2Fonts.setCursor(106,38);
    u8g2Fonts.print("微博热点");
  }else if(udc%3==1){
    display.drawInvertedBitmap(75, 16, toutiao, 32, 32, GxEPD_BLACK);//画图
    u8g2Fonts.setCursor(106,38);
    u8g2Fonts.print("央视新闻");
    
  }else{
    display.drawInvertedBitmap(75, 16, zhihu, 32, 32, GxEPD_BLACK);//画图
    u8g2Fonts.setCursor(106,38);
    u8g2Fonts.print("知乎热榜");
  }
  String news_title,tt="";
  for(int i=0;i<11;i++){
    u8g2Fonts.setCursor(4,60+i*22);
    news_title =String(xinwen.title[i]);
    if(news_title.length()>54){
       for(int j=0;j<54;j++){
         tt+=news_title[j];
       }
       u8g2Fonts.print(tt);
     }else{
      u8g2Fonts.print(news_title);
     }
    tt="";
  }
  
}
/*温度*/
dht11 DHT11;
void gettem(){
  DHT11.read(21);
  String temperature=String(DHT11.temperature)+"℃";
  String humidity = String(DHT11.humidity)+"%";
  u8g2Fonts.setFont(chinese_city_gb2312);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // 设置前景色
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // 设置背景色
  u8g2Fonts.setCursor(272,222);
  u8g2Fonts.print("室内");
  display.drawInvertedBitmap(312, 210, wendu, 16, 16, GxEPD_BLACK);//画图
  u8g2Fonts.setCursor(330,222);
  u8g2Fonts.print(temperature);
  display.drawInvertedBitmap(358, 210, shidu, 16, 16, GxEPD_BLACK);//画图
  u8g2Fonts.setCursor(376,222);
  u8g2Fonts.print(humidity);
}
