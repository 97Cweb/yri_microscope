#pragma once

class Service{
  public:
    virtual ~Service() = default;

    virtual bool begin() = 0;
    virtual void update() {}
};
