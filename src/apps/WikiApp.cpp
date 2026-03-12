#include "WikiApp.h"
#include "../core/Microscope.h"
#include "../device/DisplayService.h"
#include <Arduino.h>

bool WikiApp::begin(Microscope& m){
  Serial.println("[WikiApp] begin");
  return true;
}

void WikiApp::update(Microscope& m){
  if(_created) return;

  DisplayService* display = m.display();
  if(!display) return;

  lv_obj_t* screen = display->mainScreen();
  if(!screen) return;

  if(_view.create(screen)){
    _view.setText(_text);
    _created = true;
  }
}

void WikiApp::setTestText(const String& text){
  _text = text;
  if(_created){
    _view.setText(_text);
  }
}
