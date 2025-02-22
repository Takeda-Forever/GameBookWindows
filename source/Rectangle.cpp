#include "include/application.hpp"
#include "application.hpp"

bool TimeBar::Draw(ptr_decls::ptr_RendWindow & window, const float second)
{
    if(Params.timeRemaining <= 0.0f) return false;
    
    if(!Params.Init)
    {
        setUp();
    }
    else
    {
        Params.timeRemaining -= second;
        setPos();
    }
    window->draw(*obj);
    return true;
}

void TimeBar::Reset()
{
    Params.timeRemaining = Params.DefaultTime;;
}

void TimeBar::setPos()
{
    obj->setSize(vec2f(Params.timeBarWidthPerSecond *
        Params.timeRemaining, Params.timeBarHeight));
}
void TimeBar::setUp()
{
    obj->setSize(vec2f(Params.timeBarStartWidth, Params.timeBarHeight));
	obj->setFillColor(sf::Color::Red);
	obj->setPosition(vec2f((1920 / 2) - Params.timeBarStartWidth / 2, 980));
    Params.Init = true;
}