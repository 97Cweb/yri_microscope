#pragma once

struct MicroscopeMainDisplayConfig{
  int width;
  int height;
  int rotation;
};

struct MicroscopeMenuDisplayConfig{
  int width;
  int height;
  int rotation;
};

struct MicroscopeBoardConfig{
  MicroscopeMainDisplayConfig mainDisplay;
  MicroscopeMenuDisplayConfig menuDisplay;
};
