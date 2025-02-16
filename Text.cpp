#include "application.hpp"

void Score::Draw(ptr_decls::ptr_RendWindow & window)
{
}

void Message::Draw(ptr_decls::ptr_RendWindow & window)
{
    obj->setPosition(Params.pos);
    window->draw(*obj);
}