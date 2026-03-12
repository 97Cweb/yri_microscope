#pragma once

class Microscope;

class Service{
  public:
    virtual ~Service() = default;

    virtual const char* serviceId() const = 0;

    virtual bool begin(Microscope& m) = 0;
    virtual void update(Microscope& m) {}
};
