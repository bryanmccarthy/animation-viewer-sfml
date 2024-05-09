#include <iostream>
#include <SFML/Graphics.hpp>

#define START_POS_X 10
#define START_POS_Y 50

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "animation viewer");

    int numRows = 1;
    int numCols = 1;
    float scaleFactor = 1.0;

    sf::Texture texture;
    if(!texture.loadFromFile("player_run.png"))
    {
        return EXIT_FAILURE;
    }

    sf::Sprite sprite(texture);
    sprite.setPosition(START_POS_X, START_POS_Y);
    
    int spriteSheetWidth = texture.getSize().x; // Width of the sprite sheet
    int spriteSheetHeight = texture.getSize().y; // Height of the sprite sheet
    int cellWidth = spriteSheetWidth / numCols;
    int cellHeight = spriteSheetHeight / numRows;

    // Define the border for the sprite sheet
    sf::RectangleShape border(sf::Vector2f(spriteSheetWidth, spriteSheetHeight));
    border.setPosition(START_POS_X, START_POS_Y);
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
                    if(event.key.code == sf::Keyboard::Q)
                    {
                        numCols++;
                        cellWidth = spriteSheetWidth / numCols;
                    }
                    else if(event.key.code == sf::Keyboard::A)
                    {
                        if(numCols > 1)
                        {
                            numCols--;
                            cellWidth = spriteSheetWidth / numCols;
                        }
                    }
                    else if(event.key.code == sf::Keyboard::W)
                    {
                        numRows++;
                        cellHeight = spriteSheetHeight / numRows;
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        if(numRows > 1)
                        {
                            numRows--;
                            cellHeight = spriteSheetHeight / numRows;
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Up)
                    {
                        scaleFactor = scaleFactor + 0.1;
                        sprite.setScale(scaleFactor, scaleFactor);
                        border.setScale(scaleFactor, scaleFactor);
                        std::cout << "ScaleFactor: " << scaleFactor << std::endl;
                    }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        if(scaleFactor > 0.6)
                        {
                            scaleFactor = scaleFactor - 0.1;
                            sprite.setScale(scaleFactor, scaleFactor);
                            border.setScale(scaleFactor, scaleFactor);
                        }
                        std::cout << "ScaleFactor: " << scaleFactor << std::endl;
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
                sf::Vertex(sf::Vector2f(START_POS_X + col * (cellWidth * scaleFactor), START_POS_Y)),
                sf::Vertex(sf::Vector2f(START_POS_X + col * (cellWidth * scaleFactor), START_POS_Y + (spriteSheetHeight * scaleFactor)))
            };

            window.draw(line, 2, sf::Lines);
        }

        // Draw horizontal lines
        for (int row = 1; row < numRows; row++)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(START_POS_X, START_POS_Y + row * (cellHeight * scaleFactor))),
                sf::Vertex(sf::Vector2f(START_POS_X + (spriteSheetWidth * scaleFactor), START_POS_Y + row * (cellHeight * scaleFactor)))
            };

            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }
    
    return EXIT_SUCCESS;
}