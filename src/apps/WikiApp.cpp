#include "WikiApp.h"
#include "../core/Microscope.h"
#include "../device/DisplayService.h"
#include "../util/TextUtil.h"

#include <Arduino.h>

bool WikiApp::begin(Microscope& m){
  Serial.println("[WikiApp] begin");
  return true;
}

void WikiApp::update(Microscope& m){
  if(_created){
    return;
  }

  DisplayService* display = m.display();
  Serial.printf("[WikiApp] display=%p\n",(void*)display);

  if(!display) return;

  lv_obj_t* screen = display->mainScreen();

  Serial.printf("[WikiApp] mainScreen=%p\n",(void*)screen);
  if(!screen) return;

  if(!_loaded){
    Serial.println("[WikiApp] loading");

    String text;

    if(_http.getText("https://simple.yri.ca/beeton/reason", text)){
      Serial.println("[WikiApp] HTTP ok");
      _text = TextUtil::toAscii(text);
    }
    else{
      Serial.println("[WikiApp] HTTP failed");
      _text = "HTTP FAILED";
    }
    _loaded = true;
  }

  if(_view.create(screen)){
    Serial.println("[WikiApp] view created");
    _view.setText(_text);
    _created = true;
  }
  else{
    Serial.println("[WikiApp] view create failed");
  }
}

void WikiApp::setTestText(const String& text){
  _text = TextUtil::toAscii(text);
  if(_created){
    _view.setText(_text);
  }
}
