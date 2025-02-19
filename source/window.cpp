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
                        }
                        else
                        {
                            window.Button_Exit();
                        }
                    }
                    if(window.isPaused())
                    {
                        if (keyPressed->scancode == sf::Keyboard::Scancode::Enter){
                            window.swap();
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


// Include important libraries here
// #include <SFML/Graphics.hpp>

// // Make code easier to type with "using namespace" 
// using namespace sf;

// // This is where our game starts from int main()
// int main()
// {
// 	// What is the player's score?
// 	int playerScore;

// 	// What is the player�s first initial
// 	char playerInitial;

// 	// What is the value of pi
// 	float valuePi;

// 	// Is the player alive or dead?
// 	bool isAlive;

// 	playerScore = 'J';
// 	playerInitial = 0;
// 	valuePi = true;
// 	isAlive = 3.141f;



// 	// Create a video mode object 
// 	VideoMode vm(Vector2u(1920, 1080));

// 	// Create and open a window for the game
// 	RenderWindow window(vm, "Timber!!!");

// 	// Create a texture to hold a graphic on the GPU 
// 	Texture textureBackground("resources/background.png");

// 	// Load a graphic into the texture 

// 	// Create a sprite 
// 	Sprite spriteBackground(textureBackground);

// 	// Set the spriteBackground to cover the screen 
// 	spriteBackground.setPosition(Vector2f(0, 0));

// 	// Make a tree sprite
// 	Texture textureTree("resources/tree.png");
// 	Sprite spriteTree(textureTree);
// 	spriteTree.setPosition(Vector2f(810, 0));

// 	// Prepare the bee
// 	Texture textureBee("resources/bee.png");
// 	Sprite spriteBee(textureBee);
// 	spriteBee.setPosition(Vector2f(0, 800));

// 	// Is the bee currently moving?
// 	bool beeActive = false;

// 	// How fast can the bee fly
// 	float beeSpeed = 0.0f;

// 	// make 3 cloud sprites from 1 texture
// 	Texture textureCloud("resources/cloud.png");

// 	// 3 New sprites with the same texture
// 	Sprite spriteCloud1(textureCloud);
// 	Sprite spriteCloud2(textureCloud);
// 	Sprite spriteCloud3(textureCloud);
// 	// at different heights
// 	spriteCloud1.setPosition(Vector2f(0, 0));
// 	spriteCloud2.setPosition(Vector2f(0, 250));
// 	spriteCloud3.setPosition(Vector2f(0, 500));

// 	// Are the clouds currently on screen?
// 	bool cloud1Active = false;
// 	bool cloud2Active = false;
// 	bool cloud3Active = false;

// 	// How fast is each cloud?
// 	float cloud1Speed = 0.0f;
// 	float cloud2Speed = 0.0f;
// 	float cloud3Speed = 0.0f;

// 	// Variables to control time itself
// 	Clock clock;

// 	while (window.isOpen())
// 	{

// 		/*
// 		****************************************
// 		Handle the players input
// 		****************************************
// 		*/

// 		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
// 		{
// 			window.close();
// 		}

// 		/*
// 		****************************************
// 		Update the scene
// 		****************************************
// 		*/
		
// 		// Measure time
// 		Time dt = clock.restart();

// 		// Setup the bee
// 		if (!beeActive)
// 		{

// 			// How fast is the bee
// 			srand((int)time(0));
// 			beeSpeed = (rand() % 200) + 200;

// 			// How high is the bee
// 			srand((int)time(0) * 10);
// 			float height = (rand() % 500) + 500;
// 			spriteBee.setPosition(Vector2f(2000, height));
// 			beeActive = true;

// 		}
// 		else
// 		// Move the bee
// 		{

// 			spriteBee.setPosition(Vector2f(
// 				spriteBee.getPosition().x -
// 				(beeSpeed * dt.asSeconds()),
// 				spriteBee.getPosition().y));

// 			// Has the bee reached the left-hand edge of the screen?
// 			if (spriteBee.getPosition().x < -100)
// 			{
// 				// Set it up ready to be a whole new bee next frame
// 				beeActive = false;
// 			}
// 		}

// 		// Manage the clouds
// 		// Cloud 1
// 		if (!cloud1Active)
// 		{

// 			// How fast is the cloud
// 			srand((int)time(0) * 10);
// 			cloud1Speed = (rand() % 200);

// 			// How high is the cloud
// 			srand((int)time(0) * 10);
// 			float height = (rand() % 150);
// 			spriteCloud1.setPosition(Vector2f(-200, height));
// 			cloud1Active = true;
// 		}
// 		else
// 		{
// 			spriteCloud1.setPosition(Vector2f(
// 				spriteCloud1.getPosition().x +
// 				(cloud1Speed * dt.asSeconds()),
// 				spriteCloud1.getPosition().y));

// 			// Has the cloud reached the right hand edge of the screen?
// 			if (spriteCloud1.getPosition().x > 1920)
// 			{
// 				// Set it up ready to be a whole new cloud next frame
// 				cloud1Active = false;
// 			}
// 		}
// 		// Cloud 2
// 		if (!cloud2Active)
// 		{

// 			// How fast is the cloud
// 			srand((int)time(0) * 20);
// 			cloud2Speed = (rand() % 200);

// 			// How high is the cloud
// 			srand((int)time(0) * 20);
// 			float height = (rand() % 300) - 150;
// 			spriteCloud2.setPosition(Vector2f(-200, height));
// 			cloud2Active = true;


// 		}
// 		else
// 		{

// 			spriteCloud2.setPosition(Vector2f(
// 				spriteCloud2.getPosition().x +
// 				(cloud2Speed * dt.asSeconds()),
// 				spriteCloud2.getPosition().y));

// 			// Has the cloud reached the right hand edge of the screen?
// 			if (spriteCloud2.getPosition().x > 1920)
// 			{
// 				// Set it up ready to be a whole new cloud next frame
// 				cloud2Active = false;
// 			}
// 		}

// 		if (!cloud3Active)
// 		{

// 			// How fast is the cloud
// 			srand((int)time(0) * 30);
// 			cloud3Speed = (rand() % 200);

// 			// How high is the cloud
// 			srand((int)time(0) * 30);
// 			float height = (rand() % 450) - 150;
// 			spriteCloud3.setPosition(Vector2f(-200, height));
// 			cloud3Active = true;


// 		}
// 		else
// 		{

// 			spriteCloud3.setPosition(Vector2f(
// 				spriteCloud3.getPosition().x +
// 				(cloud3Speed * dt.asSeconds()),
// 				spriteCloud3.getPosition().y));

// 			// Has the cloud reached the right hand edge of the screen?
// 			if (spriteCloud3.getPosition().x > 1920)
// 			{
// 				// Set it up ready to be a whole new cloud next frame
// 				cloud3Active = false;
// 			}
// 		}



// 		/*
// 		****************************************
// 		Draw the scene
// 		****************************************
// 		*/

// 		// Clear everything from the last frame 
// 		window.clear();

// 		// Draw our game scene here
// 		window.draw(spriteBackground);

// 		// Draw the clouds
// 		window.draw(spriteCloud1);
// 		window.draw(spriteCloud2);
// 		window.draw(spriteCloud3);

// 		// Draw the tree
// 		window.draw(spriteTree);

// 		// Draw the insect
// 		window.draw(spriteBee);

// 		// Show everything we just drew 
// 		window.display();
// 	}
// 	return 0;
// }

