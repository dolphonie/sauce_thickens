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

  http.begin(client, "http://jsonplaceholder.typicode.com/users/1");
  int httpCode = http.GET();                                  //Send the request

  if (httpCode >= 200 && httpCode <= 299 ) { //Check the returning code
    // success
    String payload = http.getString();   //Get the request response payload
    http.end();   //Close connection
    return payload;
  } else {
    //failure
    Serial.println("HTTP request failed");
    http.end();   //Close connection
    return "";
  }
}

//void http_post(String url) {
//  WiFiClient client;
//  HTTPClient http;
//
//  // Your Domain name with URL path or IP address with path
//  http.begin(client, url);
//
//  // If you need an HTTP request with a content type: application/json, use the following:
////  http.addHeader("Content-Type", "application/json");
////  int httpResponseCode = http.POST("{\"speed\":\"5\"}");
//  int httpResponseCode = http.POST();
//  Serial.print("HTTP Response code: ");
//  Serial.println(httpResponseCode);
//
//  // Free resources
//  http.end();
////  return http.getString();
//}

#endif
