#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

#define SPRITESHEET_POS_X 5
#define SPRITESHEET_POS_Y 5

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "animation viewer");

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

    sf::Color gray(144, 144, 144, 255);
    sf::Color brown_one(38, 18, 20, 255);
    sf::Color brown_two(77, 44, 41, 255);
    sf::Color brown_three(120, 67, 44, 255);
    sf::Color brown_four(181, 117, 74, 255);
    sf::Color brown_five(209, 163, 138, 255);

    sf::Sprite spritesheet(texture);
    spritesheet.setPosition(SPRITESHEET_POS_X, SPRITESHEET_POS_Y);

    sf::Sprite frameSprite(texture);
    frameSprite.setPosition(10, 360);
    
    int spriteSheetWidth = texture.getSize().x;
    int spriteSheetHeight = texture.getSize().y;
    int cellWidth = spriteSheetWidth / numCols;
    int cellHeight = spriteSheetHeight / numRows;

    sf::RectangleShape spritesheetBackground(sf::Vector2f(650, 350));
    spritesheetBackground.setPosition(0, 0);
    spritesheetBackground.setFillColor(brown_one);
    spritesheetBackground.setOutlineColor(sf::Color::Black);
    spritesheetBackground.setOutlineThickness(3);

    sf::RectangleShape frameSpriteBackground(sf::Vector2f(650, 230));
    frameSpriteBackground.setPosition(0, 350);
    frameSpriteBackground.setFillColor(brown_one);
    frameSpriteBackground.setOutlineColor(sf::Color::Black);
    frameSpriteBackground.setOutlineThickness(3);

    sf::RectangleShape configBackground(sf::Vector2f(150, 600));
    configBackground.setPosition(650, 0);
    configBackground.setFillColor(brown_two);
    configBackground.setOutlineColor(sf::Color::Black);
    configBackground.setOutlineThickness(3);

    sf::RectangleShape spritesheetBorder(sf::Vector2f(spriteSheetWidth, spriteSheetHeight));
    spritesheetBorder.setPosition(SPRITESHEET_POS_X, SPRITESHEET_POS_Y);
    spritesheetBorder.setFillColor(sf::Color::Transparent);
    spritesheetBorder.setOutlineColor(gray);
    spritesheetBorder.setOutlineThickness(1);

    sf::RectangleShape frameBorder(sf::Vector2f(spriteSheetWidth, spriteSheetHeight));
    frameBorder.setPosition(10, 360);
    frameBorder.setFillColor(sf::Color::Transparent);
    frameBorder.setOutlineColor(gray);
    frameBorder.setOutlineThickness(1);

    sf::ConvexShape increaseRowsButton;
    increaseRowsButton.setPointCount(3);
    increaseRowsButton.setPoint(0, sf::Vector2f(770, 10));
    increaseRowsButton.setPoint(1, sf::Vector2f(760, 25));
    increaseRowsButton.setPoint(2, sf::Vector2f(780, 25));
    increaseRowsButton.setFillColor(brown_five);
    increaseRowsButton.setOutlineColor(sf::Color::White);
    increaseRowsButton.setOutlineThickness(1);

    sf::ConvexShape decreaseRowsButton;
    decreaseRowsButton.setPointCount(3);
    decreaseRowsButton.setPoint(0, sf::Vector2f(760, 30));
    decreaseRowsButton.setPoint(1, sf::Vector2f(780, 30));
    decreaseRowsButton.setPoint(2, sf::Vector2f(770, 45));
    decreaseRowsButton.setFillColor(brown_five);
    decreaseRowsButton.setOutlineColor(sf::Color::White);
    decreaseRowsButton.setOutlineThickness(1);

    sf::ConvexShape increaseColsButton;
    increaseColsButton.setPointCount(3);
    increaseColsButton.setPoint(0, sf::Vector2f(770, 60));
    increaseColsButton.setPoint(1, sf::Vector2f(760, 75));
    increaseColsButton.setPoint(2, sf::Vector2f(780, 75));
    increaseColsButton.setFillColor(brown_five);
    increaseColsButton.setOutlineColor(sf::Color::White);
    increaseColsButton.setOutlineThickness(1);

    sf::ConvexShape decreaseColsButton;
    decreaseColsButton.setPointCount(3);
    decreaseColsButton.setPoint(0, sf::Vector2f(760, 80));
    decreaseColsButton.setPoint(1, sf::Vector2f(780, 80));
    decreaseColsButton.setPoint(2, sf::Vector2f(770, 95));
    decreaseColsButton.setFillColor(brown_five);
    decreaseColsButton.setOutlineColor(sf::Color::White);
    decreaseColsButton.setOutlineThickness(1);

    sf::CircleShape zoomOutButton;
    zoomOutButton.setRadius(12);
    zoomOutButton.setFillColor(brown_five);
    zoomOutButton.setPosition(690, 120);
    zoomOutButton.setOutlineColor(sf::Color::White);
    zoomOutButton.setOutlineThickness(1);

    sf::CircleShape zoomInButton;
    zoomInButton.setRadius(12);
    zoomInButton.setFillColor(brown_five);
    zoomInButton.setPosition(740, 120);
    zoomInButton.setOutlineColor(sf::Color::White);
    zoomInButton.setOutlineThickness(1);

    sf::RectangleShape minus(sf::Vector2f(20, 2));
    minus.setFillColor(sf::Color::White);
    minus.setPosition(zoomOutButton.getPosition().x + zoomOutButton.getRadius() - minus.getSize().x / 2,
                      zoomOutButton.getPosition().y + zoomOutButton.getRadius() - minus.getSize().y / 2);

    sf::RectangleShape plusHorizontal(sf::Vector2f(20, 2));
    plusHorizontal.setFillColor(sf::Color::White);
    plusHorizontal.setPosition(zoomInButton.getPosition().x + zoomInButton.getRadius() - plusHorizontal.getSize().x / 2,
                               zoomInButton.getPosition().y + zoomInButton.getRadius() - plusHorizontal.getSize().y / 2);

    sf::RectangleShape plusVertical(sf::Vector2f(2, 20));
    plusVertical.setFillColor(sf::Color::White);
    plusVertical.setPosition(zoomInButton.getPosition().x + zoomInButton.getRadius() - plusVertical.getSize().x / 2,
                             zoomInButton.getPosition().y + zoomInButton.getRadius() - plusVertical.getSize().y / 2);
    
    sf::Font font;
    if(!font.loadFromFile("Anonymous_Pro.ttf"))
    {
        return EXIT_FAILURE;
    }

    sf::Text rowsDisplayString("ROWS:" + std::to_string(numRows), font, 24);
    rowsDisplayString.setPosition(660, 10);
    sf::Text colsDisplayString("COLS:" + std::to_string(numCols), font, 24);
    colsDisplayString.setPosition(660, 60);
    sf::Text frameSizeDisplayString("FRAME:" + std::to_string(cellWidth) + "x" + std::to_string(cellHeight), font, 16);
    frameSizeDisplayString.setPosition(5, 580);
    sf::Text scaleDisplayString("SCALE:" + std::to_string(scaleFactor), font, 16);
    scaleDisplayString.setPosition(125, 580);
    
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
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                        if(increaseRowsButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            numRows++;
                            cellHeight = spriteSheetHeight / numRows;
                            rowsDisplayString.setString("ROWS:" + std::to_string(numRows));
                            frameSizeDisplayString.setString("FRAME:" + std::to_string(cellWidth) + "x" + std::to_string(cellHeight));
                            frameBorder.setSize(sf::Vector2f(cellWidth, cellHeight));
                            frameSprite.setTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
                        }
                        else if(decreaseRowsButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            if(numRows > 1)
                            {
                                numRows--;
                                cellHeight = spriteSheetHeight / numRows;
                                rowsDisplayString.setString("ROWS:" + std::to_string(numRows));
                                frameSizeDisplayString.setString("FRAME:" + std::to_string(cellWidth) + "x" + std::to_string(cellHeight));
                                frameBorder.setSize(sf::Vector2f(cellWidth, cellHeight));
                                frameSprite.setTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
                            }
                        }
                        else if(increaseColsButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            numCols++;
                            cellWidth = spriteSheetWidth / numCols;
                            colsDisplayString.setString("COLS:" + std::to_string(numCols));
                            frameSizeDisplayString.setString("FRAME:" + std::to_string(cellWidth) + "x" + std::to_string(cellHeight));
                            frameBorder.setSize(sf::Vector2f(cellWidth, cellHeight));
                            frameSprite.setTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
                        }
                        else if(decreaseColsButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            if(numCols > 1)
                            {
                                numCols--;
                                cellWidth = spriteSheetWidth / numCols;
                                colsDisplayString.setString("COLS:" + std::to_string(numCols));
                                frameSizeDisplayString.setString("FRAME:" + std::to_string(cellWidth) + "x" + std::to_string(cellHeight));
                                frameBorder.setSize(sf::Vector2f(cellWidth, cellHeight));
                                frameSprite.setTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
                            }
                        }
                        else if(zoomOutButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            if(scaleFactor > 0.6)
                            {
                                scaleFactor = scaleFactor - 0.1;
                                spritesheet.setScale(scaleFactor, scaleFactor);
                                spritesheetBorder.setScale(scaleFactor, scaleFactor);
                                scaleDisplayString.setString("SCALE:" + std::to_string(scaleFactor));
                            }
                        }
                        else if(zoomInButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            scaleFactor = scaleFactor + 0.1;
                            spritesheet.setScale(scaleFactor, scaleFactor);
                            spritesheetBorder.setScale(scaleFactor, scaleFactor);
                            scaleDisplayString.setString("SCALE:" + std::to_string(scaleFactor));
                        }
                    }
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
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

        window.draw(spritesheetBackground);
        window.draw(frameSpriteBackground);
        
        window.draw(spritesheet);
        window.draw(spritesheetBorder);
        window.draw(frameSprite);
        window.draw(frameBorder);

        // Draw column splits
        for (int col = 1; col < numCols; col++)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(SPRITESHEET_POS_X + col * (cellWidth * scaleFactor), SPRITESHEET_POS_Y), gray),
                sf::Vertex(sf::Vector2f(SPRITESHEET_POS_X + col * (cellWidth * scaleFactor), SPRITESHEET_POS_Y + (spriteSheetHeight * scaleFactor)), gray)
            };

            window.draw(line, 2, sf::Lines);
        }

        // Draw row splits
        for (int row = 1; row < numRows; row++)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(SPRITESHEET_POS_X, SPRITESHEET_POS_Y + row * (cellHeight * scaleFactor)), gray),
                sf::Vertex(sf::Vector2f(SPRITESHEET_POS_X + (spriteSheetWidth * scaleFactor), SPRITESHEET_POS_Y + row * (cellHeight * scaleFactor)), gray)
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

        window.draw(configBackground);
        window.draw(increaseRowsButton);
        window.draw(decreaseRowsButton);
        window.draw(increaseColsButton);
        window.draw(decreaseColsButton);
        window.draw(zoomOutButton);
        window.draw(zoomInButton);
        window.draw(minus);
        window.draw(plusHorizontal);
        window.draw(plusVertical);

        window.draw(rowsDisplayString);
        window.draw(colsDisplayString);
        window.draw(scaleDisplayString);
        window.draw(frameSizeDisplayString);

        window.display();
    }
    
    return EXIT_SUCCESS;
}