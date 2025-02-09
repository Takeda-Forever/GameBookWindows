#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <thread>

/*
Task:
Recover the frame update time & make the bee move;

Last log:
    beeSetup:  [x:2000 y:727 frame:0.378534 speed:398];
    beeNewPos: [x:2000 y:727 frame:0        speed:398];
    beeNewPos: [x:2000 y:727 frame:0        speed:398];
    beeNewPos: [x:2000 y:727 frame:0        speed:398];
    beeNewPos: [x:2000 y:727 frame:0        speed:398];
    beeNewPos: [x:2000 y:727 frame:0        speed:398];
*/

#ifndef _DECLARATIONS_
#define _DECLARATIONS_

    namespace ptr_decls
    {
        template< typename T >
        using DeclPtr                   = std::unique_ptr<T>;

        using ptr_Texture               = DeclPtr<sf::Texture>;
        using ptr_RendWindow            = DeclPtr<sf::RenderWindow>;
        using ptr_Obj                   = DeclPtr<sf::Sprite>;
        using ptr_Clock                 = DeclPtr<sf::Clock>;
        using ptr_Time                 = DeclPtr<sf::Time>;
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

#ifndef _CLASS_WINDOW_
#define _CLASS_WINDOW_


class Windows
{
    public:
//---------------------- Other ---------------------
    Windows() // Initialization of window
    {
        window = m_RendWindow
                    (sf::VideoMode(sf::Vector2u(WindowParams.width, WindowParams.height)), WindowParams.title);
        clock->start();
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
    auto restartTime()
    {
        dt = m_Time(clock->reset());
        //std::cout << "New frame: [frame:" << dt->asMilliseconds() << "];\n";
    }
//--------------------------------------------------

//---------------------- Bee -----------------------
    void beeSetup()
    {

            srand((int)time(0));
            BeeParams.speed = (rand() % 200) + 200;

            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
            BeeParams.pos = vec2f(2000, height);
            o_bee->setPosition(BeeParams.pos);
            BeeParams.active = true;

    }
    void beeUpdatePos()
    {
        o_bee->setPosition(BeeParams.pos);
    }
    void beeSetPos()
    {
        auto beePosX = o_bee->getPosition().x,
             beePosY = o_bee->getPosition().y;
        auto beeSpeed = BeeParams.speed;
        auto frame = dt->asSeconds();
        
        BeeParams.pos = vec2f(beePosX - (beeSpeed * frame), beePosY);
        std::cout << "beeNewPos: [x:" << BeeParams.pos.x << " y:" << BeeParams.pos.y << " frame:" << frame << " speed:" << beeSpeed << "];\n";
        
    }
    void beeUpdate()
    {
        beeSetPos();
        beeUpdatePos();
        if(BeeParams.isEdge())
        {
            BeeParams.active = false;
            std::cout << "bee get Edge of window: [x:" << BeeParams.pos.x << " y:" << BeeParams.pos.y << "];\n";
        }
    }
//--------------------------------------------------

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
        restartTime();
        if(BeeParams.active == false)

        {
            beeSetup();
            std::cout << "beeSetup: [x:" << BeeParams.pos.x << " y:" << BeeParams.pos.y << " frame:" << dt->asSeconds() << " speed:" << BeeParams.speed << "];\n";
        }
        else
        {
            beeUpdate();
        }
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
        dt.reset();
        window->display();
    }
//---------------------------------------------------
    private:
//--------------------- Params ----------------------
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
        bool isEdge()
        {
            return pos.x < -100;
        }
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
//---------------------------------------------------

//-------------------- Variables --------------------
//****************************** Others ******************************
    ptr_decls::ptr_RendWindow window;
    ptr_decls::ptr_Time dt;
    ptr_decls::ptr_Clock clock          = m_Clock();
//******************************* Paths ******************************
    path r_dir /*Resources directory*/ = "resources/"; 
    path p_background            = r_dir + "background.png";
    path p_tree                  = r_dir + "tree.png";
    path p_bee                   = r_dir + "bee.png";
    path p_cloud                 = r_dir + "cloud.png";
//***************************** Textures *****************************
    ptr_decls::ptr_Texture t_background = m_Texture(p_background);
    ptr_decls::ptr_Texture t_tree       = m_Texture(p_tree);
    ptr_decls::ptr_Texture t_bee        = m_Texture(p_bee);
    ptr_decls::ptr_Texture t_cloud      = m_Texture(p_cloud);

//****************************** Objects *****************************
    ptr_decls::ptr_Obj o_background    = m_Obj(*t_background);
    ptr_decls::ptr_Obj o_tree          = m_Obj(*t_tree);
    ptr_decls::ptr_Obj o_bee           = m_Obj(*t_bee);
    ptr_decls::ptr_Obj oa_cloud[3]     = {m_Obj(*t_cloud), m_Obj(*t_cloud), m_Obj(*t_cloud)};
//---------------------------------------------------
};

#endif // _CLASS_WINDOW_