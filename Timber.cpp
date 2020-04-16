
#include <iostream>
#include <sstream>
#include <SFML/graphics.hpp>

// easier to type code
using namespace sf;


int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);

    // Create and open a game window
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    //Create a texture to hold the graphic on the GPU
    Texture textureBackground;

    // Load the background onto the frame
    textureBackground.loadFromFile("graphics/background.png");

    // Create the sprite
    Sprite spriteBackground;

    //Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Cover the screen
    spriteBackground.setPosition(0, 0);


    // Create a tree object
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // Create a bee object
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    // Is the bee moving?
    bool beeActive = false;
    // How fast can the bee fly ?
    float beeSpeed = 0.0f;

    // Create 3 clouds
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    spriteCloud1.setPosition(0, 100);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);
    // Is the bee moving?
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
    // How fast can the bee fly ?
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    // Variables to control time
    Clock clock;

    // Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool paused = true;

    //Draw some text
    int score = 0;
    sf::Text messageText;
    sf::Text scoreText;

    //Font choice
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    //Set the font to our message
    messageText.setFont(font);
    scoreText.setFont(font);

    //The text content
    messageText.setString("Press Enter to start.");
    scoreText.setString("Score = 0");

    //Make font big
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    // Set color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    //Text position
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    // The game loop
    while (window.isOpen())
    {   
        /*
        *************************
        Player input handling
        *************************
        */

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        //Start the game
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;

            //reset the time and score
            score = 0;
            timeRemaining = 6;
        }
        /*
        *************************
        Update the scene
        *************************
        */

        // Measure time
        Time dt = clock.restart();


        if (!paused)
        {

            // Timebar logic
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0)
            {
                paused = true;

                messageText.setString("Out of time!");

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left +
                    textRect.width / 2.0f,
                    textRect.top +
                    textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }
            //Bee setup
            if (!beeActive)
            {
                // How fast is the bee
                srand((int)time(0) * 10);
                beeSpeed = (rand() % 200) + 200;

                // How high is the bee?
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
                // Move the bee
            {
                spriteBee.setPosition(
                    spriteBee.getPosition().x -
                    (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y
                );
                //Has the bee reached the edge of the screen?
                if (spriteBee.getPosition().x < -100)
                {
                    beeActive = false;
                }
            }
            // cloud set up
            if (!cloud1Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 150);

                // How high is the cloud
                srand((int)time(0) * 10);
                float height = (rand() % 100);
                spriteCloud1.setPosition(-200, height);
                cloud1Active = true;
            }
            else
                // Move the cloud
            {
                spriteCloud1.setPosition(
                    spriteCloud1.getPosition().x +
                    (cloud1Speed * dt.asSeconds()),
                    spriteCloud1.getPosition().y
                );
                //Has the bee reached the edge of the screen?
                if (spriteCloud1.getPosition().x > 1920)
                {
                    cloud1Active = false;
                }
            }
            if (!cloud2Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);

                // How high is the cloud
                srand((int)time(0) * 10);
                float height = (rand() % 300);
                spriteCloud2.setPosition(-200, height);
                cloud2Active = true;
            }
            else
                // Move the cloud
            {
                spriteCloud2.setPosition(
                    spriteCloud2.getPosition().x +
                    (cloud2Speed * dt.asSeconds()),
                    spriteCloud2.getPosition().y
                );
                //Has the bee reached the edge of the screen?
                if (spriteCloud2.getPosition().x > 1920)
                {
                    cloud2Active = false;
                }
            }
            if (!cloud3Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 300);

                // How high is the cloud
                srand((int)time(0) * 10);
                float height = (rand() % 300);
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;
            }
            else
                // Move the cloud
            {
                spriteCloud3.setPosition(
                    spriteCloud3.getPosition().x +
                    (cloud3Speed * dt.asSeconds()),
                    spriteCloud3.getPosition().y
                );
                //Has the bee reached the edge of the screen?
                if (spriteCloud3.getPosition().x > 1920)
                {
                    cloud3Active = false;
                }
            }
            // Update the score
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }
            /*
            *************************
            Draw the scene
            *************************
            */
            // Clear last frame
            window.clear();

            //Draw game scene
            window.draw(spriteBackground);

            // Draw clouds
            window.draw(spriteCloud1);
            window.draw(spriteCloud2);
            window.draw(spriteCloud3);

            //Draw tree
            window.draw(spriteTree);

            // Draw Bee
            window.draw(spriteBee);

            // Draw the score
            window.draw(scoreText);
            if (paused)
            {
                window.draw(messageText);
            }
            window.draw(timeBar);

        //Show what we just drew
        window.display();

    }
    return 0;
}
