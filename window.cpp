#include <SFML/Graphics.hpp>
#include <iostream>

class Windows
{
    public:
    Windows() // Initialization of window
    {
        window = std::make_unique<sf::RenderWindow>
                    (sf::VideoMode(sf::Vector2u(width, height)), title);
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
    void DrawMake()     // Update frame
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
    std::string title = "SFML Game";    // A title of window -- on the upside of programm
    uint16_t    width = 1920,           // A window width  -- x: 0 - 1919bits on window
                height = 1080;          // A window height -- y: 0 - 1079bits on window
    std::unique_ptr<sf::RenderWindow> window;

    std::string resourcesPath = "resources/";
    std::string textureFile = resourcesPath + "Background.jpg";
    sf::Texture* bgTexture = new sf::Texture(textureFile);
    sf::Sprite* bgSprite = new sf::Sprite(*bgTexture);
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
            window.DrawMake();
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
