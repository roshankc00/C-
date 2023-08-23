#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "player.h"
#include "moves.h"
#include "enemy.h"
#include "menu.h"




class Game : public Menu
{
protected:
    sf::Texture scorebackground;
    sf::Sprite scoreBackImage;

public:
    int return_gameChance()
    {
        return chanceturn;
    }

    bool return_isCollide()
    {
        return isCollide;
    }

    void set_isCollideFalse()
    {
        isCollide = false;
    }

    void setGameChance()
    {
        chanceturn = 0;
    }

    void set_BackscoreImage()
    {

        scorebackground.setRepeated(true);

        // loading the texture
        if (!scorebackground.loadFromFile("images/black.jpg"))
        {
            std::cout << "Error in loading the page " << std::endl;
        }
        //  spritemenu.setPosition(0, 0);
        scoreBackImage.setTexture(scorebackground);
    }

    sf::Sprite backScoreImage()
    {
        set_BackscoreImage();
        return scoreBackImage;
    }
};






int main()
{
    // show or hide the menu
    int show = 1;
    int score1 = 0;
    int finalscore = 0;
    int chance = 0;
    bool showFinalScore = false;
    bool isgameover = false;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Parallax Example");
    window.setVerticalSyncEnabled(true);

    // class instance
    Game g1;
    g1.set_Texture();
    g1.create_Enemy();

    // here
    g1.setmenu();
    // backgound logic

    // BUTTON TESTING

    sf::Font fontb;
    if (!fontb.loadFromFile("fonts/Real Delight.ttf"))
    {
        return EXIT_FAILURE;
    }

    sf::Text buttonText("  Play now!", fontb, 24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(1450, 805);

    sf::RectangleShape buttonBackground(sf::Vector2f(200, 50));
    buttonBackground.setPosition(1400, 800);
    buttonBackground.setFillColor(sf::Color::Black);

    //   score board
    sf::Font font;
    font.loadFromFile("fonts/Real Delight.ttf");

    // Create a text
    sf::Text text(std::to_string(score1), font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);

    // gamechance logic
    sf::Font fontchance;
    fontchance.loadFromFile("fonts/eBuenaClassic.ttf");

    // Create a text

    sf::Text textchance(std::to_string(g1.return_gameChance()), fontchance);
    textchance.setCharacterSize(30);
    textchance.setStyle(sf::Text::Bold);
    textchance.setFillColor(sf::Color::Red);
    textchance.setPosition(3000, 34000);
    textchance.setCharacterSize(100);

    // background image for the score board
    // setting up the texture

    // final score
    sf::Font finalscorefont;
    finalscorefont.loadFromFile("fonts/Real Delight.ttf");

    // Create a text
    sf::Text finalscoretext("Play", finalscorefont);
    finalscoretext.setCharacterSize(30);
    finalscoretext.setStyle(sf::Text::Bold);
    finalscoretext.setFillColor(sf::Color::Red);
    finalscoretext.setPosition(100, 232);

    // background logic
    sf::Texture texture;
    if (!texture.loadFromFile("images/kxa.jpg"))
    {

        std::cout << "Error in loading the page " << std::endl;
    }
    texture.setRepeated(true);
    sf::Sprite sprite(texture);
    sprite.scale(2, 1.2);

    sf::Shader parallaxShader;
    parallaxShader.loadFromMemory(
        "uniform float offset;"

        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;" 
        "    gl_FrontColor = gl_Color;"
        "}",
        sf::Shader::Vertex);

    float offset = 0.f;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))

            if (g1.return_isCollide() && g1.return_gameChance() < 3 && show != 3)
            {
                show = 3;
                std::cout << "wow";
            }
        if (g1.return_gameChance() >= 3)
        {
            g1.setGameChance();
            g1.set_isCollideFalse();

            show = 1;
            finalscore = score1;

            score1 = 0;
        }
        sf::Text textchance(std::to_string(g1.return_gameChance()) + " time you have collided \n press enter to continue", fontchance);
        textchance.setPosition(window.getSize().x / 2.3, window.getSize().y / 2);

        g1.return_gameChance() >= 3 ? score1 = 0 : score1++;
        sf::Text text("Score :" + std::to_string(score1), font);

        {

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {

                case sf::Keyboard::Left:
                    g1.move_left();
                    break;
                case sf::Keyboard::Right:
                    g1.move_right();
                    break;

                case sf::Keyboard::Up:
                    if (show == 3)
                    {

                        g1.set_isCollideFalse();
                        show = 2;
                    }

                    break;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

                if (buttonBackground.getGlobalBounds().contains(mousePosFloat))
                {
                    std::cout << "done" << std::endl;
                    showFinalScore = true;

                    score1 = 0;
                    show = 2;
                }
            }
        }

        // I set an arbitrary value as the offset, you'd calculate this based on camera position
        parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() / 1.6);

        if (show == 2)
        {

            g1.move_Enemy();
            window.draw(sprite, &parallaxShader);
            window.draw(g1.returnme());
            window.draw(g1.return_Enemy());
            window.draw(text);
        }
        else if (show == 1)
        {
            window.draw(g1.return_menu());
            std::cout << finalscore << std::endl;
            if (showFinalScore)
            {
                sf::Text textchance("\t \t  your score is \n \n \t \t \t \t " + std::to_string(finalscore) + " \n \n click play  to go play again", fontchance);
                textchance.setFillColor(sf::Color::Yellow);
                textchance.setPosition(window.getSize().x / 2.3, 0);

                window.draw(textchance);
            }

            window.draw(buttonBackground);
            window.draw(buttonText);
        }
        else if (show == 3)
        {
            window.draw(g1.backScoreImage());

            window.draw(textchance);
        }

        window.display();
    }
    return 0;
}
