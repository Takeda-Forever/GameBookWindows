#pragma once
#include "pch.h"
#include "interface.hpp"

/*
Task:

*/
#ifdef _I_OBJ_
#ifdef _DECLARATIONS_

//------------ IObjW -----------
class Bee : public IObjW
{
  public:
    void Draw(ptr_decls::ptr_RendWindow&, const float) override;
    Bee(bool debug = false): debugger(debug)
    {};
  protected:
    struct
    {
        bool active = false;
        float speed = 150.0f;
        vec2f pos{0, 800};
        const int edge = -100;
        bool isEdge()
        {
            return pos.x < edge;
        }
        struct{
            struct 
            {
                const unsigned min = 300;
                const unsigned max = 500;
            }Speed;
            struct 
            {
                const unsigned min = 600;
                const unsigned max = 800;
            }Height;
        }Random;
        
    }Params;
    path _path                              = r_dir + "bee.png";
    ptr_decls::ptr_Texture texture          = m_Texture(_path);
    ptr_decls::ptr_Obj obj                  = m_Obj(*texture);
    bool debugger;

    virtual void printParams()              ;
    virtual void setUp()                    ;
    virtual void setPos(const float)        ;
    virtual void Update(const float)        ;
};

class Cloud : public IObjW
{
  public:
    void Draw(ptr_decls::ptr_RendWindow&, const float) override;
    Cloud(bool debug = false): debugger(debug){};
  protected:
    struct
    {
        const size_t cloudCount = 3;
        int speed[3]
        {0, 0, 0};
        const int edge = 1921;
        vec2f pos[3]
        {
            vec2f{0, 0}, 
            vec2f{0, 250}, 
            vec2f{0, 500}
        };
        bool isEdge(const size_t select)
        {
            return pos[select].x < edge;
        }
        bool active[3]{};
        struct{
            struct 
            {
                const unsigned min = 40;
                const unsigned max = 200;
            }Speed;
            struct 
            {
                const unsigned max = 100;
            }Height;
        }Random;
    }Params;
    path _path                              = r_dir + "cloud.png";
    ptr_decls::ptr_Texture texture          = m_Texture(_path);
    ptr_decls::ptr_Obj obj[3]               = {m_Obj(*texture), m_Obj(*texture), m_Obj(*texture)};
    bool debugger;
    
    void printParams(const int);
    void setUp(const int);
    void setPos(const float, const int);
    void Update(const float, const int);

};
//------------------------------

//------------ IObjEx ----------
class Background : public IObjEx
{
  public:
    void Draw(ptr_decls::ptr_RendWindow&) override;

  protected:
    path _path                              = r_dir + "background.png";
    ptr_decls::ptr_Texture texture          = m_Texture(_path);
    ptr_decls::ptr_Obj obj                  = m_Obj(*texture);
};

class Tree : public IObjEx
{
  public:
    void Draw(ptr_decls::ptr_RendWindow&) override;

  protected:
    struct
    {
        vec2f pos{810, 0};
    }Params;
    path _path                              = r_dir + "tree.png";
    ptr_decls::ptr_Texture texture          = m_Texture(_path);
    ptr_decls::ptr_Obj obj                  = m_Obj(*texture);
};
//------------------------------


//------------ ITxt ------------
class Paused : public ITxt
{
    public:
    void Draw(ptr_decls::ptr_RendWindow&) override;


    Paused()
    {
        obj->setFillColor(sf::Color::White);
    }
    private:
    struct
    {
        sf::Font font{"resources/font.ttf"};
        std::string word = "Press Enter to start!";
        unsigned size = 75;
        vec2f pos{500, 500};
    }Params;
    
    ptr_decls::DeclPtr<sf::Text> obj = std::make_unique<sf::Text>(Params.font, Params.word, Params.size);
};

class Score : public ITxt
{
    public:
    void Draw(ptr_decls::ptr_RendWindow&) override;
    Score()
    {
        obj->setFillColor(sf::Color::White);
    }
    private:
    struct
    {
        sf::Font font{"resources/font.ttf"};
        int score = 0;
        std::string word = "score = " + std::to_string(score);
        unsigned size = 50;
    }Params;
    
    ptr_decls::DeclPtr<sf::Text> obj = std::make_unique<sf::Text>(Params.font, Params.word, Params.size);
};
//------------------------------

class Windows
{
    private:
//--------------------- Params ----------------------
    struct // All parameter of window wich connected to the window in any way
    {
        std::string title = "SFML Game";    // A title of window -- on the upside of programm
        int         width = 1920,           // A window width  -- x: 0 - 1919bits on window
                    height = 1080;          // A window height -- y: 0 - 1079bits on window
        bool pause = true;
    }Params;
//---------------------------------------------------

//-------------------- Variables --------------------
    ptr_decls::ptr_RendWindow       window;
//                            IOjbW
    ptr_decls::DeclPtr<IObjW>       bee{std::make_unique<Bee>()};
    ptr_decls::DeclPtr<IObjW>       cloud{std::make_unique<Cloud>()};

//                            IOjbEx
    ptr_decls::DeclPtr<IObjEx>      tree{std::make_unique<Tree>()};
    ptr_decls::DeclPtr<IObjEx>      bg{std::make_unique<Background>()};

//                            ITxt
    ptr_decls::DeclPtr<ITxt>        pause{std::make_unique<Paused>()};
    ptr_decls::DeclPtr<ITxt>        score{std::make_unique<Score>()};
//---------------------------------------------------


    public:
//---------------------- Other ---------------------
    Windows() // Initialization of window
    {
        window = m_RendWindow
                    (sf::VideoMode(sf::Vector2u(Params.width, Params.height)), Params.title);
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
    void DrawW(ptr_decls::DeclPtr<IObjW>& obj, const float second)
    {
        obj->Draw(window, second);
    }
    void DrawEx(ptr_decls::DeclPtr<IObjEx>& obj)
    {
        obj->Draw(window);
    }
    void DrawT(ptr_decls::DeclPtr<ITxt>& obj)
    {
        obj->Draw(window);
    }
    bool isPaused()
    {
        return Params.pause;
    }
    void swap()
    {   
        Params.pause = !Params.pause;
    }

//--------------------------------------------------

//--------------------- Update ---------------------
void Update(const float second)
    {
        window->clear();

        DrawEx(bg);
        DrawEx(tree);
        DrawW(bee, second);
        DrawW(cloud, second);
        DrawT(score);
        if(isPaused())
        {
            DrawT(pause);
        }
        window->display();
    }
//---------------------------------------------------
};

#endif
#endif