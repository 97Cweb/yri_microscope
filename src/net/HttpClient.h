#pragma once
#include <Arduino.h>

class HttpClient{
  public:
    HttpClient();
    bool getText(const String& url, String& out);
  private:
    bool _busy = false;
};

