#ifndef WIFI_FUNCTIONS_H
#define WIFI_FUNCTIONS_H

#include <string.h>
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "constants.h"

const int RESPONSE_TIMEOUT = 10000; //ms to wait for response from host
const uint16_t OUT_BUFFER_SIZE = 10000; //size of buffer to hold HTTP response

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(NETWORK);

  WiFi.begin(NETWORK, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/*----------------------------------
  char_append Function:
  Arguments:
    char* buff: pointer to character array which we will append a
    char c:
    uint16_t buff_size: size of buffer buff

  Return value:
    boolean: True if character appended, False if not appended (indicating buffer full)
*/
uint8_t char_append(char* buff, char c, uint16_t buff_size) {
  int len = strlen(buff);
  if (len > buff_size) return false;
  buff[len] = c;
  buff[len + 1] = '\0';
  return true;
}

String http_get(String url) {
  WiFiClient client;
  HTTPClient http;  //Declare an object of class HTTPClient

  http.begin(client, url);
  int httpCode = http.GET();                                  //Send the request

  if (httpCode >0) { //Check the returning code
    // success
    String payload = http.getString();   //Get the request response payload
    http.end();   //Close connection
    Serial.println(payload);
    return payload;
  } else {
    //failure
    Serial.println("HTTP request failed");
    Serial.println(httpCode);
    http.end();   //Close connection
    return "100";
  }
}


#endif
