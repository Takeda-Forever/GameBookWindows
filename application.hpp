#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <array>

#ifndef _DECLARATIONS_
#define _DECLARATIONS_

    namespace ptr_decls
    {
        template< typename T >
        using DeclPtr                   = std::unique_ptr<T>;

        template<typename T, size_t size>
        using ptr_Arr                   = std::array<T, size>;

        using ptr_RendWindow            = DeclPtr<sf::RenderWindow>;
        using ptr_Obj                   = DeclPtr<sf::Sprite>;
    }
    
    using path = std::string;

    using vec2f                         = sf::Vector2<float>;
    using vec2u                         = sf::Vector2<unsigned>;

    #define m_RendWindow                std::make_unique<sf::RenderWindow>
    #define m_Texture                   std::make_unique<sf::Texture>
    #define m_Obj(path_to_file)         std::make_unique<sf::Sprite>(sf::Texture(path_to_file))

#endif // _DECLARATIONS_

#ifndef _CLASS_WINDOW_
#define _CLASS_WINDOW_

class Windows
{
    public:
    Windows() // Initialization of window
    {
        window = m_RendWindow
                    (sf::VideoMode(sf::Vector2u(WindowParams.width, WindowParams.height)), WindowParams.title);
    }
    ~Windows()
    {
        std::cout << "\n-----Window get closed!-----\n" << std::endl;
        window->close();
        window.get_deleter();
    }
    void Abort_Exit()
    {
        std::cout << "Abort closing window!\n";
        window->close();
        throw "Error during texture initialization!. Window will be automaticly closed!\n";
    }
    void Exit()         // Exit with command report
    {
        std::cout << "-Command: Exit;\n";
        window->close();
    }
    void Button_Exit()  // Exit with button report
    {
        std::cout << "-Button: ESC;\n";
        Exit();
    }
    virtual bool isOpen() // Own condition
    {
        return window->isOpen();
    }
    auto getEvent()      // Get window event from ::pollEvent()
    {
        return window->pollEvent();
    }

//---------------------- Draw ----------------------

    void DrawBackground()
    {
        window->draw(*backgroundObj);
    }
    void DrawTree()
    {
        treeObj->setPosition(TreeParams.pos);
        window->draw(*treeObj);
    }
    void DrawBee()
    {
        window->draw(*beeObj);
    }
    // void DrawClouds()
    // {
    //     for(int i = 0; i < 3; i++)
    //     {
    //         cloudArr.at(i)->setPosition(CloudParams.pos[i]);
    //         window->draw(*cloudArr.at(i));
    //     }
    // }

//--------------------------------------------------

//--------------------- Update ---------------------
void Update()
    {
        window->clear();

        DrawBackground();
        DrawTree();
        DrawBee();
        //DrawClouds();

        window->display();
    }
//---------------------------------------------------
    private:

    // struct 
    // {
    //     size_t cloudCount = 3;
    //     ptr_decls::ptr_Arr<vec2f, 3> pos
    //     {
    //         vec2f{0, 0}, 
    //         vec2f{0, 250}, 
    //         vec2f{0, 500}
    //     };
    //     ptr_decls::ptr_Arr<bool, 3> active{false};
    // }CloudParams;

    struct
    {
        bool active = false;
        float speed = .0f;
    }BeeParams;
    struct
    {
        vec2f pos{810, 0};
    }TreeParams;
    struct // All parameter of window wich connected to the window in any way
    {
        std::string title = "SFML Game";    // A title of window -- on the upside of programm
        int         width = 1920,           // A window width  -- x: 0 - 1919bits on window
                    height = 1080;          // A window height -- y: 0 - 1079bits on window
    }WindowParams;

    ptr_decls::ptr_RendWindow window;

    path r_dir /*Resources directory*/ = "resources/"; 
    path p_backgroundTexture            = r_dir + "background.png";
    path p_treeTexture                  = r_dir + "tree.png";
    path p_beeTexture                   = r_dir + "bee.png";
    path p_cloudTexture                 = r_dir + "cloud.png";

    ptr_decls::ptr_Obj backgroundObj    = m_Obj(p_backgroundTexture);
    ptr_decls::ptr_Obj treeObj          = m_Obj(p_treeTexture);
    ptr_decls::ptr_Obj beeObj           = m_Obj(p_beeTexture);
    //ptr_decls::ptr_Arr<ptr_decls::ptr_Obj, 3> cloudArr{m_Obj(p_cloudTexture)};
};

#endif // _CLASS_WINDOW_