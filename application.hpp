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
        window->draw(*o_background);
    }
    void DrawTree()
    {
        o_tree->setPosition(TreeParams.pos);
        window->draw(*o_tree);
    }
    void DrawBee()
    {
        o_bee->setPosition(BeeParams.pos);
        window->draw(*o_bee);
    }
    void DrawClouds()
    {
        for(int i = 0; i < CloudParams.cloudCount; i++)
        {
            oa_cloud[i]->setPosition(CloudParams.pos[i]);
            window->draw(*oa_cloud[i]);
        }
    }

//--------------------------------------------------

//--------------------- Update ---------------------
void Update()
    {
        window->clear();

        DrawBackground();
        DrawTree();
        DrawBee();
        DrawClouds();

        window->display();
    }
//---------------------------------------------------
    private:

    struct 
    {
        size_t cloudCount = 3;
        vec2f pos[3]
        {
            vec2f{0, 0}, 
            vec2f{0, 250}, 
            vec2f{0, 500}
        };
        bool active[3]{};
    }CloudParams;
    struct
    {
        bool active = false;
        float speed = .0f;
        vec2f pos{0, 800};
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
    path p_background            = r_dir + "background.png";
    path p_tree                  = r_dir + "tree.png";
    path p_bee                   = r_dir + "bee.png";
    path p_cloud                 = r_dir + "cloud.png";

    ptr_decls::ptr_Texture t_background = m_Texture(p_background);
    ptr_decls::ptr_Texture t_tree       = m_Texture(p_tree);
    ptr_decls::ptr_Texture t_bee        = m_Texture(p_bee);
    ptr_decls::ptr_Texture t_cloud      = m_Texture(p_cloud);

    ptr_decls::ptr_Obj o_background    = m_Obj(*t_background);
    ptr_decls::ptr_Obj o_tree          = m_Obj(*t_tree);
    ptr_decls::ptr_Obj o_bee           = m_Obj(*t_bee);
    ptr_decls::ptr_Obj oa_cloud[3]     = {m_Obj(*t_cloud), m_Obj(*t_cloud), m_Obj(*t_cloud)};
};

#endif // _CLASS_WINDOW_