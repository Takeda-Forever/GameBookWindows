#include "application.hpp"

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
            window.Update();
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
