#include <DNSServer.h>
#include <EEPROM.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include "WiFi.h"
const IPAddress apIP(192, 168, 1, 1);
const char* apSSID = "码蜂科技配网WiFi";
boolean settingMode;
String ssidList;
String xz_code;
DNSServer dnsServer;
WebServer webServer(80);
bool flag =false;

boolean restoreConfig() {
  Serial.println("Reading EEPROM...");
  String ssid = "";
  String pass = "";
  String authcode= "";
  if (EEPROM.read(4000) != 0) {
    for (int i = 4000; i < 4032; ++i) {
      char ch = EEPROM.read(i);
      if (isalpha(ch) || isdigit(ch)) {
        ssid += char(EEPROM.read(i));
      }

    }
    Serial.print("WiFi: ");
    Serial.println(ssid);
    for (int i = 4032; i < 4064; ++i) {
      char ch = EEPROM.read(i);
      if (isalpha(ch) || isdigit(ch)) {
        pass += char(EEPROM.read(i));
      }
    }
    Serial.print("密码: ");
    Serial.println(pass);
    for (int i = 4064; i < 4096; ++i) {
      char ch = EEPROM.read(i);
      if (isalpha(ch) || isdigit(ch)||ch=='-') {
        authcode += char(EEPROM.read(i));
      }
    }
    Serial.print("密钥: ");
    Serial.println(authcode);
    WiFi.begin(ssid.c_str(), pass.c_str());

    xz_code=authcode.c_str();
    WiFi.begin(ssid.c_str(), pass.c_str());
    return true;
  }
  else {
    Serial.println("Config not found.");
    return false;
  }
}
boolean checkConnection() {
  int count = 0;
  Serial.println("正在等待连接");
  while ( count < 30 ) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("成功连接！");
      return (true);
    }
    delay(500);
    Serial.print(".");
    count++;
  }
  Serial.println("连接超时.");
  return false;
}

String makePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s += "<title>";
  s += title;
  s += "</title></head><body>";
  s += contents;
  s += "</body></html>";
  return s;
}

