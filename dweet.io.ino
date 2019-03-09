#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include "dweet.io_cert.h"

// based on https://github.com/SensorsIot/HTTPS-for-Makers licensed under
// MIT https://github.com/SensorsIot/HTTPS-for-Makers/blob/master/LICENSE
// CA certificate converted with CertToESP8266.py in the same repository
extern const unsigned char caCert[] PROGMEM;
extern const unsigned int caCertLen;

const char *ssid = "MY_SSID"; // TODO
const char *password = "MY_PASSWORD"; // TODO

const char *host = "dweet.io";
const char *path = "/dweet/for";
#define MAX_URI 256
char uri_str[MAX_URI];//used to form the uri
const int port = 443;
#define MAX_REQUEST 1024
char request_body[MAX_REQUEST];
#define USE_CACERT
#ifndef USE_CACERT
const uint8_t fingerprint[]= //SHA-1, not very secure anymore
  {0x4A,0x4E,0x39,0x71,0x0B,0x7D,0xD7,0x95,0xD2,0x35,0x06,0xC1,0xC4,0xBF,0x48,0x8D,0x92,0x5E,0x3F,0xED};
#endif

void create_uri(){
  snprintf(uri_str,MAX_URI,"%s/%s",path,WiFi.macAddress().c_str());
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
void setup() {
  Serial.begin(115200);
  // setup uri string for requests
  Serial.println("Setup uri for requests");
  create_uri();
  Serial.println(uri_str);
  //connect to network
  Serial.print("\nConnecting to network ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100); // keeps watchdog happy
  }
  Serial.print("Connected to network, local IP = "); 
  Serial.println(WiFi.localIP());

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

  WiFiClientSecure client; // use TLS
  #ifdef USE_CACERT
  Serial.println("Setting CA certificate ");
  if (!client.setCACert_P(caCert, caCertLen)) {
    Serial.println("Setting CA certificate failed");
  }
  #else
    client.setFingerprint(fingerprint,host);
  #endif
  Serial.print("Connecting to host ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);
  if (client.connect(host, port)) {
    #ifdef USE_CACERT
    Serial.println("Verifying certificate chain ");
    if (client.verifyCertChain(host)) {
    #else
    if(client.verify/(fingerprint,host)){
    #endif    
      Serial.print('\n');    
      Serial.println("Sending HTTP request");
      Serial.println("Request:");
      Serial.print(create_request_post("somenewkey=value"));
      client.print(create_request_post("somenewkey=value"));
  
      Serial.println("Reading HTTP response\n");
      while (client.connected() || client.available()) {
        int ch = client.read();
        while (ch >= 0) {
            Serial.print((char) ch);
            ch = client.read();
        }
      }
    } else {
    #ifdef USE_CACERT
      Serial.println("Certificate mismatch");
    #else
      Serial.println("Fingerprint mismatch");
    #endif
    }
  } else {
    Serial.println("Cannot connect");
  }
}

void loop() {}
