#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include "thingspeak.com_cert.h"

extern const unsigned char caCert[] PROGMEM;
extern const unsigned int caCertLen;

const char *ssid = "MY_SSID"; // TODO
const char *password = "MY_PASSWORD"; // TODO

const char *api_key="J4T4XOGET2K7UY9K";//write key
//GET https://api.thingspeak.com/update?api_key=J4T4XOGET2K7UY9K&field1=0
const char *host = "api.thingspeak.com";
const char *path = "update";
#define MAX_URI 256
char uri_str[MAX_URI];//used to form the uri
const int port = 443;
#define MAX_REQUEST 1024
char request_body[MAX_REQUEST];
#define MAX_POST 1024
char post_body[MAX_POST];
#define USE_CACERT

WiFiClientSecure client; // use TLS

void create_uri(){
  snprintf(uri_str,MAX_URI,"%s/%s",path,WiFi.macAddress().c_str());
}
void setup_sensor(){

  
}
const char* create_request_post(const char* tuples){
  snprintf(request_body,MAX_REQUEST,"POST %s HTTP/1.1\r\n"
  "Host: %s\r\n"
  "Content-Type: application/x-www-form-urlencoded\r\n"
  "Content-length: %d\r\n"
  "Connection: close\r\n\r\n",uri_str,host,strlen(tuples));
  strncat(request_body,tuples,MAX_REQUEST);
  strncat(request_body,"\r\n",MAX_REQUEST);

  return request_body;
}
void sync_time(){
  Serial.println("Setting system time");
  // call built-in, ESP8266-specific function in time.cpp
  // https://github.com/esp8266/Arduino/blob/master/cores/esp8266/time.cpp#L61
  const int timezone = 0;
  const int dst_off = 0;
  configTime(timezone * 3600, dst_off, "pool.ntp.org", "time.nist.gov");
  // wait for time() being adjusted, as a side effect of configTime
  while (time(NULL) < 28800 * 2) {
    delay(500);
  }
}
char* timestamp(){
  char stamp[125];
  time_t local_time;
  tm* gm_time;
  local_time=time(NULL);
  gm_time = gmtime(&local_time);
  
  snprintf(stamp,125,"%d-%02d-%02dT%02d:%02d:%02dZ",gm_time->tm_year+1900/*years since 1900*/, gm_time->tm_mon+1/*months since january*/, gm_time->tm_mday, gm_time->tm_hour, gm_time->tm_min, gm_time->tm_sec);//YYYY-MM-DDTHH:mm:ssZ
  return stamp;
}
void send_request(){
  Serial.print("Connecting to host ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);
  if (client.connect(host, port)) {
    Serial.println("Verifying certificate chain ");
    if (client.verifyCertChain(host)) {
      Serial.print('\n');    
      Serial.println("Sending HTTP request");
      Serial.println("Request:");
      //GET https://api.thingspeak.com/update?api_key=J4T4XOGET2K7UY9K&field1=0
      snprintf(post_body,MAX_POST,"api_key=%s",api_key);
      Serial.print(create_request_post(post_body));
      client.print(create_request_post(post_body));
  
      Serial.println("Reading HTTP response\n");
      while (client.connected() || client.available()) {
        int ch = client.read();
        while (ch >= 0) {
            Serial.print((char) ch);
            ch = client.read();
        }
      }
    } else {
      Serial.println("Certificate mismatch");
    }
  } else {
    Serial.println("Cannot connect");
  }
}
void connect_wifi(){
  //connect to network
  Serial.print("\nConnecting to network ");
  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100); // keeps watchdog happy
  }
  Serial.print("Connected to network, local IP = "); 
  Serial.println(WiFi.localIP());
  sync_time();
}
void setup() {
  Serial.begin(115200);
  // setup uri string for requests
  Serial.println("Setup uri for requests");
  create_uri();
  Serial.println(uri_str);
  //setup temp and humidity sensor
  setup_sensor();
  //connect to network
  connect_wifi();

  Serial.println("Setting CA certificate ");
  if (!client.setCACert_P(caCert, caCertLen)) {
    Serial.println("Setting CA certificate failed");
  }
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){//lost connection, reconnect
    Serial.println("lost wifi connection");
    connect_wifi();
  }
  Serial.println(timestamp());
//  send_request();
}
