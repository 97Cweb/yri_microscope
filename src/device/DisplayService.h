#pragma once

#include "../core/Service.h"
#include <lvgl.h>

class Microscope;

class DisplayService : public Service{
  public:
    const char* serviceId() const override {return "display";}
    bool begin(Microscope& m) override;
    void update(Microscope& m) override;

    void setDisplays(lv_display_t* mainDisplay, lv_display_t* menuDisplay = nullptr);

    lv_display_t* mainDisplay() const;
    lv_display_t* menuDisplay() const;

    lv_obj_t* mainScreen() const;
    lv_obj_t* menuScreen() const;
  private:
    lv_display_t* _mainDisplay = nullptr;
    lv_display_t* _menuDisplay = nullptr;

    lv_obj_t* _mainScreen = nullptr;
    lv_obj_t* _menuScreen = nullptr;
};
