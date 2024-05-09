#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#define START_POS_X 10
#define START_POS_Y 50

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "animation viewer");

    int numRows = 1;
    int numCols = 1;
    float scaleFactor = 1.0;
    bool animationPlaying = false;
    int currFrameX = 0;
    int currFrameY = 0;

    sf::Clock clock;
    float frameDuration = 0.2f;

    sf::Texture texture;
    if(!texture.loadFromFile("player_run.png"))
    {
        return EXIT_FAILURE;
    }

    sf::Sprite sprite(texture);
    sprite.setPosition(START_POS_X, START_POS_Y);

    sf::Sprite frameSprite(texture);
    frameSprite.setPosition(10, 250);
    
    int spriteSheetWidth = texture.getSize().x;
    int spriteSheetHeight = texture.getSize().y;
    int cellWidth = spriteSheetWidth / numCols;
    int cellHeight = spriteSheetHeight / numRows;

    sf::RectangleShape border(sf::Vector2f(spriteSheetWidth, spriteSheetHeight));
    border.setPosition(START_POS_X, START_POS_Y);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(1);

    sf::RectangleShape frameBorder(sf::Vector2f(spriteSheetWidth, spriteSheetHeight));
    frameBorder.setPosition(10, 250);
    frameBorder.setFillColor(sf::Color::Transparent);
    frameBorder.setOutlineColor(sf::Color::White);
    frameBorder.setOutlineThickness(1);
    
    sf::Font font;
    if(!font.loadFromFile("Anonymous_Pro.ttf"))
    {
        return EXIT_FAILURE;
    }

    sf::Text rowsDisplayString("ROWS:" + std::to_string(numRows), font, 24);
    sf::Text colsDisplayString("COLS:" + std::to_string(numCols), font, 24);
    rowsDisplayString.setPosition(5, 5);
    colsDisplayString.setPosition(100, 5);

    sf::Text scaleDisplayString("SCALE:" + std::to_string(scaleFactor), font, 24);
    scaleDisplayString.setPosition(220, 5);

    sf::Text frameSizeDisplayString("FRAME:" + std::to_string(cellWidth) + "x" + std::to_string(cellHeight), font, 24);
    frameSizeDisplayString.setPosition(420, 5);
    
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
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Q:
                            numCols++;
                            cellWidth = spriteSheetWidth / numCols;
                            colsDisplayString.setString("COLS:" + std::to_string(numCols));
                            frameSizeDisplayString.setString("FRAME:" + std::to_string(cellWidth) + "x" + std::to_string(cellHeight));
                            frameBorder.setSize(sf::Vector2f(cellWidth, cellHeight));
                            frameSprite.setTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
                            break;
                        case sf::Keyboard::A:
                            if(numCols > 1)
                            {
                                numCols--;
                                cellWidth = spriteSheetWidth / numCols;
                                colsDisplayString.setString("COLS:" + std::to_string(numCols));
                                frameSizeDisplayString.setString("FRAME:" + std::to_string(cellWidth) + "x" + std::to_string(cellHeight));
                                frameBorder.setSize(sf::Vector2f(cellWidth, cellHeight));
                                frameSprite.setTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
                            }
                            break;
                        case sf::Keyboard::W:
                            numRows++;
                            cellHeight = spriteSheetHeight / numRows;
                            rowsDisplayString.setString("ROWS:" + std::to_string(numRows));
                            frameSizeDisplayString.setString("FRAME:" + std::to_string(cellWidth) + "x" + std::to_string(cellHeight));
                            frameBorder.setSize(sf::Vector2f(cellWidth, cellHeight));
                            frameSprite.setTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
                            break;
                        case sf::Keyboard::S:
                            if(numRows > 1)
                            {
                                numRows--;
                                cellHeight = spriteSheetHeight / numRows;
                                rowsDisplayString.setString("ROWS:" + std::to_string(numRows));
                                frameSizeDisplayString.setString("FRAME:" + std::to_string(cellWidth) + "x" + std::to_string(cellHeight));
                                frameBorder.setSize(sf::Vector2f(cellWidth, cellHeight));
                                frameSprite.setTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
                            }
                            break;
                        case sf::Keyboard::Up:
                            scaleFactor = scaleFactor + 0.1;
                            sprite.setScale(scaleFactor, scaleFactor);
                            border.setScale(scaleFactor, scaleFactor);
                            scaleDisplayString.setString("SCALE:" + std::to_string(scaleFactor));
                            break;
                        case sf::Keyboard::Down:
                            if(scaleFactor > 0.6)
                            {
                                scaleFactor = scaleFactor - 0.1;
                                sprite.setScale(scaleFactor, scaleFactor);
                                border.setScale(scaleFactor, scaleFactor);
                            scaleDisplayString.setString("SCALE:" + std::to_string(scaleFactor));
                            }
                        case sf::Keyboard::Z:
                            animationPlaying = !animationPlaying;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        window.clear();

        window.draw(sprite);
        window.draw(border);
        window.draw(frameSprite);
        window.draw(frameBorder);

        window.draw(rowsDisplayString);
        window.draw(colsDisplayString);
        window.draw(scaleDisplayString);
        window.draw(frameSizeDisplayString);

        // Draw column splits
        for (int col = 1; col < numCols; col++)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(START_POS_X + col * (cellWidth * scaleFactor), START_POS_Y)),
                sf::Vertex(sf::Vector2f(START_POS_X + col * (cellWidth * scaleFactor), START_POS_Y + (spriteSheetHeight * scaleFactor)))
            };

            window.draw(line, 2, sf::Lines);
        }

        // Draw row splits
        for (int row = 1; row < numRows; row++)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(START_POS_X, START_POS_Y + row * (cellHeight * scaleFactor))),
                sf::Vertex(sf::Vector2f(START_POS_X + (spriteSheetWidth * scaleFactor), START_POS_Y + row * (cellHeight * scaleFactor)))
            };

            window.draw(line, 2, sf::Lines);
        }

        if (animationPlaying && clock.getElapsedTime().asSeconds() > frameDuration) {
            // Move to the next frame
            currFrameX++;
            if (currFrameX >= numCols) {
                currFrameX = 0;
                currFrameY++;
                if (currFrameY >= numRows) {
                    currFrameY = 0; // Loop back to the first frame
                }
            }

            // Set the new texture rectangle for the current frame
            frameSprite.setTextureRect(sf::IntRect(currFrameX * cellWidth, currFrameY * cellHeight, cellWidth, cellHeight));

            // Reset the clock for the next frame
            clock.restart();
        }

        window.display();
    }
    
    return EXIT_SUCCESS;
}