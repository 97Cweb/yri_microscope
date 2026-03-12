#include "HttpClient.h"

#include <WiFi.h>
#include <HTTPClient.h>

HttpClient::HttpClient(){}

bool HttpClient::getText(const String& url, String& out){
  if(_busy){
    Serial.println("[HttpClient] busy");
    return false;
  }
  _busy = true;
  out = "";
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("[HttpClient] WiFi not connected");
    _busy = false;
    return false;
  }

  HTTPClient http;
  Serial.printf("[HttpClient] GET %s\n",url.c_str());

  if(!http.begin(url)){
    Serial.println("[HttpClient] begin failed");
    _busy = false;
    return false;
  }

  int code = http.GET();
  Serial.printf("[HttpClient] code %d\n", code);

  if(code != 200){
    http.end();
    _busy = false;
    return false;
  }
  out = http.getString();
  http.end();
  _busy= false;
  Serial.printf("[HttpClient] received %d bytes\n", out.length());
  return true;
}
