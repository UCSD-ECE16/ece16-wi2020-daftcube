#define DAFT_DRAW_LIB false
#define OLED_ADVANCED true

void setup() {
  // put your setup code here, to run once:
  setupOled();
}

int t = 0;

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  t++;
  printToScreen(String(t));
}
