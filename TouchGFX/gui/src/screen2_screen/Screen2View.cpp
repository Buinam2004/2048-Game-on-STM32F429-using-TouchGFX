#include <gui/screen2_screen/Screen2View.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include<math.h>
#include <random>
extern "C" {
#include "main.h"
}
#include <touchgfx/Color.hpp>
using namespace touchgfx;
Unicode::UnicodeChar buff[4][4][20];
Unicode::UnicodeChar score[20];
extern int JoytickX;
extern int JoytickY;
int value;
int isStop=1;
int point=0;
int arr[4][4]= {
    {0,0,0,0},
    {0,0,0,0},
    {0,4,2,0},
    {0,0,0,0}
}; 

int r[2]={2,4};
unsigned int seed = (unsigned int)time(NULL);

touchgfx::colortype getTileBgColor(int v) {
    switch (v) {
        case 2:    return touchgfx::Color::getColorFromRGB(230, 230, 250);
        case 4:    return touchgfx::Color::getColorFromRGB(173, 216, 230);
        case 8:    return touchgfx::Color::getColorFromRGB(144, 238, 144);
        case 16:   return touchgfx::Color::getColorFromRGB(102, 51, 153);
        case 32:   return touchgfx::Color::getColorFromRGB(34, 139, 34);
        case 64:   return touchgfx::Color::getColorFromRGB(0, 104, 139);
        case 128:  return touchgfx::Color::getColorFromRGB(138, 43, 226);
        case 256:  return touchgfx::Color::getColorFromRGB(0, 191, 255);
        case 512:  return touchgfx::Color::getColorFromRGB(50, 205, 50);
        case 1024: return touchgfx::Color::getColorFromRGB(25, 25, 112);
        case 2048: return touchgfx::Color::getColorFromRGB(75, 0, 130);
        default:   return touchgfx::Color::getColorFromRGB(204, 192, 179);
    }
}

int randInRange(unsigned int seed, int min, int max) {
    static std::mt19937 rng(std::random_device{}());  // Chỉ khởi tạo 1 lần với seed từ random_device
    std::uniform_int_distribution<int> dist(min, max);     // Sinh số nguyên từ 1 đến 4 (bao gồm)
    return dist(rng);
}
int pushLeft(int a[4][4]) {
    int result = 0;
    int b[4], k;
    for (int i = 0; i < 4; i++) {
        k = 0;
        for (int j = 0; j < 4; j++) {
            if (a[i][j] != 0) b[k++] = a[i][j];
        }
        for (int j = k; j < 4; j++) b[j] = 0;
        for (int j = 0; j < 4; j++) {
            if (a[i][j] != b[j]) result = 1;
            a[i][j] = b[j];
        }
    }
    return result;
}

int leftAction(int a[4][4], unsigned int seed) {
    int core=0;
    int r1 = pushLeft(a);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] == a[i][j + 1]) {
                core+=2*a[i][j];
                a[i][j] += a[i][j + 1];
                a[i][j + 1] = 0;
            }
        }
    }
    int r2 = pushLeft(a);
    if (r1 || r2) {
        int c[16], k = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 2; j < 4; j++) {
                if (a[i][j] == 0) c[k++] = i * 4 + j;
            }
        }
        if (k > 0) {
            int h = c[randInRange(seed, 0, k - 1)];
            a[h / 4][h % 4] = r[(randInRange(seed + 1, 0, 7)>6?1:0)];
        }
    }
    return core;
}
int pushRight(int a[4][4]) {
    int result = 0;
    int b[4], k;
    for (int i = 0; i < 4; i++) {
        k = 3;
        for (int j = 3; j >= 0; j--) {
            if (a[i][j] != 0) b[k--] = a[i][j];
        }
        for (int j = k; j >= 0; j--) b[j] = 0;
        for (int j = 0; j < 4; j++) {
            if (a[i][j] != b[j]) result = 1;
            a[i][j] = b[j];
        }
    }
    return result;
}

int rightAction(int a[4][4], unsigned int seed) {
    int core=0;
    int r1 = pushRight(a);
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) {
            if (a[i][j] == a[i][j - 1]) {
                core+=2*a[i][j];
                a[i][j] += a[i][j - 1];
                a[i][j - 1] = 0;
            }
        }
    }
    int r2 = pushRight(a);
    if (r1 || r2) {
        int c[16], k = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
                if (a[i][j] == 0) c[k++] = i * 4 + j;
            }
        }
        if (k > 0) {
            int h = c[randInRange(seed, 0, k - 1)];
            a[h / 4][h % 4] = r[(randInRange(seed + 1, 0, 7)>6?1:0)];
        }
    }
    return core;
}
int pushUp(int a[4][4]) {
    int result = 0;
    int b[4], k;
    for (int i = 0; i < 4; i++) {
        k = 0;
        for (int j = 0; j < 4; j++) {
            if (a[j][i] != 0) b[k++] = a[j][i];
        }
        for (int j = k; j < 4; j++) b[j] = 0;
        for (int j = 0; j < 4; j++) {
            if (a[j][i] != b[j]) result = 1;
            a[j][i] = b[j];
        }
    }
    return result;
}

