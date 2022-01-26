//****** 获取一言数据
void ParseHitokoto(String content, struct Hitokoto* data)
{
  DynamicJsonDocument json(1536); //分配内存,动态
  DeserializationError error = deserializeJson(json, content); //解析json
  //serializeJson(json, Serial);//构造序列化json,将内容从串口输出
  if (error)   //检查API是否有返回错误信息，有返回则进入休眠
  {
    Serial.print("一言加载json配置失败:");
    Serial.println(error.c_str());
    Serial.println(" ");
    String z = "一言json配置失败:" + String(error.c_str()) + " " + content;
  }
  if (json["status_code"].isNull() == 0) //检查到不为空
  {
    strcpy(data->status_code, json["status_code"]);
    String z = "一言异常:" + String(yiyan.status_code);
    Serial.print("一言异常:"); Serial.println(yiyan.status_code);
  }
  else
  {
    if (json["hitokoto"].isNull() == 0){
      strcpy(data->hitokoto, json["hitokoto"]);
      } 
    else strcpy(data->hitokoto, "哎呀\"hitokoto\"没有数据呢");
  }
  // 复制我们感兴趣的字符串 ,先检查是否为空，空会导致系统无限重启
  // 这不是强制复制，你可以使用指针，因为他们是指向"内容"缓冲区内
  // 所以你需要确保 当你读取字符串时它仍在内存中
  // isNull()检查是否为空 空返回1 非空0
}
