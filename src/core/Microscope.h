#pragma once

class DisplayService;
//class NetworkService;
//class StorageService;
class App;
//class Service;

class Microscope{
  public:
    Microscope();

    bool begin();
    void update();

    void setDisplayService(DisplayService* display);
    DisplayService* display() const;

    void setActiveApp(App* app);
    App* activeApp() const;

   // bool registerApp(&App);
   // bool registerService(&Service);

  private:
    DisplayService* _display = nullptr;
    App* _activeApp = nullptr;
};
