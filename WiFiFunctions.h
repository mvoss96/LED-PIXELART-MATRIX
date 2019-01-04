#ifndef WIFI_FUNCTIONS_H
#define WIFI_FUNCTIONS_H
void wifi_init()
{
  String ssid = "";
  String password ="";
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

String translate_wifi_status(byte stat)
{
  String wifi_status;
  switch (stat)
  {
    case 0: wifi_status = "idle"; break;
    case 1: wifi_status = "no SSID"; break;
    case 2: wifi_status = "Scan completed"; break;
    case 3: wifi_status = "connected"; break;
    case 4: wifi_status = "connection failed"; break;
    case 5: wifi_status = "connection lost"; break;
    case 6: wifi_status = "disconnected"; break;
    default: wifi_status = "unknown";
  }
  return wifi_status;
}

#endif
