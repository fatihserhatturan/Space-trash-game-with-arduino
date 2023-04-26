#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <Adafruit_SSD1306.h>


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#include <Fonts/FreeSans9pt7b.h>
//#include <Fonts/FreeSans12pt7b.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);



#include "Wire.h"
#define LATCH 4
#define CLK 3
#define DATA 2

byte digit[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F}; 

const byte potPin = A1;
int val = 0;
int sayac = 0;
const unsigned char PROGMEM dioda16 [] = {

0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x3F, 0xF0, 0x3C, 0x00, 0x3C, 0x00, 0xFF, 0x00, 0x7F, 0xFF,
0x7F, 0xFF, 0xFF, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x1F, 0xF0, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00

};


void setup()   {

    pinMode(LATCH, OUTPUT);
    pinMode(CLK, OUTPUT);
    pinMode(DATA, OUTPUT);
    pinMode(A0, INPUT);
    pinMode(8, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(13, OUTPUT);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    display.clearDisplay();
    display.setFont(&FreeSans9pt7b);
    display.setTextColor(WHITE);
    display.setFont();
    display.setCursor(0, 0);
    display.setFont(&FreeSans9pt7b);
    display.setFont();
    Serial.begin(9600);
    display.display();
}
int metx = 0; // metalik x koordinatı
int mety = 0; // metalik y koordinatı
int hasWeapon = 0; // metalik var mı?
int enemyCount = 8; // düşman sayısı
int direction = 0; // hareket yönü
int go = 0; // gitmek
int rx = 95; // x koordinatı
int ry = 0; // y koordinatı
int rx2 = 95; // ikinci x koordinatı
int ry2 = 0; // ikinci y koordinatı
int rx3 = 95; // üçüncü x koordinatı
int ry3 = 0; // üçüncü y koordinatı
int totalPoints = 0; // toplam puan
int bulletSpeed = 1; // mermi hızı
int bulletCount = 1; // mermi sayısı
int bulletDiameter = 10; // mermi çapı
int rx4 = 95; // dördüncü x koordinatı
int ry4 = 0; // dördüncü y koordinatı
int lives = 3; // can sayısı
int start = 0; // başlama
int bulletsFired = 0; // atılan mermi sayısı
int level = 1; // seviye
int center = 95; // merkez
unsigned long startTime = 0; // başlangıç zamanı
unsigned long selectedTime = 0; // seçilen süre
unsigned long currentTime = 0; // şu anki zaman
int position = 30; // pozisyon
int count = 0;
int prevBulletsFired = 0;
int prevVal = 0;
int LDRValue;
int currentPage = 2;
int i = 20;
int end = 0;
int temporary = 1;
int difficulty = 0;
int weapon = 4;
int invulnerability = 0;
int seconds = 0;
int prevSeconds = 0;
int meteorLive = 2;
boolean button = false;
int prevSeconds2 = 0;
int score = 0;
int ones = 0;
int tens = 0;
int hundreds = 0;
int seconds3;
void updateDisplay() {
    display.display();
    display.clearDisplay();
}

void drawProlab2Screen() {
    display.setTextSize(0);
    display.setFont(&FreeSans9pt7b);
    display.setTextColor(WHITE);
    display.setCursor(65, 14);
    display.println("prolab2");
    display.setFont();
    display.setCursor(65, 17);
    display.setTextSize(0);
    display.println("space");
    display.setCursor(0, 0);
    display.setFont(&FreeSans9pt7b);
    display.setCursor(65, 39);
    display.println("trash");
    display.setFont();
    display.setCursor(65, 42);
    display.println("game  ");
    display.setTextSize(0);
    display.setCursor(65, 55);

    if (seconds3 % 2 == 0) {
        display.println("oyuna gir : ");
    }

    display.setFont();
    display.setCursor(5, 5);
    display.setTextSize(1);
    display.println("cop:");
    display.drawCircle(50, 9, 1, 1);
    display.setFont();
    display.setCursor(5, 15);
    display.setTextSize(1);
    display.println("meteor:");
    display.drawCircle(50, 19, 2, 1);
    display.setFont();
    display.setCursor(5, 25);
    display.setTextSize(1);
    display.println("d.maz:");
    display.drawCircle(50, 29, 3, 1);
    display.setFont();
    display.setCursor(5, 35);
    display.setTextSize(1);
    display.println("can:");
    display.drawCircle(50, 39, 4, 1);

    updateDisplay();
}

void drawDifficultyScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(15, 0);
    display.println("ZORLUK");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 20);
    display.println("KOLAY");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 30);
    display.println("ZOR");
    display.setCursor(0, i);
    display.print(">");

    updateDisplay();
}

