#pragma once
#include <Arduino.h>
#include <lvgl.h>

class TextView{
  public:
    TextView() = default;

    bool create(lv_obj_t* parent);
    void setText(const String& text);

    lv_obj_t* root() const;
    lv_obj_t* label() const;

  private:
    lv_obj_t* _root = nullptr;
    lv_obj_t* _label = nullptr;
};

