#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Game
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Texture textureenemy;
    sf::Sprite spriteenemy;
    sf::Music music;
    sf::Music crash;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    static int count;
    char enemyImages[5][100] = {"van.png", "taxi.png", "semi_trailer.png", "pickup_truck.png"};

public:
    void set_Texture()
    {
        if (!music.openFromFile("background.mp3"))
        {
            std::cout << "ERROR ERROR :" << std::endl;
        }
        if (!crash.openFromFile("crash.mp3"))
        {
            std::cout << "ERROR ERROR :" << std::endl;
        }
    
        music.play();
        crash.play();
        crash.setVolume(0);

        // setting up the texture
        texture.setRepeated(false);

        // loading the texture
        if (!texture.loadFromFile("car.png"))
        {
            std::cout << "Error in loading the page " << std::endl;
        }
        sprite.setTexture(texture);
        // positive number in x axis goes right for y down
        sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * 0.5, sprite.getTexture()->getSize().y * 0.5));

        // // setting up the car position
        // sprite.setTextureRect(sf::IntRect(0, 0, 100, 200));

        // setting up the sprite position
        sprite.setPosition(sf::Vector2f(120, 190));
    }

    void move_left()
    {
        if (sprite.getPosition().y > 230)
        {
            sprite.move(sf::Vector2f(0, -10));
            std::cout << "the x postion of the right  sprite is " << spriteenemy.getPosition().x << " " << spriteenemy.getPosition().y << std::endl;
            std::cout << "the y postion of the left sprite is " << sprite.getPosition().y << std::endl;
        }
    }
    void move_right()
    {
        if (sprite.getPosition().y < 490)
        {
            sprite.move(sf::Vector2f(0, 10));
            std::cout << "the x postion of the right  sprite is " << spriteenemy.getPosition().x << " " << spriteenemy.getPosition().y << std::endl;
            std::cout << "the y postion of the sprite right  is " << sprite.getPosition().y << std::endl;
        }
    }
    void move_down()
    {
        if (sprite.getPosition().y > 100)
        {
            sprite.move(sf::Vector2f(-10, 0));

            std::cout << "the x postion of the right  sprite is " << sprite.getPosition().x << std::endl;
            std::cout << "the y postion of the sprite right  is " << sprite.getPosition().y << std::endl;
        }
    }

    sf::Sprite returnme()
    {
        return sprite;
    }

    void create_Enemy()
    {
        // no repetation
        textureenemy.setRepeated(false);

        //    loading the car image
        if (!textureenemy.loadFromFile(enemyImages[count]))
        {
            std::cout << "Error in loading the page " << std::endl;
        }
        count++;
        spriteenemy.setTexture(textureenemy);

        // random number logic
        int diff = 490 - 230;
        int a = rand() % diff + 230;
        ;

        std::cout << a << std::endl;

        // setting up the sprite position
        spriteenemy.setPosition(sf::Vector2f(490, a));

        if (count > 3)
        {
            count = 0;
        }
        else
        {
            count++;
        }
    }

    void move_Enemy()
    {
        if (sprite.getGlobalBounds().intersects(spriteenemy.getGlobalBounds()))
        {
     music.pause();       
     if(crash.getStatus() != sf::Music::Status::Playing){

        crash.setVolume(100);
      crash.play();
     }
        crash.setVolume(100);

  

            std::cout << "game over";
        }
        else
        {

            std::cout << "the y postion of the sprite right  is "
                      << "y=" << spriteenemy.getPosition().y << "x= " << spriteenemy.getPosition().x << std::endl;
            spriteenemy.move(sf::Vector2f(-5, 0));
        }

        if (spriteenemy.getPosition().x == -80)
        {
            spriteenemy.move(sf::Vector2f(490, 230));
            create_Enemy();
        }
    }

    sf::Sprite return_Enemy()
    {
        return spriteenemy;
    }
};

int Game::count;

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Parallax Example",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // class instance
    Game g1;
    g1.set_Texture();
    g1.create_Enemy();

    // backgound logic

    sf::Texture texture;
    if (!texture.loadFromFile("roooad.png"))
    {

        std::cout << "Error in loading the page " << std::endl;
    }
    texture.setRepeated(true);
    sf::Sprite sprite(texture);
    sprite.setPosition(0, 0);

    sf::Shader parallaxShader;
    parallaxShader.loadFromMemory(
        "uniform float offset;"

        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;" // magic
        "    gl_FrontColor = gl_Color;"
        "}",
        sf::Shader::Vertex);

    float offset = 0.f;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
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
                case sf::Keyboard::Down:
                    g1.move_down();
                    break;
                }
            }
        }

        // I set an arbitrary value as the offset, you'd calculate this based on camera position
        parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() / 2);

        g1.move_Enemy();
        window.clear(sf::Color::Red);
        window.draw(sprite, &parallaxShader);
        window.draw(g1.returnme());
        window.draw(g1.return_Enemy());
        window.display();
    }
    return 0;
}