#include <iostream>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "animation viewer");

    int numRows = 1;
    int numCols = 10;

    sf::Texture texture;
    if(!texture.loadFromFile("player_run.png"))
    {
        return EXIT_FAILURE;
    }

    sf::Sprite sprite(texture);
    sprite.setPosition(10, 10);
    
    int spriteSheetWidth = texture.getSize().x; // Width of the sprite sheet
    int spriteSheetHeight = texture.getSize().y; // Height of the sprite sheet
    int cellWidth = spriteSheetWidth / numCols;
    int cellHeight = spriteSheetHeight / numRows;

    // Define the border for the sprite sheet
    sf::RectangleShape border(sf::Vector2f(spriteSheetWidth, spriteSheetHeight));
    border.setPosition(10, 10);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(1);

    // sf::Font font;
    // if (!font.loadFromFile("Anonymous_Pro.ttf"))
    //     return EXIT_FAILURE;
    // sf::Text text("Hello SFML", font, 50);

    // Use something like this for when animating
    // sprite.setTextureRect(sf::IntRect(0, 0, 50, 50)); // Set the rectangle to (0,0) with width 50 and height 50
    
    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Right)
                    {
                        numCols++;
                        cellWidth = spriteSheetWidth / numCols;
                    }
                    else if(event.key.code == sf::Keyboard::Left)
                    {
                        numCols--;
                        cellWidth = spriteSheetWidth / numCols;
                    }
                    else if(event.key.code == sf::Keyboard::Up)
                    {
                        numRows++;
                        cellHeight = spriteSheetHeight / numRows;
                    }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        numRows --;
                        cellHeight = spriteSheetHeight / numRows;
                    }
                default:
                    break;
            }
        }

        window.clear();

        window.draw(sprite);
        window.draw(border);

        // window.draw(text);

        // Draw vertical lines
        for (int col = 1; col < numCols; col++)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(10 + col * cellWidth, 10)),
                sf::Vertex(sf::Vector2f(10 + col * cellWidth, 10 + spriteSheetHeight))
            };

            window.draw(line, 2, sf::Lines);
        }

        // Draw horizontal lines
        for (int row = 1; row < numRows; row++)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(10, 10 + row * cellHeight)),
                sf::Vertex(sf::Vector2f(10 + spriteSheetWidth, 10 + row * cellHeight))
            };

            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }
    
    return EXIT_SUCCESS;
}