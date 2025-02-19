#include "include/application.hpp"

void Bee::Draw(ptr_decls::ptr_RendWindow& window, const float second, bool debug = false)
{
    debugger = debug;
    if(Params.active == false)
    {
        setUp();
    }
    else
    {
        Update(second);
    }
    window->draw(*obj);
}

void Bee::printParams()
{
    std::cout << "BeeParams: \n"
    " - [x:" << Params.pos.x << "],\n" <<
    " - [y:" << Params.pos.y << "],\n" <<
    " - [speed:" << Params.speed << "],\n" <<
    " - [active: " << std::boolalpha << Params.active << "];\n\n";
}

void Bee::setPos(const float second)
{
    Params.pos.x -= Params.speed * second;
    obj->setPosition(Params.pos);
}

void Bee::setUp()
{
    if(debugger) printC("beeSetup");
    Params.speed = (rand() % 200) + 200;
    float height = (rand() % 500) + 500;
    Params.pos = vec2f(2000, height);
    obj->setPosition(Params.pos);
    Params.active = true;
    if(debugger) printParams();
}

void Bee::Update(const float second)
{
    setPos(second);
    if(Params.isEdge())
    {
        Params.active = false;
        if(debugger) std::cout << "bee get Edge of window: [x:" << Params.pos.x << " y:" << Params.pos.y << "];\n";
    }
}