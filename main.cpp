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
    sf::Texture texturemenu;
    sf::Sprite spritemenu;
  int chanceturn=0;
  bool isCollide=false;

    int n = 0;
    bool showmenu = false;
    static int count;
    char enemyImages[5][100] = {"van.png", "taxi.png", "semi_trailer.png", "pickup_truck.png"};

public:
    // set the texture
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
            sprite.move(sf::Vector2f(0, -4));
          
        }
    }
    void move_right()
    {
        if (sprite.getPosition().y < 490)
        {
            sprite.move(sf::Vector2f(0, 4));
       
        }
    }
    void move_down()
    {
        if (sprite.getPosition().y > 100)
        {
            sprite.move(sf::Vector2f(-6, 0));

         
        }
    }

    sf::Sprite returnme()
    {
        return sprite;
    }

    void create_Enemy()
    {
        n = 0;
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
            while (n == 0)
            {
                music.pause();
                chanceturn++;
                isCollide=true;
                std::cout<<chanceturn;               

                std::cout << "game over";
                n = 1;
            }
        }
        else
        {

         
            spriteenemy.move(sf::Vector2f(-5, 0));
            isCollide==false;
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

    // menu stups

    void setmenu()
    {

        // setting up the texture
        texturemenu.setRepeated(true);

        // loading the texture
        if (!texturemenu.loadFromFile("final.jpg"))
        {
            std::cout << "Error in loading the page " << std::endl;
        }
        //  spritemenu.setPosition(0, 0);
        spritemenu.setTexture(texturemenu);
    }

    sf::Sprite return_menu()
    {
        return spritemenu;
    }

    void togglemenu()
    {
        if (showmenu)
        {
            showmenu = false;
        }
        else
        {
            showmenu = true;
        }
    }

    bool return_showmenu()
    {
        return showmenu;
    }


    int return_gameChance(){
        return chanceturn;
    }


   bool return_isCollide(){
    return isCollide;
   }

   void set_isCollideFalse(){
    isCollide=false;
   }


void setGameChance(){
        chanceturn=0;
    }












    
};

int Game::count;



















int main()
{
    // show or hide the menu
    int show = 1;
    int score1 = 0;
    int finalscore=0;
    int chance=0;
    bool isgameover=false;
    sf::RenderWindow window(sf::VideoMode(600, 600), "Parallax Example",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // class instance
    Game g1;
    g1.set_Texture();
    g1.create_Enemy();

    // here
    g1.setmenu();
    // backgound logic

    //   score board
    sf::Font font;
    font.loadFromFile("Real Delight.ttf");

    // Create a text
    sf::Text text(std::to_string(score1), font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);


// gamechance logic
 sf::Font fontchance;

    fontchance.loadFromFile("Real Delight.ttf");

    // Create a text
    
    sf::Text textchance(std::to_string(g1.return_gameChance()), fontchance);
    textchance.setCharacterSize(30);
    textchance.setStyle(sf::Text::Bold);
    textchance.setFillColor(sf::Color::Red);
    textchance.setPosition(sf::Vector2f(800,200));

// background image for the score board 
 // setting up the texture
 sf::Texture scorebackground;
 sf::Sprite scoreBackImage;
    scorebackground.setRepeated(true);

        // loading the texture
        if (!scorebackground.loadFromFile("chance.jpg"))
        {
            std::cout << "Error in loading the page " << std::endl;
        }
        //  spritemenu.setPosition(0, 0);
        scoreBackImage.setTexture(scorebackground);






// final score
  sf::Font finalscorefont;
    finalscorefont.loadFromFile("Real Delight.ttf");

    // Create a text
    sf::Text finalscoretext("Play", finalscorefont);
    finalscoretext.setCharacterSize(30);
    finalscoretext.setStyle(sf::Text::Bold);
    finalscoretext.setFillColor(sf::Color::Red);
    finalscoretext.setPosition(sf::Vector2f{ window.getSize() / 3u });










// background logic
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
        
      
          if(g1.return_isCollide()&& g1.return_gameChance()<3&& show!=3){       
        show=3;
            std::cout<<"wow";
        }
    if(g1.return_gameChance()>=3){
        g1.setGameChance();
        g1.set_isCollideFalse();
        show=1;
       
        

        score1=0;

       

    }
           sf::Text textchance(std::to_string(g1.return_gameChance())+" time you have collided \n press enter to continue", fontchance);

         
          g1.return_gameChance()>=3?score1=0:score1++;
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
                case sf::Keyboard::Down:
                    g1.move_down();
                    break;
                case sf::Keyboard::Up:
                    g1.set_isCollideFalse();
                    show=2;
                    isgameover=true;
                    

                    break;
               
                 
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
               std::cout<<sf::Mouse::getPosition().x << sf::Mouse::getPosition().y;


                if (sf::Mouse::getPosition().x > 1025 && sf::Mouse::getPosition().x < 1122 && sf::Mouse::getPosition().y > 576 && sf::Mouse::getPosition().y < 672)
                {

                    std::cout << "done" << std::endl;
                    score1=0;
                    show = 2;
                }
            }
        }

        // I set an arbitrary value as the offset, you'd calculate this based on camera position
        parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() / 2);

        if (show==2)
        {

            g1.move_Enemy();
            window.clear(sf::Color::Red);
            window.draw(sprite, &parallaxShader);
            window.draw(g1.returnme());
            window.draw(g1.return_Enemy());
            window.draw(text);
           
            
        }
        else if (show==1)
        {
            window.draw(scoreBackImage);
            window.draw(g1.return_menu());
           

          
        }else if(show==3){
            window.draw(scoreBackImage);
            window.draw(textchance);         
        }
    


        window.display();
    }
    return 0;
}

// kosari logic launa 