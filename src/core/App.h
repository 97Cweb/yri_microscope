#pragma once

class App{
  public:
    virtual ~App() = default;
    virtual bool begin() = 0;
    virtual void update() = 0;
};
