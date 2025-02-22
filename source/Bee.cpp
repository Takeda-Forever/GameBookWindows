#include "include/application.hpp"

void Bee::Draw(ptr_decls::ptr_RendWindow& window, const float second)
{
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
    Params.speed = Params.Random.Speed.min  + (rand() % (Params.Random.Speed.max - Params.Random.Speed.min));
    float height = Params.Random.Height.min + (rand() % (Params.Random.Height.max - Params.Random.Height.min));
    Params.pos = vec2f(Params.spawn, height);
    obj->setPosition(Params.pos);
    Params.active = true;
    if(debugger) printParams();
}

// Min=400
// Max=200
// random = x
// min + (x % (max-min))
// 400 + (18 % (500 - 400))
// 400 + 18 % 100
// 400 + 18
// 418

void Bee::Update(const float second)
{
    setPos(second);
    if(Params.isEdge())
    {
        Params.active = false;
        if(debugger) std::cout << "bee get Edge of window: [x:" << Params.pos.x << " y:" << Params.pos.y << "];\n";
    }
}