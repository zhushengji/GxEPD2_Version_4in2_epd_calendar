String callHttps(String url)
{
  String payload;
  Serial.print("requesting URL: ");
  Serial.println(url);
  HTTPClient https;
  if (https.begin(url))
  {
    int httpsCode = https.GET();
    if (httpsCode > 0)  //判断有无返回值
    {
      /*payload = https.getString();
      Serial.println(payload);
      return payload;*/
      if (httpsCode == 200 || httpsCode == 304 || httpsCode == 403 || httpsCode == 404 || httpsCode ==   500) //判断请求是正确
      {
        payload = https.getString();
//        Serial.println(payload);
        Serial.println(" ");
        return payload;
      }
      else
      {
        Serial.print("请求错误："); Serial.println(httpsCode); Serial.println(" ");
        char* httpsCode_c = new char[8];
        itoa(httpsCode, httpsCode_c, 10); //int转char*
        payload = "{\"status_code\":\"" + String("请求错误:") + String(httpsCode_c) + "\"}";
        return payload;
      }
    }
    else
    {
      Serial.println(" "); Serial.print("GET请求错误："); Serial.println(httpsCode);
      Serial.printf("[HTTPS] GET... 失败, 错误: %s\n", https.errorToString(httpsCode).c_str());
      payload = "{\"status_code\":\"" + String(https.errorToString(httpsCode).c_str()) + "\"}";
      //Serial.println(payload);
      return payload;
    }
  }
  else
  {
    Serial.printf("[HTTPS] 无法连接服务器\n");
    payload = "{\"status_code\":\"" + String("无法连接服务器") + "\"}";
    return payload;
  }
  https.end();
}
