#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_ST7789.h>
#include <lvgl.h>
#include <WiFi.h>

#include <yri_microscope.h>
#include "secrets_local.h"

//SPI pins

#define TFT_SCK 12
#define TFT_MOSI 11

//Big screen = MAIN
#define BIG_CS  10
#define BIG_DC  9
#define BIG_RST 6

//mini screen = MENU
#define MINI_CS  14
#define MINI_DC  8
#define MINI_RST 5

Adafruit_ILI9341 mainTft(BIG_CS, BIG_DC, BIG_RST);
Adafruit_ST7789  menuTft(MINI_CS, MINI_DC, MINI_RST);

//resolutions

#define MAIN_HOR_RES 320
#define MAIN_VER_RES 240

#define MENU_HOR_RES 240
#define MENU_VER_RES 240

// ===== LVGL draw buffers =====
static uint16_t draw_buf_main[MAIN_HOR_RES * 40];
static uint16_t draw_buf_menu[MENU_HOR_RES * 40];

static lv_display_t* disp_main = nullptr;
static lv_display_t* disp_menu = nullptr;

Microscope microscope;
DisplayService displayService;
WikiApp wikiApp;

#if LV_USE_LOG != 0
  void my_print(lv_log_level_t level, const char* buf){
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
  }
#endif

inline void deselectMain() { digitalWrite(BIG_CS, HIGH); }
inline void deselectMenu() { digitalWrite(MINI_CS, HIGH); }

void flush_main(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map) {
  deselectMenu();

  const uint32_t w = (area->x2 - area->x1 + 1);
  const uint32_t h = (area->y2 - area->y1 + 1);
  uint16_t * pix = (uint16_t *)px_map;

  mainTft.startWrite();
  mainTft.setAddrWindow(area->x1, area->y1, w, h);
  mainTft.writePixels(pix, w * h, true);
  mainTft.endWrite();

  lv_display_flush_ready(disp);
}

void flush_menu(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map) {
  deselectMain();

  const uint32_t w = (area->x2 - area->x1 + 1);
  const uint32_t h = (area->y2 - area->y1 + 1);
  uint16_t * pix = (uint16_t *)px_map;

  menuTft.startWrite();
  menuTft.setAddrWindow(area->x1, area->y1, w, h);
  menuTft.writePixels(pix, w * h, true);
  menuTft.endWrite();

  lv_display_flush_ready(disp);
}

static uint32_t my_tick(void) {
  return millis();
}


static void createMenuStatusUi() {
  if (!disp_menu) return;

  lv_display_set_default(disp_menu);

  lv_obj_t* label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "Menu\nready");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

static void initBoardDisplayAndLvgl() {
  pinMode(BIG_CS, OUTPUT);
  pinMode(MINI_CS, OUTPUT);
  deselectMain();
  deselectMenu();

  SPI.begin(TFT_SCK, -1, TFT_MOSI);

  mainTft.begin();
  mainTft.setRotation(3);
  mainTft.setSPISpeed(8000000);

  menuTft.init(MENU_HOR_RES, MENU_VER_RES);
  menuTft.setRotation(3);
  menuTft.invertDisplay(true);
  menuTft.setSPISpeed(8000000);

  lv_init();
  lv_tick_set_cb(my_tick);

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print);
#endif

  disp_main = lv_display_create(MAIN_HOR_RES, MAIN_VER_RES);
  lv_display_set_flush_cb(disp_main, flush_main);
  lv_display_set_buffers(
    disp_main,
    draw_buf_main,
    NULL,
    sizeof(draw_buf_main),
    LV_DISPLAY_RENDER_MODE_PARTIAL
  );

  disp_menu = lv_display_create(MENU_HOR_RES, MENU_VER_RES);
  lv_display_set_flush_cb(disp_menu, flush_menu);
  lv_display_set_buffers(
    disp_menu,
    draw_buf_menu,
    NULL,
    sizeof(draw_buf_menu),
    LV_DISPLAY_RENDER_MODE_PARTIAL
  );
}

void connectWifi(){
  const char* ssid = WIFI_SSID;
  const char* pass = WIFI_PASS;

  Serial.println("Connecting WiFi...");
  WiFi.begin(ssid,pass);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}


void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println();
    Serial.println("Microscope dual-screen test starting...");
    
    connectWifi();

    initBoardDisplayAndLvgl();

    createMenuStatusUi();

    wikiApp.setTestText(
      "Microscope main display test\n\n"
      "This is the main screen.\n\n"
      "Soon this will show fetched markdown from simple.yri.ca.\n\n"
      "- DisplayService wired\n"
      "- WikiApp wired\n"
      "- TextView wired"
    );
    displayService.setDisplays(disp_main, disp_menu);
    microscope.setDisplayService(&displayService);
    microscope.setActiveApp(&wikiApp);

    if (!microscope.begin()) {
        Serial.println("Microscope begin failed");
        while (true) {
            delay(1000);
        }
    }

    Serial.println("Microscope begin ok");
}

void loop() {
    microscope.update();
    delay(5);
}
