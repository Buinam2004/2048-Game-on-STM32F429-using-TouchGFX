#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>
#include <touchgfx/Unicode.hpp>
#include <gui/common/FrontendApplication.hpp>

#define SIZE 20
extern Unicode::UnicodeChar buff[4][4][20];
extern Unicode::UnicodeChar score[20];
extern int point;
extern int value;
extern int arr[4][4];
int leftAction(int a[4][4],unsigned int seed);
int rightAction(int a[4][4],unsigned int seed);
int upAction(int a[4][4],unsigned int seed);
int downAction(int a[4][4],unsigned int seed);
int isFinish(int a[4][4]);
unsigned int randFromSeed(unsigned int seed);
int randInRange(unsigned int seed, int min, int max);
int pushLeft(int a[4][4]);
int pushRight(int a[4][4]);
int pushUp(int a[4][4]);
int pushDown(int a[4][4]);
extern int isStop;
class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void Show();
    virtual void Top();
    virtual void Right();
    virtual void Bottom();
    virtual void Left();
    virtual void refesh();
protected:
};

#endif // SCREEN2VIEW_HPP
