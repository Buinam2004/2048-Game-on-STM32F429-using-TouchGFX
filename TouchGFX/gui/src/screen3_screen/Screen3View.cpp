#include <gui/screen3_screen/Screen3View.hpp>
#include <gui/screen2_screen/Screen2View.hpp>
#include <touchgfx/Unicode.hpp>
Screen3View::Screen3View()
{

}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
    Unicode::snprintf(score, SIZE, "%d", point);
    Score.setWildcard(score);
    Score.invalidate();
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}