void loop() {
    LDRValue = analogRead(A0);
    display.invertDisplay(LDRValue <= 512);
    Serial.println(LDRValue);

    if (currentPage == 2) {
        seconds3 = millis() / 400;
        drawProlab2Screen();
        secim2();
    }

    if (currentPage == 1) {
        drawDifficultyScreen();

        if (sayac == 10000 || (digitalRead(12) == 1 || digitalRead(8)) && sayac > 5) {
            yon();
            secim();
        }

        sayac++;
    }

    if (currentPage == 0) {
       oyun();
    }
}//void loop() fonksiyonunun bitişi
void oyun(){
     currentTime = 0;
        seconds = millis() / 1000 - score;
        ones = seconds % 10;
        tens = (seconds % 100) / 10;
        hundreds = seconds / 100;
        digitalWrite(LATCH, LOW);
        shiftOut(DATA, CLK, MSBFIRST, ~digit[ones]);
        shiftOut(DATA, CLK, MSBFIRST, ~digit[tens]);
        shiftOut(DATA, CLK, MSBFIRST, ~digit[hundreds]);
        digitalWrite(LATCH, HIGH);

        /////////////////////////////////////////////////////////////////////////////////
        if (lives > 3) {
            lives = 3;
        }
        ///////////////////////////////////////////////////////////////////////////////
        if (lives != 0)
        {
            if (lives == 1) {
                digitalWrite(5, HIGH);
                digitalWrite(6, LOW);
                digitalWrite(7, LOW);
            }
            if (lives == 2) {
                digitalWrite(5, HIGH);
                digitalWrite(6, HIGH);
                digitalWrite(7, LOW);
            }
            if (lives == 3) {
                digitalWrite(5, HIGH);
                digitalWrite(6, HIGH);
                digitalWrite(7, HIGH);
            }
        }
        /////////////////////////////////////////////////////////////////////////////////

        if (weapon == 0) {
            digitalWrite(11, LOW);
            digitalWrite(13, LOW);
            digitalWrite(10, LOW);
        }
        if (weapon == 1) {
            digitalWrite(11, HIGH);
            digitalWrite(13, LOW);
            digitalWrite(10, LOW);
        }
        if (weapon == 2) {
            digitalWrite(11, HIGH);
            digitalWrite(13, HIGH);
            digitalWrite(10, LOW);
        }
        if (weapon == 3) {
            digitalWrite(11, HIGH);
            digitalWrite(13, HIGH);
            digitalWrite(10, HIGH);
        }
        ////////////////////////////////////////////////////////////////////////////////
        val = analogRead(potPin);
        /////////////////////////////////////////////////////////////////////////////////
        if (go == 0) {


            if (difficulty == 1) {

                // bulletSpeed=9;

                if (seconds >= 5 && seconds % 5 == 0 && seconds != prevSeconds2) {
                    bulletSpeed = bulletSpeed + 2;

                }

            }

            prevSeconds2 = seconds;
            Serial.println(bulletSpeed);
            display.clearDisplay();


            display.drawPixel(50, 30, 1);
            display.drawPixel(30, 17, 1);
            display.drawPixel(60, 18, 1);
            display.drawPixel(55, 16, 1);
            display.drawPixel(25, 43, 1);
            display.drawPixel(100, 43, 1);
            display.drawPixel(117, 52, 1);
            display.drawPixel(14, 49, 1);
            display.drawPixel(24, 24, 1);
            display.drawPixel(78, 36, 1);
            display.drawPixel(80, 57, 1);
            display.drawPixel(107, 11, 1);
            display.drawPixel(150, 11, 1);
            display.drawPixel(5, 5, 1);
            display.drawPixel(8, 7, 1);
            display.drawPixel(70, 12, 1);
            display.drawPixel(10, 56, 1);
            display.drawPixel(70, 25, 1);



            if (start == 0) {
                startTime = millis();
                selectedTime = random(400, 1200);
                start = 1;
            }
            currentTime = millis();


            if ((selectedTime + startTime) < currentTime)
            {
                start = 0;
                bulletsFired = bulletsFired + 1;
                if (bulletsFired == 1)
                { rx = 95;
                    ry = enemyCount;
                }
                if (bulletsFired == 2) {
                    rx2 = 95;
                    ry2 = enemyCount;
                }
                if (bulletsFired == 3)
                {
                    rx3 = 95;
                    ry3 = enemyCount;
                }


                if (bulletsFired == 4) {
                    rx4 = 95;
                    ry4 = enemyCount;

                }



            }


            if (bulletsFired > 0)
            {
                display.drawCircle(rx, ry, 2, 1);
                rx = rx - bulletSpeed;

            }

            if (bulletsFired > 1)
            {
                display.drawCircle(rx2, ry2, 1, 1);
                rx2 = rx2 - bulletSpeed;

            }

            if (bulletsFired > 2)
            {
                display.drawCircle(rx3, ry3, 4, 1);
                rx3 = rx3 - bulletSpeed;

            }

            if (bulletsFired > 3)
            {
                display.drawCircle(rx4, ry4, 2, 1);
                rx4 = rx4 - bulletSpeed;

            }


            if (val > prevVal && position >= 2) {
                position = position - 2;
            }

            if (val < prevVal && position <= 46) {
                position = position + 2;
            }
            //////////////////////////////////////////////////////

            //////////////////////////////////////////////////////
            if (count >= 10 && count % 10 == 0 && prevBulletsFired != bulletsFired) {
                lives++;
                weapon++;
            }

            if (weapon > 3) {
                weapon = 3;
            }


            if (digitalRead(8) == 0 && hasWeapon == 0 && weapon != 0 && (seconds)>0)
            {
                weapon--;
                hasWeapon = 1;
                metx = 6;
                mety = position + 8;
                tone(9, 1200, 20);


            }
            if (hasWeapon == 1)

            {
                metx = metx + 8 ;

                display.drawLine(metx, mety, metx + 4, mety, 1);
            }

            display.drawBitmap(4, position, dioda16, 16, 16, 1);

            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(33, 57);
            display.println("score:");
            display.setCursor(68, 57);
            display.println(totalPoints);

            display.setCursor(33, 0);
            display.println("lives:");
            display.setCursor(68, 0);
            display.println(lives);

            display.setCursor(110, 0);
            display.println("L:");

            display.setCursor(122, 0);
            display.println(level);

            display.setCursor(108, 57);
            display.println(currentTime / 1000);
            display.display();
            //////////////////////////////////////////////////////////
            //Serial.println(prevSeconds);
            seconds = (millis() / 1000);

            if (seconds - prevSeconds >= 3)
            {
                invulnerability = 0;
            }
            //////////////////////////////////////////////////////////
            if (metx > 128)hasWeapon = 0;



            if (direction == 0) {
                enemyCount = enemyCount + bulletCount;
            }
            else
            {
                enemyCount = enemyCount - bulletCount;
            }

            if (enemyCount >= (64 - bulletDiameter))
                direction = 1;
            if (enemyCount <= bulletDiameter)
                direction = 0;

            //////////////////////////////////////////////////////////////////////////ATEŞ SONRASI VURUŞ FONKSİYONU
            if (mety >= enemyCount - bulletDiameter && mety <= enemyCount + bulletDiameter)
                if (metx > (center - bulletDiameter) && metx < (center + bulletDiameter))
                {
                    metx = -20;

                    totalPoints = totalPoints + 1;
                    hasWeapon = 0;
                }
            ///////////////////////////////////////////////////////////////////////////
            if (mety >= ry - 8 && mety <= ry + 8 && metx >= rx - 8 && metx <= rx + 8 )
            {
                meteorLive--;
                if (meteorLive == 0)
                {
                    rx = -50;
                    ry = -50;
                    meteorLive = 2;
                    tone(9, 100, 100);
                }

            }

            if (mety >= ry2 - 8 && mety <= ry2 + 8 && metx >= rx2 - 8 && metx <= rx2 + 8 )
            {
                rx2 = -50;
                ry2 = -50;
                tone(9, 100, 100);
            }
            //////////////////////////////////////////////////////////////////////////
            int currposition = position + 8;
            if (ry >= currposition - 8 && ry <= currposition + 8 && invulnerability == 0)
                if (rx < 12 && rx > 4)
                {
                    rx = 95;
                    ry = -50;
                    tone(9, 100, 100);
                    lives = lives - 1;
                }

            if (ry2 >= currposition - 8 && ry2 <= currposition + 8 && invulnerability == 0)
                if (rx2 < 12 && rx2 > 4)
                {
                    rx2 = -50;
                    ry2 = -50;
                    tone(9, 100, 100);
                    lives = lives - 1;
                }

            if (ry3 >= currposition - 8 && ry3 <= currposition + 8)
                if (rx3 < 12 && rx3 > 4)
                {
                    rx3 = -50;
                    ry3 = -50;
                    tone(5, 100, 100);
                    invulnerability = 1;
                    prevSeconds = seconds;
                    lives = lives;
                }

            if (ry4 >= currposition - 8 && ry4 <= currposition + 8)
                if (rx4 < 12 && rx4 > 4)
                {
                    rx4 = 200;
                    ry4 = -50;

                    bulletsFired = 0;
                    tone(5, 100, 100);
                    lives = lives + 1;
                }

            if (rx4 < 1) {

                bulletsFired = 0;
                rx4 = 200;
            }

            if (lives == 0)

                currentPage = 2;
        }
        ///////////////////////////////////////////
        if (prevBulletsFired != bulletsFired && bulletsFired >> 0)
        {
            count++;
        }
        //////////////////////////////////////////
        prevBulletsFired = bulletsFired;
        prevVal = val;
}
void yon() {
    int a = digitalRead(12);
    if (a == 0) {
        temporary = 0;
    }
    if (a == 1 && temporary == 0) {
        end = 1;
        button = true;
    }
    if (end == 1 && button == true)
    {
        temporary = 1;
        display.clearDisplay();
        display.display();
        i = i + 10;
        button = false; end = 0;

        if (i > 30)
        {
            i = 20;
        }
    }
}
void secim() {
    int b = digitalRead(8);
    if (b == 0 && i == 20 && currentPage == 1) {
        currentPage = 0;

    }
    if (b == 0 && i == 30 && currentPage == 1) {
        currentPage = 0;
        difficulty = 1;
        score = millis() / 1000;
    }


}
void secim2() {
    int b = digitalRead(8);
    if (b == 0) {
        currentPage = 1;
        score = millis() / 1000;
    }
}
