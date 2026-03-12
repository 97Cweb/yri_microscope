#pragma once

class Microscope;

class App{
  public:
    virtual ~App() = default;

    virtual const char* appId() const = 0;

    virtual bool begin(Microscope& m) = 0;
    virtual void update(Microscope& m) = 0;

    virtual void onActivate(Microscope& m){}
    virtual void onDeactivate(Microscope& m){}
};
