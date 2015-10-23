//////////////////////////////////////////////////////////
//
// AQM0802A - http://akizukidenshi.com/catalog/g/gP-06669/
//
// How to use...
//
//   #include <Wire.h>
//
//   void setup() {
//     Wire.begin(5, 4);
//     aqm0802_init();
//     aqm0802_print("hello world");
//     delay(1000);
//   }
//   void loop() {}
//
#define AQM0802_ADDR 0x3e

void aqm0802_init() {
  // http://maicommon.ciao.jp/ss/Arduino_g/LCD_I2C/index.htm
  aqm0802_cmd(0x38);
  aqm0802_cmd(0x39);
  aqm0802_cmd(0x14);
  aqm0802_cmd(0x70);
  aqm0802_cmd(0x56);
  aqm0802_cmd(0x6c);

  aqm0802_cmd(0x38);
  aqm0802_cmd(0x0c);

  aqm0802_clear();
}

void aqm0802_clear() {
  aqm0802_cmd(0x01);
}

void aqm0802_print(char *str) {
  aqm0802_print(str, strlen(str));
}

void aqm0802_print(char *str, int len) {
  aqm0802_move_cursor(0, 0);

  if (str == NULL) {
    aqm0802_clear();
    return;
  }

  if (len == 0) {
    aqm0802_clear();
    return;
  }

  // for AQM0802 display size
  int char_count = len;
  if (char_count > 16) char_count = 16;

  // print character
  for (int i = 0; i < char_count; ++i) {
    aqm0802_char(str[i]);
    if (i  == 7) {
      aqm0802_move_cursor(0, 1);
    }
  }
}

void aqm0802_move_cursor(uint8_t x, uint8_t y) {
  if (y == 0) {
    aqm0802_cmd(0x80 + x);
  }
  else if (y == 1) {
    aqm0802_cmd(0xc0 + x);
  }
}

void aqm0802_cmd(char d) {
  aqm0802_data(0x00, d);
}

void aqm0802_char(char d) {
  aqm0802_data(0x40, d);
}

void aqm0802_data(char c, char d) {
  Wire.beginTransmission(AQM0802_ADDR);
  Wire.write(c);
  Wire.write(d);
  Wire.endTransmission();
  delayMicroseconds(20);
}