String urlDecode(String input) {
  String s = input;
  s.replace("%20", " ");
  s.replace("+", " ");
  s.replace("%21", "!");
  s.replace("%22", "\"");
  s.replace("%23", "#");
  s.replace("%24", "$");
  s.replace("%25", "%");
  s.replace("%26", "&");
  s.replace("%27", "\'");
  s.replace("%28", "(");
  s.replace("%29", ")");
  s.replace("%30", "*");
  s.replace("%31", "+");
  s.replace("%2C", ",");
  s.replace("%2E", ".");
  s.replace("%2F", "/");
  s.replace("%2C", ",");
  s.replace("%3A", ":");
  s.replace("%3A", ";");
  s.replace("%3C", "<");
  s.replace("%3D", "=");
  s.replace("%3E", ">");
  s.replace("%3F", "?");
  s.replace("%40", "@");
  s.replace("%5B", "[");
  s.replace("%5C", "\\");
  s.replace("%5D", "]");
  s.replace("%5E", "^");
  s.replace("%5F", "-");
  s.replace("%60", "`");
  return s;
}
void startWebServer() {
//  display.drawInvertedBitmap(0, 0, jitang, 400, 300, GxEPD_BLACK);//画图
//  Serial.println("开屏动画");
  
  if (settingMode) {
    Serial.print("Starting Web Server at ");
    Serial.println(WiFi.softAPIP());
    webServer.on("/settings", []() {
      String s = "<head><meta charset=\"utf-8\"></head><h1>码蜂Wi-Fi配置</h1><p>请在选择WiFi名称后输入对应的WiFi密码.</p>";
      s += "<form method=\"get\" action=\"setap\"><label>网络:</label><select name=\"ssid\">";
      s += ssidList;
      s += "</select><br>密码:<input name=\"pass\" length=64 type=\"password\"><br>心知密钥:<input name=\"authcode\" length=64 type=\"password\"><br>";
      s += "<input name=\"保存并提交\"  type=\"submit\"></form>";
      webServer.send(200, "text/html", makePage("码蜂Wi-Fi配置", s));
    });
    webServer.on("/setap", []() {
        //清空数据，防止出现WiFi账号密码长度不一致导致的无法联网问题
      for (int i = 4000; i < 4096; ++i) {
        EEPROM.begin(4096);
        EEPROM.write(i, 0);
        EEPROM.commit();
      }
      String ssid = urlDecode(webServer.arg("ssid"));
      Serial.print("SSID: ");
      Serial.println(ssid);
      String pass = urlDecode(webServer.arg("pass"));
      Serial.print("Password: ");
      Serial.println(pass);
      String authcode = urlDecode(webServer.arg("authcode"));
      Serial.print("authcode: ");
      Serial.println(authcode);
      Serial.println("Writing ssid to EEPROM...");
      for (int i = 0; i < ssid.length(); ++i) {
        EEPROM.begin(4096);
        EEPROM.write(4000 + i, ssid[i]);
        EEPROM.commit();
      }
      Serial.println("Writing Password to EEPROM...");
      for (int i = 0; i < pass.length(); ++i) {
        EEPROM.begin(4096);
        EEPROM.write(4032 + i, pass[i]);
        EEPROM.commit();
      }
      EEPROM.end();
      Serial.println("Write EEPROM done!");
      Serial.println("Writing authcode to EEPROM...");
      for (int i = 0; i < authcode.length(); ++i) {
        EEPROM.begin(4096);
        EEPROM.write(4064 + i, authcode[i]);
        EEPROM.commit();
      }
      EEPROM.end();
      Serial.println("Write EEPROM done!");
      String s = "<h1>设置结束！</h1><p>设备即将在重启后接入 \"";

      s += ssid;
      s += "\" ";
      webServer.send(200, "text/html", makePage("码蜂Wi-Fi配置", s));
      ESP.restart();
    });
    webServer.onNotFound([]() {
      String s = "<h1>配网模式</h1><p><a href=\"/settings\">点击配网</a></p>";
      webServer.send(200, "text/html", makePage("配网模式", s));
    });
  }
  else {
    Serial.print("Starting Web Server at ");
    Serial.println(WiFi.localIP());
    webServer.on("/", []() {
      String s = "<h1>STA mode</h1><p><a href=\"/reset\">重置WiFi设置</a></p>";
      webServer.send(200, "text/html", makePage("STA mode", s));
    });
    webServer.on("/reset", []() {
      for (int i = 4000; i < 4096; ++i) {
        EEPROM.begin(4096);
        EEPROM.write(i, 0);
        //        EEPROM.commit();
        EEPROM.end();
      }

      String s = "<h1>Wi-Fi 设置已重置</h1><p>请重启设备.</p>";
      webServer.send(200, "text/html", makePage("Reset Wi-Fi Settings", s));
    });
  }
  webServer.begin();
}
void setupMode() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  delay(100);
  Serial.println("");
  for (int i = 0; i < n; ++i) {
    ssidList += "<option value=\"";
    ssidList += WiFi.SSID(i);
    ssidList += "\">";
    ssidList += WiFi.SSID(i);
    ssidList += "</option>";
  }
  delay(100);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(apSSID);
  dnsServer.start(53, "*", apIP);
  /*如果联网失败就显示失败提醒*/
  display.fillScreen(GxEPD_WHITE);
  display.drawInvertedBitmap(0, 0, jitang, 400, 300, GxEPD_BLACK);//画图
  display.nextPage();
  startWebServer();
  Serial.print("Starting Access Point at \"");
  Serial.print(apSSID);
  Serial.println("\"");
}



void wifi_init(){
  delay(10);
  if (restoreConfig()) {
    if (checkConnection()) {
      settingMode = false;
      startWebServer();
      return;
    }
  }
  settingMode = true;
  setupMode();
}