int upAction(int a[4][4], unsigned int seed) {
    int core=0;
    int r1 = pushUp(a);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[j][i] == a[j + 1][i]) {
                core+=2*a[j][i];
                a[j][i] += a[j + 1][i];
                a[j + 1][i] = 0;
            }
        }
    }
    int r2 = pushUp(a);
    if (r1 || r2) {
        int c[16], k = 0;
        for (int i = 2; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (a[i][j] == 0) c[k++] = i * 4 + j;
            }
        }
        if (k > 0) {
            int h = c[randInRange(seed, 0, k - 1)];
            a[h / 4][h % 4] = r[(randInRange(seed + 1, 0, 7)>6?1:0)];
        }
    }
    return core;
}
int pushDown(int a[4][4]) {
    int result = 0;
    int b[4], k;
    for (int i = 0; i < 4; i++) {
        k = 3;
        for (int j = 3; j >= 0; j--) {
            if (a[j][i] != 0) b[k--] = a[j][i];
        }
        for (int j = k; j >= 0; j--) b[j] = 0;
        for (int j = 0; j < 4; j++) {
            if (a[j][i] != b[j]) result = 1;
            a[j][i] = b[j];
        }
    }
    return result;
}

int downAction(int a[4][4], unsigned int seed) {
    int core=0;
    int r1 = pushDown(a);
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) {
            if (a[j][i] == a[j - 1][i]) {
                core+=2*a[j][i];
                a[j][i] += a[j - 1][i];
                a[j - 1][i] = 0;
            }
        }
    }
    int r2 = pushDown(a);
    if (r1 || r2) {
        int c[16], k = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                if (a[i][j] == 0) c[k++] = i * 4 + j;
            }
        }
        if (k > 0) {
            int h = c[randInRange(seed, 0, k - 1)];
            a[h / 4][h % 4] = r[(randInRange(seed + 1, 0, 7)>6?1:0)];
        }
    }
    return core;
}
int isFinish(int a[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (a[i][j] == 0) return 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j < 3 && a[i][j] == a[i][j + 1]) return 0;
            if (i < 3 && a[i][j] == a[i + 1][j]) return 0;
        }
    }
    return 1;
}

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    point=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            arr[i][j]=0;
        }
    }
    int h = randInRange(seed, 0, 15);
    arr[h / 4][h % 4] = r[(randInRange(seed + 1, 0, 1))];
    h = randInRange(seed+2, 0, 15);
    arr[h / 4][h % 4] = r[(randInRange(seed + 3, 0, 1))];
    Show();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}
void Screen2View::handleTickEvent()
{
    Screen2ViewBase::handleTickEvent();
    if(JoytickX<150&&JoytickY<150&&JoytickX>100&&JoytickY>100) isStop=0;
    if(isStop==1) return;
    if(JoytickX>150&&JoytickY<150&&JoytickY>100){
    		Right();
    		isStop=1;
    	} else if(JoytickX<100&&JoytickY<150&&JoytickY>100){
    		Left();
    		isStop=1;
    	} else if(JoytickY>150&&JoytickX<150&&JoytickX>100){
    		Bottom();
    		isStop=1;
    	} else if(JoytickY<100&&JoytickX<150&&JoytickX>100){
    		Top();
    		isStop=1;
    	}
}
void Screen2View::Left(){
    point += leftAction(arr,seed);
    Show();
}
void Screen2View::Right(){
    point += rightAction(arr,seed);
    Show();
}
void Screen2View::Top(){
    point += upAction(arr,seed);
    Show();
}

void Screen2View::Bottom(){
    point += downAction(arr,seed);
    Show();
}

