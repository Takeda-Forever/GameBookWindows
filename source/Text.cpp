#include "include/application.hpp"

void Score::Draw(ptr_decls::ptr_RendWindow & window)
{
    obj->setPosition(vec2f(20, 20));
    window->draw(*obj);
}

void Paused::Draw(ptr_decls::ptr_RendWindow & window)
{
    
    obj->setPosition(Params.pos);
    window->draw(*obj);
}