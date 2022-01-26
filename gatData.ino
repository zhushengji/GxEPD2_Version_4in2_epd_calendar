
void GetData()
{
  //"http://api.seniverse.com/v3/weather/now.json?key=S6pG_Q54kjfnBAi6i&location=深圳&language=zh-Hans&unit=c"
  //拼装实况天气API地址
  url_ActualWeather = "https://api.seniverse.com/v3/weather/now.json";
  url_ActualWeather += "?key=" + xz_code;
  url_ActualWeather += "&location=ip" ;
  url_ActualWeather += "&language=" + language;
  url_ActualWeather += "&unit=c";
  
  //https://api.seniverse.com/v3/weather/daily.json?key=S6pG_Q54kjfnBAi6i&location=深圳&language=zh-Hans&unit=c&start=0&days=3
  //拼装实况未来API地址
  url_FutureWeather = "https://api.seniverse.com/v3/weather/daily.json";
  url_FutureWeather += "?key=" + xz_code;
  url_FutureWeather += "&location=ip";
  url_FutureWeather += "&language=" + language;
  url_FutureWeather += "&unit=c";
  url_FutureWeather += "&start=0";
  url_FutureWeather += "&days=3";

  //https://api.seniverse.com/v3/life/suggestion.json?key=S6pG_Q54kjfnBAi6i&location=shanghai&language=zh-Hans
  //拼装生活指数
  String url_LifeIndex = "https://api.seniverse.com/v3/life/suggestion.json";
  url_LifeIndex += "?key=" + xz_code;
  url_LifeIndex += "&location=ip";

  //新闻地址
  String url_News="";
  if(udc%3==0){
    url_News="https://api.vvhan.com/api/wbhot";//微博
  }else if(udc%3==1){
    url_News = "https://api.iyk0.com/ysxw/";//央视新闻
  }else{
    url_News = "http://api.rosysun.cn/zhihu/";
  }
//  String url_News = "https://api.iyk0.com/ysxw/";//央视新闻
//  String url_News = "http://api.rosysun.cn/zhihu/";
//  String url_News = "https://api.iyk0.com/bdr";//百度头条
//  String url_News = "https://api.vvhan.com/api/douban";
  //请求数据并Json处理
//  display_partialLine(7, "获取生活指数");
/*两个半小时更新一次天气，节省访问次数且不影响使用*/
  if(udc%30==0){
    ParseActualWeather(callHttps(url_LifeIndex), &life_index); //获取生活指数
  
    ParseActualWeather(callHttps(url_ActualWeather), &actual);

//  display_bitmap_bottom(Bitmap_wlq2, "获取未来天气数据中");
    ParseFutureWeather(callHttps(url_FutureWeather), &future);
  }
  

  ParseHitokoto(callHttps(url_yiyan), &yiyan);

  ParseNews(callHttps(url_News),&xinwen);
}
