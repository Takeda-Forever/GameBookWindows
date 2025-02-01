#include <SFML/Graphics.hpp>
#include <iostream>



namespace ptr_decls
{
template<typename T>
using DeclPtr = std::unique_ptr<T>;
template<typename T>
using MakePtr = std::make_unique<T>;

using ptr_RendWindow = DeclPtr<sf::RenderWindow>;
using ptr_Texture = DeclPtr<sf::Texture>;
using ptr_Sprite = DeclPtr<sf::Sprite>;

using m_RendWindow = MakePtr<sf::RenderWindow>;
using m_Texture = MakePtr<sf::Texture>;
using m_Sprite = MakePtr<sf::Sprite>;
}



class Windows
{
    public:
    Windows() // Initialization of window
    {
        window = ptr_decls::m_RendWindow
                    (sf::VideoMode(sf::Vector2u(WindowParams.width, WindowParams.height)), WindowParams.title);
    }
    ~Windows()
    {
        std::cout << "\n-----Window get closed!-----\n" << std::endl;
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
    void DrawDisplay()     // Update frame
    {
        window->clear();
        window->draw(*bgSprite);
        window->display();
    }

    virtual bool isOpen() // Own conditional
    {
        return window->isOpen();
    }

    auto getEvent()      // Get window event from ::pollEvent()
    {
        return window->pollEvent();
    }

    private:
    struct // All parameter of window wich connected to the window in any way
    {
        std::string title = "SFML Game";    // A title of window -- on the upside of programm
        uint16_t    width = 1920,           // A window width  -- x: 0 - 1919bits on window
                    height = 1080;          // A window height -- y: 0 - 1079bits on window
    }WindowParams;

    ptr_decls::ptr_RendWindow window;

    std::string resourcesPath = "resources/";
    std::string textureFile = resourcesPath + "Background.jpg";
    ptr_decls::ptr_Texture bgTexture   = ptr_decls::m_Texture(textureFile);
    ptr_decls::ptr_Sprite bgSprite     = ptr_decls::m_Sprite(*bgTexture);
};

int main() {
    try{
        Windows window;
        while (window.isOpen()) {
            while (const auto event = window.getEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.Exit();
                }
                else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                        window.Button_Exit();
                    }                   
                }
            }


            window.DrawDisplay();
        }
    }
    catch(const std::exception ex)
    {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "Press any buttons...";
    std::cin.get();
    return EXIT_SUCCESS;
}
