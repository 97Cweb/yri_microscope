#pragma once

#include "../core/App.h"
#include "../ui/widgets/TextView.h"

class WikiApp : public App{
  public:
    const char* appId() const override {return "wiki";}

    bool begin(Microscope& m) override;
    void update(Microscope& m) override;

    void setTestText(const String& text);

  private:
    TextView _view;
    String _text = "Microscope wiki app";
    bool _created = false;
};
