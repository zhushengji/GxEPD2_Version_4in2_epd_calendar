//****** 天气数据获取
//使用Json解析天气数据，天气实况
bool ParseActualWeather(String content, struct ActualWeather* data)
{
  DynamicJsonDocument json(1536); //分配内存,动态
  DeserializationError error = deserializeJson(json, content); //解析json
  //serializeJson(json, Serial);//构造序列化json,将内容从串口输出
  if (error)
  {
    Serial.print("实况天气加载json配置失败:");
    Serial.println(error.c_str());
    Serial.println(" ");
    String z = "实况天气json配置失败:" + String(error.c_str()) + " " + content;
    //display_partialLine(7, z);
//    esp_sleep(0);
    return false;
  }

  //检查API是否有返回错误信息，有返回则进入休眠
  if (json["status_code"].isNull() == 0) //检查到不为空
  {
    strcpy(data->status_code, json["status_code"]);
    String z;
    if (String(actual.status_code) == "AP010001") z = "API 请求参数错误" ;
    else if (String(actual.status_code) == "AP010002") z = "没有权限访问这个 API 接口" ;
    else if (String(actual.status_code) == "AP010003") z = "API 密钥 key 错误" ;
    else if (String(actual.status_code) == "AP010004") z = "签名错误" ;
    else if (String(actual.status_code) == "AP010005") z = "你请求的 API 不存在" ;
    else if (String(actual.status_code) == "AP010006") z = "没有权限访问这个地点" ;
    else if (String(actual.status_code) == "AP010007") z = "JSONP 请求需要使用签名验证方式" ;
    else if (String(actual.status_code) == "AP010008") z = "没有绑定域名" ;
    else if (String(actual.status_code) == "AP010009") z = "API 请求的 user-agent 与你设置的不一致" ;
    else if (String(actual.status_code) == "AP010010") z = "没有这个地点";
    else if (String(actual.status_code) == "AP010011") z = "无法查找到指定 IP 地址对应的城市" ;
    else if (String(actual.status_code) == "AP010012") z = "你的服务已经过期" ;
    else if (String(actual.status_code) == "AP010013") z = "访问量余额不足" ;
    else if (String(actual.status_code) == "AP010014") z = "访问频率超过限制" ;
    else if (String(actual.status_code) == "AP010015") z = "暂不支持该城市的车辆限行信息" ;
    else if (String(actual.status_code) == "AP010016") z = "暂不支持该城市的潮汐数据" ;
    else if (String(actual.status_code) == "AP010017") z = "请求的坐标超出支持的范围" ;
    else if (String(actual.status_code) == "AP100001") z = "心知系统内部错误：数据缺失" ;
    else if (String(actual.status_code) == "AP100002") z = "心知系统内部错误：数据错误" ;
    else if (String(actual.status_code) == "AP100003") z = "心知系统内部错误：服务内部错误" ;
    else if (String(actual.status_code) == "AP100004") z = "心知系统内部错误：网关错误" ;
    else z = "实况天气异常:" + String(actual.status_code);
    //display_partialLine(7, z);
    Serial.print("实况天气异常:"); Serial.println(actual.status_code);
    //esp_sleep(60);
  }

  // 复制我们感兴趣的字符串 ,先检查是否为空，空会导致系统无限重启
  // isNull()检查是否为空 空返回1 非空0
  if (json["results"][0]["location"]["name"].isNull() == 0)
    strcpy(data->city, json["results"][0]["location"]["name"]);
  if (json["results"][0]["now"]["text"].isNull() == 0)
    strcpy(data->weather_name, json["results"][0]["now"]["text"]);
  if (json["results"][0]["now"]["code"].isNull() == 0)
    strcpy(data->weather_code, json["results"][0]["now"]["code"]);
  if (json["results"][0]["now"]["temperature"].isNull() == 0)
    strcpy(data->temp, json["results"][0]["now"]["temperature"]);
  if (json["results"][0]["last_update"].isNull() == 0)
    strcpy(data->last_update, json["results"][0]["last_update"]);
  // 这不是强制复制，你可以使用指针，因为他们是指向"内容"缓冲区内，所以你需要确保
  // 当你读取字符串时它仍在内存中
  
  return true;
}

