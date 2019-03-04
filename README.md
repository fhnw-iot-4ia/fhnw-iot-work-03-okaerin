# IoT Engineering
## Hands-on of lesson 3
For slides and example code, see [lesson 3](../../../fhnw-iot/blob/master/03/README.md)

> *Note: Do not work on this repository right away.*<br/>
> *[Check existing forks to find the specific repository for your class.](../../network/members)*

### a) Wi-Fi, 15'
* Build and run the previous Wi-Fi related examples.
* Use the _.ino_ link on each page to find the source.
* The examples are in the course repository.
* Make sure to use the ESP8266 board

### b) ESP8266 NTP clients, 15'
* Build, run and compare the following NTP clients:
* The [Web-based time client](https://github.com/tamberg/fhnw-iot/blob/master/03/Arduino/ESP8266_WiFiTimeClient/ESP8266_WiFiTimeClient.ino) and [built-in NTP client](https://github.com/tamberg/fhnw-iot/blob/master/03/Arduino/ESP8266_WiFiNtpClient/ESP8266_WiFiNtpClient.ino).
* Arduino > Examples > ESP8266WiFi > [NTPClient](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/NTPClient/NTPClient.ino).
* Bonus: Read the code of this [low memory version](https://playground.arduino.cc/Code/NTPclient).

### c) ESP8266 TLS clients, 15'
* Build, run and compare the following TLS clients:
* [Secure Wi-Fi client](https://github.com/tamberg/fhnw-iot/blob/master/03/Arduino/ESP8266_WiFiClientSecure/ESP8266_WiFiClientSecure.ino), with [fingerprint](https://github.com/tamberg/fhnw-iot/blob/master/03/Arduino/ESP8266_WiFiClientSecureFingerprint/ESP8266_WiFiClientSecureFingerprint.ino), with [CA check](https://github.com/tamberg/fhnw-iot/blob/master/03/Arduino/ESP8266_WiFiClientSecureCaCert/ESP8266_WiFiClientSecureCaCert.ino).
* Locate/download the CA certificate in your browser.
* Locate the SHA-1 fingerprint of the host certificate.
* Bonus: Try to change the host to another Website.

### d) Wi-Fi, 15'
* 

### Submitting results
* [Commit and push](#git) local changes to your repository.
* Want a review? [Create an issue](../../issues/new), mention me (@tamberg).

## Tools
### Git
On your computer
* In the hands-on repository [fork for your class](../../network/members), in README.md, click the _GitHub Classroom link_.
* Once you accept the assessment, you get a personal, private repository URL for your _USER_NAME_:<pre>
http://github.com/fhnw-iot-CLASS/fhnw-iot-work-03-USER_NAME</pre>

On your computer or Raspberry Pi
* Clone the repository<pre>
    $ cd ~
    $ git clone REPO_URL</pre>
* Add a file<pre>
    $ git add FILE</pre>
* Commit changes<pre>
    $ git commit FILE -m "Fixed all bugs"</pre>
* Push changes<pre>
    $ git push</pre>

## Wiki
- [IoT Engineering Wiki](https://github.com/tamberg/fhnw-iot/wiki)

## Support
- [IoT Engineering Slack](https://fhnw-iot.slack.com/)
