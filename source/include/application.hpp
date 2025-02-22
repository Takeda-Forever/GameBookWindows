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
        vec2f pos{};
        const int edge = -100;
        float spawn = 2500;
        bool isEdge()
        {
            return pos.x < edge;
        }
        struct{
            struct 
            {
                const unsigned min = 100;
                const unsigned max = 300;
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

class TimeBar
{
  public:
    bool Draw(ptr_decls::ptr_RendWindow&, const float);
    void Reset();

  protected:
    struct
    {
        float timeBarStartWidth = 400;
        float timeBarHeight = 80;
        float DefaultTime = 6.0;
        float timeRemaining = DefaultTime;
        float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
        bool  Init = false;
    }Params;

    ptr_decls::DeclPtr<sf::RectangleShape> obj{std::make_unique<sf::RectangleShape>()};
    void setPos();
    void setUp();
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
    void Draw(ptr_decls::ptr_RendWindow&, const GameRule) override;


    Paused()
    {
        obj->setFillColor(sf::Color::White);
    }
    private:
    struct
    {
        sf::Font font{"resources/font.ttf"};
        std::string word = "Press Enter to start!";
        std::string loseword = "Game Over!";
        unsigned size = 75;
        vec2f pos{500, 500};
    }Params;
    
    ptr_decls::DeclPtr<sf::Text> obj = std::make_unique<sf::Text>(Params.font, Params.word, Params.size);
};

class Score : public ITxt
{
    public:
    void Draw(ptr_decls::ptr_RendWindow&, const GameRule) override;
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
        bool isOver = true;
    }Params;
//---------------------------------------------------

//-------------------- Variables --------------------
    ptr_decls::ptr_RendWindow       window;
//                            IOjbW
    ptr_decls::DeclPtr<IObjW>       bee{std::make_unique<Bee>()};
    ptr_decls::DeclPtr<IObjW>       cloud{std::make_unique<Cloud>()};
    ptr_decls::DeclPtr<TimeBar>       time{std::make_unique<TimeBar>()};

//                            IOjbEx
    ptr_decls::DeclPtr<IObjEx>      tree{std::make_unique<Tree>()};
    ptr_decls::DeclPtr<IObjEx>      bg{std::make_unique<Background>()};

//                            ITxt
    ptr_decls::DeclPtr<ITxt>        pause{std::make_unique<Paused>()};
    ptr_decls::DeclPtr<ITxt>        score{std::make_unique<Score>()};
//---------------------------------------------------

void DrawW(ptr_decls::DeclPtr<TimeBar>& obj, const float second)
{
    Params.isOver = obj->Draw(window, second);
}
void DrawW(ptr_decls::DeclPtr<IObjW>& obj, const float second)
{
    obj->Draw(window, second);
}
void DrawEx(ptr_decls::DeclPtr<IObjEx>& obj)
{
    obj->Draw(window);
}
void DrawT(ptr_decls::DeclPtr<ITxt>& obj, GameRule rule = NOTHING)
{
    obj->Draw(window, rule);
}

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
    virtual bool isOpen() // Own condition
    {
        return window->isOpen();
    }
    auto getEvent()      // Get window event from ::pollEvent()
    {
        return window->pollEvent();
    }
    bool isPaused()
    {
        return Params.pause;
    }
    void swap()
    {   
        Params.pause = !Params.pause;
    }
    void ResetTime()
    {
        time->Reset();
    }
    void RestartAll()
    {
        ResetTime();
        Params.isOver = true;
        bee = std::make_unique<Bee>();
        DrawT(score, GameRule::GameRestart);
        DrawT(pause, GameRule::GameRestart);
    }
//--------------------- Update ---------------------
void Update(const float second)
    {
        window->clear();
        
        if(!Params.isOver) swap();

        DrawEx(bg);
        DrawEx(tree);

        if(!isPaused() && Params.isOver) DrawW(bee, second);
        else if(!isPaused() && !Params.isOver) DrawW(bee, 0);
        DrawW(cloud, second);

        if(!Params.isOver)  DrawT(score, GameRule::GameOver);
        else                DrawT(score);

        if(isPaused())      DrawT(pause);
        else if(!Params.isOver)      DrawT(pause, GameRule::GameOver);

        if(!isPaused())     DrawW(time, second);
        else                DrawW(time, 0);
        
        window->display();
    }
//--------------------------------------------------


};

#endif
#endif