#pragma once
#include "pch.h"

#ifndef _DECLARATIONS_
#define _DECLARATIONS_

    namespace ptr_decls
    {
        template< typename T >
        using DeclPtr                   = std::unique_ptr<T>;

        using ptr_Texture               = DeclPtr<sf::Texture>;
        using ptr_RendWindow            = DeclPtr<sf::RenderWindow>;
        using ptr_Obj                   = DeclPtr<sf::Sprite>;
    }

    using path = std::string;

    using vec2f                         = sf::Vector2<float>;
    using vec2u                         = sf::Vector2<unsigned>;

    #define m_RendWindow                std::make_unique<sf::RenderWindow>
    #define m_Texture                   std::make_unique<sf::Texture>
    #define m_Obj                       std::make_unique<sf::Sprite>
    #define m_Clock                     std::make_unique<sf::Clock>
    #define m_Time                      std::make_unique<sf::Time>

#endif // _DECLARATIONS_

#ifndef _I_OBJ_
#define _I_OBJ_
class IObj
{
    protected:
    path r_dir /*Resources directory*/ = "resources/"; 
    void printC(std::string complite)
    {
        std::cout << "DO: " << complite << std::endl;
    }
};
#endif // _I_OBJ_

class ITxt
{
    public:
    virtual void Draw(ptr_decls::ptr_RendWindow&) = 0;
};

#ifdef _I_OBJ_
class IObjEx : protected IObj
{
    public:
    virtual void Draw(ptr_decls::ptr_RendWindow&)        = 0;
};

class IObjW : protected IObj
{
    public:
    virtual void Draw(ptr_decls::ptr_RendWindow&, const float, bool = false)          = 0;
};
#endif // if _I_OBJ_