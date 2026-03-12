#include "TextView.h"

bool TextView::create(lv_obj_t* parent){
  if(!parent) return false;

  _root = lv_obj_create(parent);
  lv_obj_set_size(_root, lv_pct(100),lv_pct(100));

  _label = lv_label_create(_root);
  lv_obj_set_width(_label,lv_pct(100));
  lv_label_set_long_mode(_label, LV_LABEL_LONG_WRAP);
  lv_obj_align(_label, LV_ALIGN_TOP_LEFT,0,0);

  return _label != nullptr;
}

void TextView::setText(const String& text){
  if(_label){
    lv_label_set_text(_label,text.c_str());
  }
}

lv_obj_t* TextView::root() const{
  return _root;
}

lv_obj_t* TextView::label() const{
  return _label;
}
