#include "include/application.hpp"

int main() {
    try{
        Windows window;
        sf::Clock clock;
        srand(static_cast<unsigned>(time(nullptr)));
        while (window.isOpen()) 
        {
            sf::Time time = clock.restart();
            while (const auto event = window.getEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.Exit();
                }
                else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                        if(!window.isPaused())
                        {
                            window.swap();
                            window.RestartAll();
                        }
                    }
                    if(window.isPaused())
                    {
                        if (keyPressed->scancode == sf::Keyboard::Scancode::Enter){
                            window.swap();
                            clock.reset();
                        }          
                    }            
                }
            }
            window.Update(time.asSeconds());
        }
    }
    catch(const sf::Exception ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }
    std::cout << "Press any buttons...";
    std::cin.get();
    return EXIT_SUCCESS;
}