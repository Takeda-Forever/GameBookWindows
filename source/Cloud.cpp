#include "include/application.hpp"

void Cloud::Draw(ptr_decls::ptr_RendWindow & window, const float second)
{
    for(int select = 0; select < Params.cloudCount; select++)
        {
            if(!Params.active[select])
            {
                setUp(select);
                if(debugger) std::cout << "Cloud #" << select+1 << ":\n";
                if(debugger) printParams(select);
            }
            else{
                Update(second, select);
            }
            window->draw(*obj[select]);
    }
}

void Cloud::printParams(const int select)
{
    std::cout << 
    " - [x:" << Params.pos[select].x << "],\n" <<
    " - [y:" << Params.pos[select].y << "],\n" <<
    " - [speed:" << Params.speed[select] << "],\n" <<
    " - [active: " << std::boolalpha << Params.active[select] << "];\n\n";
}

void Cloud::setUp(const int select)
{
    if(debugger) printC("cloudSetup");
    Params.speed[select] = (rand() % Params.Random.Speed.max) + Params.Random.Speed.min;
    float height = (rand() % Params.Random.Height.max);
    Params.pos[select] = vec2f(-202, height);
    obj[select]->setPosition(Params.pos[select]);
    Params.active[select] = true;
}

void Cloud::setPos(const float second, const int select)
{
    Params.pos[select].x += Params.speed[select] * second;
    obj[select]->setPosition(Params.pos[select]);
}

void Cloud::Update(const float second, const int select)
{
    setPos(second, select);
    if(!Params.isEdge(select))
    {
        Params.active[select] = false;
        if(debugger) std::cout << "cloud "<< select << " get Edge of window: [x:" << Params.pos[select].x << " y:" << Params.pos[select].y << "];\n";
    }
}
