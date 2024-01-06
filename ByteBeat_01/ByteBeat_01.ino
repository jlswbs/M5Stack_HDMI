// Byte-Beat video synthesizer //

#include <M5ModuleDisplay.h>
#include <M5Unified.h>

#define WIDTH   512
#define HEIGHT  128

  long t, col;
  int16_t raw_data[WIDTH];
  uint16_t color;

void setup() {

  srand(time(NULL));

  auto cfg = M5.config();

  cfg.external_speaker.module_display = true;
  cfg.external_display.module_display = true;
  cfg.module_display.logical_width = WIDTH;
  cfg.module_display.logical_height = HEIGHT;
  cfg.module_display.refresh_rate = 60;

  M5.begin(cfg);

  M5.Display.clear(BLACK);
  M5.Display.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Display.drawString("ByteBeat video synthesizer", 5, 20);

  M5.setPrimaryDisplayType(m5gfx::board_M5ModuleDisplay);
  M5.Display.clear(TFT_BLACK);

}

void loop(void) {

  color = esp_random();

  for (int y = 0; y < HEIGHT; ++y) {

    for (int x = 0; x < WIDTH; ++x){

      col = (t^t>>10)-(t|t>>9);

      M5.Display.drawPixel(col%WIDTH, y, color);
      raw_data[x] = (int16_t)(16*col);

      t = t + 4;

    }

    M5.Speaker.playRaw(raw_data, WIDTH, 48000, false, 1, -1, false);

  }

}