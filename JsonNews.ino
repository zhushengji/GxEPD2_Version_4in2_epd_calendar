//****** 获取新闻数据
void ParseNews(String content, struct News* data)
{
  DynamicJsonDocument json(8536); //分配内存,动态 1536
  DeserializationError error = deserializeJson(json, content); //解析json
  //serializeJson(json, Serial);//构造序列化json,将内容从串口输出
  if (error)   //检查API是否有返回错误信息，有返回则进入休眠
  {
    Serial.print("新闻加载json配置失败:");
    Serial.println(error.c_str());
    Serial.println(" ");
    String z = "新闻json配置失败:" + String(error.c_str()) + " " + content;
  }
  if (json["status_code"].isNull() == 0) //检查到不为空
  {
    strcpy(data->status_code, json["status_code"]);
    String z = "新闻异常:" + String(xinwen.status_code);
    Serial.print("新闻异常:"); Serial.println(xinwen.status_code);
  }
  else
  {
    if (json["data"].isNull() == 0){
      for(int i = 0;i<11;i++){
        strcpy(data->title[i], json["data"][i]["title"]);
      }
      
      } 
  }
}
