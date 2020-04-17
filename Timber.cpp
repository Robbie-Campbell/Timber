
#include <iostream>
#include <sstream>
#include <SFML/graphics.hpp>
#include <SFML/Audio.hpp>
// easier to type code
using namespace sf;

// Declare the function
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

// Where is the player
enum class side { LEFT,RIGHT,NONE };
side branchPositions[NUM_BRANCHES];

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

    // Prepare the 6 branches
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    // Set the branch texture
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        // Set the origin to center
        branches[i].setOrigin(220, 20);
    }
    // prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);

    //Player starts on the right
    side playerSide = side::RIGHT;

    // Gravestone
    Texture textureGravestone;
    textureGravestone.loadFromFile("graphics/RIP.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureGravestone);
    spriteRIP.setPosition(600, 860);

    //Axe
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    //Line up axe and tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    //Log
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    //Other log variables
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    bool acceptInput(false);

    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);

    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);

    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    Sound oot;
    oot.setBuffer(ootBuffer);

    // The game loop
    while (window.isOpen())
    {   
        /*
        *************************
        Player input handling
        *************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased && !paused)
            {
                acceptInput = true;

                spriteAxe.setPosition(2000,
                    spriteAxe.getPosition().y);
            }
        }

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

            //make all the branches disappear
            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                branchPositions[i] = side::NONE;
            }
            spriteRIP.setPosition(675, 2000);
            spritePlayer.setPosition(580, 720);
            acceptInput = true;
        }

        if (acceptInput)
        {
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                // Set the player to the right
                playerSide = side::RIGHT;

                // Increase the score
                score++;

                // Add time that gets smaller with better scores
                timeRemaining += (2 / score) + .15;

                // Move the axe with the sprite
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);

                // Move the player sprite
                spritePlayer.setPosition(1200, 720);

                //update the branches
                updateBranches(score);

                // Send the log flying
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;

                // Only accept input once
                acceptInput = false;
                chop.play();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                // Set the player to the left
                playerSide = side::LEFT;

                // Increase the score
                score++;

                // Add time that gets smaller with better scores
                timeRemaining += (2 / score) + .15;

                // Move the axe with the sprite
                spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);

                // Move the player sprite
                spritePlayer.setPosition(580, 720);

                //update the branches
                updateBranches(score);

                // Send the log flying
                spriteLog.setPosition(810, 720);
                logSpeedX = 5000;
                logActive = true;

                // Only accept input once
                acceptInput = false;

                //play sound effect
                chop.play();
            }
        }
       
        /*
        *************************
        Update the scene
        *************************
        */

        // Measure time
        Time dt = clock.restart();
        if (logActive)
        {
            spriteLog.setPosition(
                spriteLog.getPosition().x +
                (logSpeedX * dt.asSeconds()),
                spriteLog.getPosition().y +
                (logSpeedY * dt.asSeconds()));
            if (spriteLog.getPosition().x < -100 ||
                spriteLog.getPosition().x > 2000)
            {
                logActive = false;
                spriteLog.setPosition(810, 720);
            }
        }
        if (branchPositions[5] == playerSide)
        {
            paused = true;
            acceptInput = false;

            spriteRIP.setPosition(525, 760);
            spritePlayer.setPosition(2000, 660);
            playerSide = side::NONE;

            messageText.setString("Squished!");

            FloatRect textRect = messageText.getLocalBounds();
            messageText.setOrigin(textRect.left +
                textRect.width / 2.0f,
                textRect.top +
                textRect.height / 2.0f);
            messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            death.play();
            playerSide = side::RIGHT;
        }

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
                oot.play();
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
                float height = (rand() % 100) + 100;
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
                srand((int)time(0) * 15);
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
                srand((int)time(0) * 20);
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

            // Update the branch sprites
            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT)
                {
                    // Move sprites left
                    branches[i].setPosition(610, height);
                    // Make them face the correct way
                    branches[i].setRotation(180);
                }
                else if (branchPositions[i] == side::RIGHT)
                {
                    // move sprite to the right
                    branches[i].setPosition(1330, height);

                    // Make it face the correct way
                    branches[i].setRotation(0);
                }
                else
                {
                    //hide the branch
                    branches[i].setPosition(3000, height);
                }
            }
            
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

            // Draw the branches
            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                window.draw(branches[i]);
            }
            
            //Draw the player
            window.draw(spritePlayer);

            //Draw the axe
            window.draw(spriteAxe);

            //Draw the log
            window.draw(spriteLog);

            //Draw the gravestone
            window.draw(spriteRIP);

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

void updateBranches(int seed)
{
    // move the branches move down 1 position at a time
    for (int j = NUM_BRANCHES - 1;j > 0; j--)
    {
        branchPositions[j] = branchPositions[j - 1];
    }
    // Spawn a new branch at position 0
    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r)
    {
    case 0:
        branchPositions[0] = side::LEFT;
        break;
    case 1:
        branchPositions[1] = side::RIGHT;
        break;
    default:
        branchPositions[0] = side::NONE;
        break;
    }
}
