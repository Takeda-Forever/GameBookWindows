#include "include/application.hpp"

void Paused::Draw(ptr_decls::ptr_RendWindow & window, const GameRule rule)
{
    if(rule == GameRule::GameOver)
    {
        obj->setString(Params.loseword);
    }
    else if(rule == GameRule::GameRestart)
    {
        obj->setString(Params.word);
    }
    obj->setPosition(Params.pos);
    window->draw(*obj);
}


void Score::Draw(ptr_decls::ptr_RendWindow & window, const GameRule rule)
{
    if(rule == GameRule::GameRestart)
    {
        Params.score = 0;
    }
    else if(rule == GameRule::NOTHING) 
    {
        Params.word = "score = " + std::to_string(Params.score);
        obj->setString(Params.word);
    }
    obj->setPosition(vec2f(20, 20));
    window->draw(*obj);
}
