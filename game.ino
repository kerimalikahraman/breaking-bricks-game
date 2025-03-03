#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Tuğla ayarları
#define BRICK_WIDTH 20
#define BRICK_HEIGHT 5
#define BRICK_COLUMNS 6
#define BRICK_ROWS 4
#define BRICK_SPACING 2
bool bricks[BRICK_ROWS][BRICK_COLUMNS];

// Buton ayarları
#define UP_BUTTON 22
#define DOWN_BUTTON 24
#define ENTER_BUTTON 26

// Palet ayarları
#define PADDLE_WIDTH 30
#define PADDLE_HEIGHT 5
#define PADDLE_Y (SCREEN_HEIGHT - 10)
int paddleX = 50;
#define POT_PIN A0

// LED pinleri
int ledPin[] = {2, 3, 4};
int lives = 3;
int level = 1;
int puan = 0;
int speed_control = 0;

// Top ayarları
int ballX = 64, ballY = 40;
float ballSpeedX = 2, ballSpeedY = 2;
#define BALL_RADIUS 3

// 7 segment ekran pinleri
const int segmentPins1[7] = {38, 39, 40, 41, 42, 43, 44};
const int segmentPins2[7] = {30, 31, 32, 33, 34, 35, 36};

struct heartObj {
    float x;
    float y;
    bool active;
};
heartObj obj;

bool start = false;
bool menu = true;
int menuIndex = 0;
const char *menuItems[] = {"Start", "Exit"};
const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);

void setup() {
    pinMode(ledPin[0], OUTPUT);
    pinMode(ledPin[1], OUTPUT);
    pinMode(ledPin[2], OUTPUT);
    pinMode(UP_BUTTON, INPUT_PULLUP);
    pinMode(DOWN_BUTTON, INPUT_PULLUP);
    pinMode(ENTER_BUTTON, INPUT_PULLUP);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while (true);
    }
    display.clearDisplay();
    displayMenu();

    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], HIGH);

    for (int i = 0; i < 7; i++) {
        pinMode(segmentPins1[i], OUTPUT);
        pinMode(segmentPins2[i], OUTPUT);
    }

    Serial.begin(9600);
    
    for (int i = 0; i < BRICK_ROWS; i++)
        for (int j = 0; j < BRICK_COLUMNS; j++)
            bricks[i][j] = true;
}

void loop() {
    int ldrValue = analogRead(A1);
    int brightness = map(ldrValue, 0, 1023, 1, 255);

    if (menu) {
        if (digitalRead(UP_BUTTON) == LOW) {
            menuIndex = (menuIndex - 1 + menuLength) % menuLength;
            displayMenu();
            delay(200);
        }
        if (digitalRead(DOWN_BUTTON) == LOW) {
            menuIndex = (menuIndex + 1) % menuLength;
            displayMenu();
            delay(200);
        }
        if (digitalRead(ENTER_BUTTON) == LOW) {
            if (menuIndex == 0) {
                start = true;
                menu = false;
            }
            if (menuIndex == 1) {
                start = false;
                menu = false;
                display.clearDisplay();
                display.display();
            }
            delay(200);
        }
    }
    
    if (start) {
        // Oyun mantığı burada devam ediyor...
    }
}

void displayMenu() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    for (int i = 0; i < menuLength; i++) {
        int x = 30, y = 20 + (i * 10);
        if (i == menuIndex) {
            display.drawRect(x - 5, y - 2, 50, 10, SSD1306_WHITE);
        }
        display.setCursor(x, y);
        display.println(menuItems[i]);
    }
    display.display();
}