//使用Json解析天气数据，今天和未来2天
bool ParseFutureWeather(String content, struct FutureWeather* data)
{
  DynamicJsonDocument json(2560); //分配内存,动态
  DeserializationError error = deserializeJson(json, content); //解析json
  // serializeJson(json, Serial);//构造序列化json,将内容从串口输出
  if (error)
  {
    Serial.print("未来天气json配置失败:");
    Serial.println(error.c_str());
    Serial.println(" ");
    String z = "未来天气加载json配置失败:" + String(error.c_str()) + " " + content;
    //display_partialLine(7, z);
//    esp_sleep(0);
    return false;
  }

  //检查API是否有返回错误信息，有返回则进入休眠
  if (json["status_code"].isNull() == 0) //检查到不为空
  {
    strcpy(data->status_code, json["status_code"]);
    String z;
    if (String(future.status_code) == "AP010001") z = "API 请求参数错误" ;
    else if (String(future.status_code) == "AP010002") z = "没有权限访问这个 API 接口" ;
    else if (String(future.status_code) == "AP010003") z = "API 密钥 key 错误" ;
    else if (String(future.status_code) == "AP010004") z = "签名错误" ;
    else if (String(future.status_code) == "AP010005") z = "你请求的 API 不存在" ;
    else if (String(future.status_code) == "AP010006") z = "没有权限访问这个地点: ";
    else if (String(future.status_code) == "AP010007") z = "JSONP 请求需要使用签名验证方式" ;
    else if (String(future.status_code) == "AP010008") z = "没有绑定域名" ;
    else if (String(future.status_code) == "AP010009") z = "API 请求的 user-agent 与你设置的不一致" ;
    else if (String(future.status_code) == "AP010010") z = "没有这个地点" ;
    else if (String(future.status_code) == "AP010011") z = "无法查找到指定 IP 地址对应的城市" ;
    else if (String(future.status_code) == "AP010012") z = "你的服务已经过期" ;
    else if (String(future.status_code) == "AP010013") z = "访问量余额不足" ;
    else if (String(future.status_code) == "AP010014") z = "访问频率超过限制" ;
    else if (String(future.status_code) == "AP010015") z = "暂不支持该城市的车辆限行信息" ;
    else if (String(future.status_code) == "AP010016") z = "暂不支持该城市的潮汐数据" ;
    else if (String(future.status_code) == "AP010017") z = "请求的坐标超出支持的范围" ;
    else if (String(future.status_code) == "AP100001") z = "心知系统内部错误：数据缺失" ;
    else if (String(future.status_code) == "AP100002") z = "心知系统内部错误：数据错误" ;
    else if (String(future.status_code) == "AP100003") z = "心知系统内部错误：服务内部错误" ;
    else if (String(future.status_code) == "AP100004") z = "心知系统内部错误：网关错误" ;
    else z = "未来天气异常:" + String(future.status_code);
    //display_partialLine(7, z);
    Serial.print("未来天气异常:"); Serial.println(future.status_code);
    //esp_sleep(60);
  }

  // 复制我们感兴趣的字符串，先检查是否为空，空会复制失败导致系统无限重启
  if (json["results"][0]["daily"][0]["date"].isNull() == 0)        //日期
    strcpy(data->date0, json["results"][0]["daily"][0]["date"]);
  if (json["results"][0]["daily"][1]["date"].isNull() == 0)
    strcpy(data->date1, json["results"][0]["daily"][1]["date"]);
  if (json["results"][0]["daily"][2]["date"].isNull() == 0)
    strcpy(data->date2, json["results"][0]["daily"][2]["date"]);

  if (json["results"][0]["daily"][0]["text_day"].isNull() == 0)    //白天天气现象
    strcpy(data->date0_text_day, json["results"][0]["daily"][0]["text_day"]);
  if (json["results"][0]["daily"][1]["text_day"].isNull() == 0)
    strcpy(data->date1_text_day, json["results"][0]["daily"][1]["text_day"]);
  if (json["results"][0]["daily"][2]["text_day"].isNull() == 0)
    strcpy(data->date2_text_day, json["results"][0]["daily"][2]["text_day"]);

  if (json["results"][0]["daily"][0]["text_night"].isNull() == 0)    //晚间天气现象
    strcpy(data->date0_text_night, json["results"][0]["daily"][0]["text_night"]);
  if (json["results"][0]["daily"][1]["text_night"].isNull() == 0)
    strcpy(data->date1_text_night, json["results"][0]["daily"][1]["text_night"]);
  if (json["results"][0]["daily"][2]["text_night"].isNull() == 0)
    strcpy(data->date2_text_night, json["results"][0]["daily"][2]["text_night"]);

  if (json["results"][0]["daily"][0]["high"].isNull() == 0)
    strcpy(data->date0_high, json["results"][0]["daily"][0]["high"]);  //最高温度
  if (json["results"][0]["daily"][1]["high"].isNull() == 0)
    strcpy(data->date1_high, json["results"][0]["daily"][1]["high"]);
  if (json["results"][0]["daily"][2]["high"].isNull() == 0)
    strcpy(data->date2_high, json["results"][0]["daily"][2]["high"]);

  if (json["results"][0]["daily"][0]["low"].isNull() == 0)             //最低温度
    strcpy(data->date0_low, json["results"][0]["daily"][0]["low"]);
  if (json["results"][0]["daily"][1]["low"].isNull() == 0)
    strcpy(data->date1_low, json["results"][0]["daily"][1]["low"]);
  if (json["results"][0]["daily"][2]["low"].isNull() == 0)
    strcpy(data->date2_low, json["results"][0]["daily"][2]["low"]);

  if (json["results"][0]["daily"][0]["humidity"].isNull() == 0)                //湿度
    strcpy(data->date0_humidity, json["results"][0]["daily"][0]["humidity"]);

  if (json["results"][0]["daily"][0]["wind_scale"].isNull() == 0)        //风力等级
    strcpy(data->date0_wind_scale, json["results"][0]["daily"][0]["wind_scale"]);
  // 这不是强制复制，你可以使用指针，因为他们是指向"内容"缓冲区内，所以你需要确保
  // 当你读取字符串时它仍在内存中
  return true;
}


