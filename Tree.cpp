#include "application.hpp"

void Tree::Draw(ptr_decls::ptr_RendWindow & window)
{
    obj->setPosition(Params.pos);
    window->draw(*obj);
}