void Screen2View::Show()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            memset(buff[i][j], 0, sizeof(buff[i][j]));

            // Gọi tên TextArea và Box theo đúng Screen2ViewBase
            #define TILE(i,j) tile_##i##_##j
            #define TILE_BG(i,j) tile_##i##_##j##_bg

            colortype bg = getTileBgColor(arr[i][j]);

            // Cập nhật text
            if (arr[i][j] == 0) {
                Unicode::snprintf(buff[i][j], sizeof(buff[i][j]) / sizeof(Unicode::UnicodeChar), " ");
            } else if (arr[i][j] >= 1024) {
                Unicode::snprintf(buff[i][j], sizeof(buff[i][j]) / sizeof(Unicode::UnicodeChar), "2e10");
            } else {
                Unicode::snprintf(buff[i][j], sizeof(buff[i][j]) / sizeof(Unicode::UnicodeChar), "%d", arr[i][j]);
            }

            // Truy cập biến tile và tile_bg theo macro
            switch (i * 4 + j) {
                case 0:  TILE(0,0).setWildcard(buff[i][j]);  TILE(0,0).invalidate();  TILE_BG(0,0).setColor(bg);  TILE_BG(0,0).invalidate(); break;
                case 1:  TILE(0,1).setWildcard(buff[i][j]);  TILE(0,1).invalidate();  TILE_BG(0,1).setColor(bg);  TILE_BG(0,1).invalidate(); break;
                case 2:  TILE(0,2).setWildcard(buff[i][j]);  TILE(0,2).invalidate();  TILE_BG(0,2).setColor(bg);  TILE_BG(0,2).invalidate(); break;
                case 3:  TILE(0,3).setWildcard(buff[i][j]);  TILE(0,3).invalidate();  TILE_BG(0,3).setColor(bg);  TILE_BG(0,3).invalidate(); break;
                case 4:  TILE(1,0).setWildcard(buff[i][j]);  TILE(1,0).invalidate();  TILE_BG(1,0).setColor(bg);  TILE_BG(1,0).invalidate(); break;
                case 5:  TILE(1,1).setWildcard(buff[i][j]);  TILE(1,1).invalidate();  TILE_BG(1,1).setColor(bg);  TILE_BG(1,1).invalidate(); break;
                case 6:  TILE(1,2).setWildcard(buff[i][j]);  TILE(1,2).invalidate();  TILE_BG(1,2).setColor(bg);  TILE_BG(1,2).invalidate(); break;
                case 7:  TILE(1,3).setWildcard(buff[i][j]);  TILE(1,3).invalidate();  TILE_BG(1,3).setColor(bg);  TILE_BG(1,3).invalidate(); break;
                case 8:  TILE(2,0).setWildcard(buff[i][j]);  TILE(2,0).invalidate();  TILE_BG(2,0).setColor(bg);  TILE_BG(2,0).invalidate(); break;
                case 9:  TILE(2,1).setWildcard(buff[i][j]);  TILE(2,1).invalidate();  TILE_BG(2,1).setColor(bg);  TILE_BG(2,1).invalidate(); break;
                case 10: TILE(2,2).setWildcard(buff[i][j]);  TILE(2,2).invalidate();  TILE_BG(2,2).setColor(bg);  TILE_BG(2,2).invalidate(); break;
                case 11: TILE(2,3).setWildcard(buff[i][j]);  TILE(2,3).invalidate();  TILE_BG(2,3).setColor(bg);  TILE_BG(2,3).invalidate(); break;
                case 12: TILE(3,0).setWildcard(buff[i][j]);  TILE(3,0).invalidate();  TILE_BG(3,0).setColor(bg);  TILE_BG(3,0).invalidate(); break;
                case 13: TILE(3,1).setWildcard(buff[i][j]);  TILE(3,1).invalidate();  TILE_BG(3,1).setColor(bg);  TILE_BG(3,1).invalidate(); break;
                case 14: TILE(3,2).setWildcard(buff[i][j]);  TILE(3,2).invalidate();  TILE_BG(3,2).setColor(bg);  TILE_BG(3,2).invalidate(); break;
                case 15: TILE(3,3).setWildcard(buff[i][j]);  TILE(3,3).invalidate();  TILE_BG(3,3).setColor(bg);  TILE_BG(3,3).invalidate(); break;
            }

        }
    }
    Unicode::snprintf(score, SIZE, "%d", point);
    textArea1.setWildcard(score);
    textArea1.invalidate();
    if (isFinish(arr)) {
    application().gotoScreen3ScreenNoTransition();
    }
}
void Screen2View::refesh()
{
    seed = (unsigned int)time(NULL);
    point=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            arr[i][j]=0;
        }
    }
    int h = randInRange(seed, 0, 15);
    arr[h / 4][h % 4] = r[(randInRange(seed + 1, 0, 1))];
    h = randInRange(seed+2, 0, 15);
    arr[h / 4][h % 4] = r[(randInRange(seed + 3, 0, 1))];
    Show();
}