//使用Json解析天气数据，天气实况
bool ParseActualWeather(String content, struct LifeIndex* data)
{
  DynamicJsonDocument json(1536); //分配内存,动态
  DeserializationError error = deserializeJson(json, content); //解析json
  //serializeJson(json, Serial);//构造序列化json,将内容从串口输出
  if (error)
  {
    Serial.print("天气指数加载json配置失败:");
    Serial.println(error.c_str());
    Serial.println(" ");
    String z = "天气指数json配置失败:" + String(error.c_str()) + " " + content;
    //display_partialLine(7, z);
//    esp_sleep(0);

    return false;
  }

  //检查API是否有返回错误信息，有返回则进入休眠
  if (json["status_code"].isNull() == 0) //检查到不为空
  {
    strcpy(data->status_code, json["status_code"]);
    String z;
    if (String(actual.status_code) == "AP010001") z = "API 请求参数错误" ;
    else if (String(actual.status_code) == "AP010002") z = "没有权限访问这个 API 接口" ;
    else if (String(actual.status_code) == "AP010003") z = "API 密钥 key 错误" ;
    else if (String(actual.status_code) == "AP010004") z = "签名错误" ;
    else if (String(actual.status_code) == "AP010005") z = "你请求的 API 不存在" ;
    else if (String(actual.status_code) == "AP010006") z = "没有权限访问这个地点: ";
    else if (String(actual.status_code) == "AP010007") z = "JSONP 请求需要使用签名验证方式" ;
    else if (String(actual.status_code) == "AP010008") z = "没有绑定域名" ;
    else if (String(actual.status_code) == "AP010009") z = "API 请求的 user-agent 与你设置的不一致" ;
    else if (String(actual.status_code) == "AP010010") z = "没有这个地点" ;
    else if (String(actual.status_code) == "AP010011") z = "无法查找到指定 IP 地址对应的城市" ;
    else if (String(actual.status_code) == "AP010012") z = "你的服务已经过期" ;
    else if (String(actual.status_code) == "AP010013") z = "访问量余额不足" ;
    else if (String(actual.status_code) == "AP010014") z = "访问频率超过限制" ;
    else if (String(actual.status_code) == "AP010015") z = "暂不支持该城市的车辆限行信息" ;
    else if (String(actual.status_code) == "AP010016") z = "暂不支持该城市的潮汐数据" ;
    else if (String(actual.status_code) == "AP010017") z = "请求的坐标超出支持的范围" ;
    else if (String(actual.status_code) == "AP100001") z = "心知系统内部错误：数据缺失" ;
    else if (String(actual.status_code) == "AP100002") z = "心知系统内部错误：数据错误" ;
    else if (String(actual.status_code) == "AP100003") z = "心知系统内部错误：服务内部错误" ;
    else if (String(actual.status_code) == "AP100004") z = "心知系统内部错误：网关错误" ;
    else z = "天气指数异常:" + String(actual.status_code);
    //display_partialLine(7, z);
    Serial.print("天气指数异常:"); Serial.println(actual.status_code);
    //esp_sleep(60);
  }

  // 复制我们感兴趣的字符串 ,先检查是否为空，空会导致系统无限重启
  // isNull()检查是否为空 空返回1 非空0
  if (json["results"][0]["suggestion"]["uv"]["brief"].isNull() == 0)          //紫外线指数
    strcpy(data->uvi, json["results"][0]["suggestion"]["uv"]["brief"]);

  //if (json["results"][0]["now"]["text"].isNull() == 0)
  //strcpy(data->weather_name, json["results"][0]["now"]["text"]);

  // 这不是强制复制，你可以使用指针，因为他们是指向"内容"缓冲区内，所以你需要确保
  // 当你读取字符串时它仍在内存中
  return true;
}
