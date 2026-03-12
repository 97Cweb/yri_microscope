#include "Microscope.h"
#include "App.h"
#include "../device/DisplayService.h"

Microscope::Microscope(){

}

bool Microscope::begin(){
  if(_display && !_display->begin(*this)){
    return false;
  }

  if(_activeApp && !_activeApp->begin(*this)){
    return false;
  }

  return true;
}

void Microscope::update(){
  if(_display){
    _display->update(*this);
  }

  if(_activeApp){
    _activeApp->update(*this);
  }
}

void Microscope::setDisplayService(DisplayService* display){
  _display = display;
}

DisplayService* Microscope::display() const{
  return _display;
}

void Microscope::setActiveApp(App* app){
  _activeApp = app;
}

App* Microscope::activeApp() const {
  return _activeApp;
}
