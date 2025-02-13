#include "application.hpp"

void Background::Draw(ptr_decls::ptr_RendWindow & window)
{
    window->draw(*obj);
}