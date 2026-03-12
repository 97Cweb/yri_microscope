#include "DisplayService.h"
#include "../core/Microscope.h"
#include <Arduino.h>

bool DisplayService::begin(Microscope& m){
  Serial.println("[DisplayService] begin");

  if(_mainDisplay){
    lv_display_set_default(_mainDisplay);
    _mainScreen = lv_screen_active();
  }

  if(_menuDisplay){
    lv_display_set_default(_menuDisplay);
    _menuScreen = lv_screen_active();
  }

  Serial.printf("[DisplayService] mainDisplay=%p mainScreen=%p\n",
    (void*)_mainDisplay, (void*)_mainScreen);
  Serial.printf("[DisplayService] menuDisplay=%p menuScreen=%p\n",
    (void*)_menuDisplay, (void*)_menuScreen);
  return _mainDisplay != nullptr && _mainScreen != nullptr;
}

void DisplayService::update(Microscope& m){
  lv_timer_handler();
}

void DisplayService::setDisplays(lv_display_t* mainDisplay, lv_display_t* menuDisplay){
  _mainDisplay = mainDisplay;
  _menuDisplay = menuDisplay;
}

lv_display_t* DisplayService::mainDisplay() const{
  return _mainDisplay;
}

lv_display_t* DisplayService::menuDisplay() const{
  return _menuDisplay;
}

lv_obj_t* DisplayService::mainScreen() const{
  return _mainScreen;
}

lv_obj_t* DisplayService::menuScreen() const{
  return _menuScreen;
}
