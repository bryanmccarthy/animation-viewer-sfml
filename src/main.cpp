#include "SFML/Graphics/RectangleShape.hpp"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>

#define SPRITESHEET_AREA_WIDTH 650
#define SPRITESHEET_AREA_HEIGHT 350

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "animation viewer");

    sf::Color lineColor(255, 255, 255, 255);
    sf::Color backgroundColor(51, 52, 67, 255);
    sf::Color buttonInnerColor(140, 23, 39, 255);

    int numRows = 1;
    int numCols = 1;
    float spritesheetScaleFactor = 1.0;
    float frameScaleFactor = 1.0;
    bool animationPlaying = false;
    int currFrameX = 0;
    int currFrameY = 0;
    int spritesheet_pos_x;
    int spritesheet_pos_y;

    sf::Clock clock;
    float frameDuration = 0.2f;

    sf::Texture texture;
    if(!texture.loadFromFile("player_run.png"))
    {
        return EXIT_FAILURE;
    }

    int spriteSheetWidth = texture.getSize().x;
    int spriteSheetHeight = texture.getSize().y;
    int cellWidth = spriteSheetWidth / numCols;
    int cellHeight = spriteSheetHeight / numRows;
    spritesheet_pos_x = (SPRITESHEET_AREA_WIDTH / 2) - (spriteSheetWidth / 2);
    spritesheet_pos_y = (SPRITESHEET_AREA_HEIGHT / 2) - (spriteSheetHeight / 2);

    sf::Sprite spritesheet(texture);
    spritesheet.setPosition(spritesheet_pos_x, spritesheet_pos_y);

    sf::Sprite frameSprite(texture);
    frameSprite.setPosition(10, 360);

    sf::RectangleShape spritesheetBackground(sf::Vector2f(650, 350));
    spritesheetBackground.setPosition(0, 0);
    spritesheetBackground.setFillColor(backgroundColor);
    spritesheetBackground.setOutlineColor(sf::Color::Black);
    spritesheetBackground.setOutlineThickness(3);

    sf::RectangleShape frameSpriteBackground(sf::Vector2f(650, 230));
    frameSpriteBackground.setPosition(0, 350);
    frameSpriteBackground.setFillColor(backgroundColor);
    frameSpriteBackground.setOutlineColor(sf::Color::Black);
    frameSpriteBackground.setOutlineThickness(3);

    sf::RectangleShape configBackground(sf::Vector2f(150, 600));
    configBackground.setPosition(650, 0);
    configBackground.setFillColor(backgroundColor);
    configBackground.setOutlineColor(sf::Color::Black);
    configBackground.setOutlineThickness(3);

    sf::RectangleShape spritesheetBorder(sf::Vector2f(spriteSheetWidth, spriteSheetHeight));
    spritesheetBorder.setPosition(spritesheet_pos_x, spritesheet_pos_y);
    spritesheetBorder.setFillColor(sf::Color::Transparent);
    spritesheetBorder.setOutlineColor(lineColor);
    spritesheetBorder.setOutlineThickness(1.5);

    sf::RectangleShape frameBorder(sf::Vector2f(spriteSheetWidth, spriteSheetHeight));
    frameBorder.setPosition(10, 360);
    frameBorder.setFillColor(sf::Color::Transparent);
    frameBorder.setOutlineColor(lineColor);
    frameBorder.setOutlineThickness(1.5);

    sf::ConvexShape increaseRowsButton;
    increaseRowsButton.setPointCount(3);
    increaseRowsButton.setPoint(0, sf::Vector2f(770, 10));
    increaseRowsButton.setPoint(1, sf::Vector2f(760, 25));
    increaseRowsButton.setPoint(2, sf::Vector2f(780, 25));
    increaseRowsButton.setFillColor(buttonInnerColor);
    increaseRowsButton.setOutlineColor(sf::Color::White);
    increaseRowsButton.setOutlineThickness(1);

    sf::ConvexShape decreaseRowsButton;
    decreaseRowsButton.setPointCount(3);
    decreaseRowsButton.setPoint(0, sf::Vector2f(760, 30));
    decreaseRowsButton.setPoint(1, sf::Vector2f(780, 30));
    decreaseRowsButton.setPoint(2, sf::Vector2f(770, 45));
    decreaseRowsButton.setFillColor(buttonInnerColor);
    decreaseRowsButton.setOutlineColor(sf::Color::White);
    decreaseRowsButton.setOutlineThickness(1);

    sf::ConvexShape increaseColsButton;
    increaseColsButton.setPointCount(3);
    increaseColsButton.setPoint(0, sf::Vector2f(770, 60));
    increaseColsButton.setPoint(1, sf::Vector2f(760, 75));
    increaseColsButton.setPoint(2, sf::Vector2f(780, 75));
    increaseColsButton.setFillColor(buttonInnerColor);
    increaseColsButton.setOutlineColor(sf::Color::White);
    increaseColsButton.setOutlineThickness(1);

    sf::ConvexShape decreaseColsButton;
    decreaseColsButton.setPointCount(3);
    decreaseColsButton.setPoint(0, sf::Vector2f(760, 80));
    decreaseColsButton.setPoint(1, sf::Vector2f(780, 80));
    decreaseColsButton.setPoint(2, sf::Vector2f(770, 95));
    decreaseColsButton.setFillColor(buttonInnerColor);
    decreaseColsButton.setOutlineColor(sf::Color::White);
    decreaseColsButton.setOutlineThickness(1);

    sf::ConvexShape increaseFpsButton;
    increaseFpsButton.setPointCount(3);
    increaseFpsButton.setPoint(0, sf::Vector2f(770, 350));
    increaseFpsButton.setPoint(1, sf::Vector2f(760, 365));
    increaseFpsButton.setPoint(2, sf::Vector2f(780, 365));
    increaseFpsButton.setFillColor(buttonInnerColor);
    increaseFpsButton.setOutlineColor(sf::Color::White);
    increaseFpsButton.setOutlineThickness(1);

    sf::ConvexShape decreaseFpsButton;
    decreaseFpsButton.setPointCount(3);
    decreaseFpsButton.setPoint(0, sf::Vector2f(760, 370));
    decreaseFpsButton.setPoint(1, sf::Vector2f(780, 370));
    decreaseFpsButton.setPoint(2, sf::Vector2f(770, 385));
    decreaseFpsButton.setFillColor(buttonInnerColor);
    decreaseFpsButton.setOutlineColor(sf::Color::White);
    decreaseFpsButton.setOutlineThickness(1);

    sf::CircleShape spritesheetZoomOutButton;
    spritesheetZoomOutButton.setRadius(12);
    spritesheetZoomOutButton.setFillColor(buttonInnerColor);
    spritesheetZoomOutButton.setPosition(690, 120);
    spritesheetZoomOutButton.setOutlineColor(sf::Color::White);
    spritesheetZoomOutButton.setOutlineThickness(1);

    sf::CircleShape spritesheetZoomInButton;
    spritesheetZoomInButton.setRadius(12);
    spritesheetZoomInButton.setFillColor(buttonInnerColor);
    spritesheetZoomInButton.setPosition(740, 120);
    spritesheetZoomInButton.setOutlineColor(sf::Color::White);
    spritesheetZoomInButton.setOutlineThickness(1);

    sf::CircleShape frameZoomOutButton;
    frameZoomOutButton.setRadius(12);
    frameZoomOutButton.setFillColor(buttonInnerColor);
    frameZoomOutButton.setPosition(690, 400);
    frameZoomOutButton.setOutlineColor(sf::Color::White);
    frameZoomOutButton.setOutlineThickness(1);

    sf::CircleShape frameZoomInButton;
    frameZoomInButton.setRadius(12);
    frameZoomInButton.setFillColor(buttonInnerColor);
    frameZoomInButton.setPosition(740, 400);
    frameZoomInButton.setOutlineColor(sf::Color::White);
    frameZoomInButton.setOutlineThickness(1);

    sf::ConvexShape playButton;
    playButton.setPointCount(3);
    playButton.setPoint(0, sf::Vector2f(740, 500));
    playButton.setPoint(1, sf::Vector2f(740, 530));
    playButton.setPoint(2, sf::Vector2f(770, 515));
    playButton.setFillColor(buttonInnerColor);
    playButton.setOutlineColor(sf::Color::White);
    playButton.setOutlineThickness(1);

    sf::RectangleShape pauseButton(sf::Vector2f(30, 30));
    pauseButton.setPosition(690, 500);
    pauseButton.setFillColor(buttonInnerColor);
    pauseButton.setOutlineColor(sf::Color::White);
    pauseButton.setOutlineThickness(1);

    sf::RectangleShape minus(sf::Vector2f(20, 2));
    minus.setFillColor(sf::Color::White);
    minus.setPosition(spritesheetZoomOutButton.getPosition().x + spritesheetZoomOutButton.getRadius() - minus.getSize().x / 2,
                      spritesheetZoomOutButton.getPosition().y + spritesheetZoomOutButton.getRadius() - minus.getSize().y / 2);

    sf::RectangleShape plusHorizontal(sf::Vector2f(20, 2));
    plusHorizontal.setFillColor(sf::Color::White);
    plusHorizontal.setPosition(spritesheetZoomInButton.getPosition().x + spritesheetZoomInButton.getRadius() - plusHorizontal.getSize().x / 2,
                               spritesheetZoomInButton.getPosition().y + spritesheetZoomInButton.getRadius() - plusHorizontal.getSize().y / 2);

    sf::RectangleShape plusVertical(sf::Vector2f(2, 20));
    plusVertical.setFillColor(sf::Color::White);
    plusVertical.setPosition(spritesheetZoomInButton.getPosition().x + spritesheetZoomInButton.getRadius() - plusVertical.getSize().x / 2,
                             spritesheetZoomInButton.getPosition().y + spritesheetZoomInButton.getRadius() - plusVertical.getSize().y / 2);

    sf::RectangleShape frameMinus(sf::Vector2f(20, 2));
    frameMinus.setFillColor(sf::Color::White);
    frameMinus.setPosition(frameZoomOutButton.getPosition().x + frameZoomOutButton.getRadius() - frameMinus.getSize().x / 2,
                      frameZoomOutButton.getPosition().y + frameZoomOutButton.getRadius() - frameMinus.getSize().y / 2);

    sf::RectangleShape framePlusHorizontal(sf::Vector2f(20, 2));
    framePlusHorizontal.setFillColor(sf::Color::White);
    framePlusHorizontal.setPosition(frameZoomInButton.getPosition().x + frameZoomInButton.getRadius() - framePlusHorizontal.getSize().x / 2,
                               frameZoomInButton.getPosition().y + frameZoomInButton.getRadius() - framePlusHorizontal.getSize().y / 2);

    sf::RectangleShape framePlusVertical(sf::Vector2f(2, 20));
    framePlusVertical.setFillColor(sf::Color::White);
    framePlusVertical.setPosition(frameZoomInButton.getPosition().x + frameZoomInButton.getRadius() - framePlusVertical.getSize().x / 2,
                             frameZoomInButton.getPosition().y + frameZoomInButton.getRadius() - framePlusVertical.getSize().y / 2);
    
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
    sf::Text spritesheetScaleDisplayString("SPRITESHEET SCALE:" + std::to_string(spritesheetScaleFactor), font, 16);
    spritesheetScaleDisplayString.setPosition(150, 580);
    sf::Text frameScaleDisplayString("FRAME SCALE:" + std::to_string(frameScaleFactor), font, 16);
    frameScaleDisplayString.setPosition(410, 580);
    sf::Text fpsDisplayString("FPS:" + std::to_string((int)std::round(1.0f / frameDuration)), font, 24);
    fpsDisplayString.setPosition(660, 350);
    
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
                        else if(spritesheetZoomOutButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            if(spritesheetScaleFactor > 0.5)
                            {
                                spritesheetScaleFactor = spritesheetScaleFactor - 0.1;
                                spritesheet.setScale(spritesheetScaleFactor, spritesheetScaleFactor);
                                spritesheetBorder.setScale(spritesheetScaleFactor, spritesheetScaleFactor);
                                spritesheetScaleDisplayString.setString("SPRITESHEET SCALE:" + std::to_string(spritesheetScaleFactor));

                                int scaledWidth = spriteSheetWidth * spritesheetScaleFactor;
                                int scaledHeight = spriteSheetHeight * spritesheetScaleFactor;

                                spritesheet_pos_x = (SPRITESHEET_AREA_WIDTH / 2) - (scaledWidth / 2);
                                spritesheet_pos_y = (SPRITESHEET_AREA_HEIGHT / 2) - (scaledHeight / 2);

                                spritesheet.setPosition(spritesheet_pos_x, spritesheet_pos_y);
                                spritesheetBorder.setPosition(spritesheet_pos_x, spritesheet_pos_y);
                            }
                        }
                        else if(spritesheetZoomInButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            spritesheetScaleFactor = spritesheetScaleFactor + 0.1;
                            spritesheet.setScale(spritesheetScaleFactor, spritesheetScaleFactor);
                            spritesheetBorder.setScale(spritesheetScaleFactor, spritesheetScaleFactor);
                            spritesheetScaleDisplayString.setString("SPRITESHEET SCALE:" + std::to_string(spritesheetScaleFactor));

                            int scaledWidth = spriteSheetWidth * spritesheetScaleFactor;
                            int scaledHeight = spriteSheetHeight * spritesheetScaleFactor;

                            spritesheet_pos_x = (SPRITESHEET_AREA_WIDTH / 2) - (scaledWidth / 2);
                            spritesheet_pos_y = (SPRITESHEET_AREA_HEIGHT / 2) - (scaledHeight / 2);

                            spritesheet.setPosition(spritesheet_pos_x, spritesheet_pos_y);
                            spritesheetBorder.setPosition(spritesheet_pos_x, spritesheet_pos_y);
                        }
                        else if(frameZoomInButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            frameScaleFactor = frameScaleFactor + 0.1;
                            frameSprite.setScale(frameScaleFactor, frameScaleFactor);
                            frameBorder.setScale(frameScaleFactor, frameScaleFactor);
                            frameScaleDisplayString.setString("FRAME SCALE:" + std::to_string(frameScaleFactor));
                        }
                        else if(frameZoomOutButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            if(frameScaleFactor > 0.5)
                            {
                                frameScaleFactor = frameScaleFactor - 0.1;
                                frameSprite.setScale(frameScaleFactor, frameScaleFactor);
                                frameBorder.setScale(frameScaleFactor, frameScaleFactor);
                                frameScaleDisplayString.setString("FRAME SCALE:" + std::to_string(frameScaleFactor));
                            }
                        }
                        else if(increaseFpsButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            float fps = 1.0f / frameDuration;
                            frameDuration = 1.0f / (fps + 1);
                            fpsDisplayString.setString("FPS:" + std::to_string((int)std::round(1.0f / frameDuration)));
                        }
                        else if(decreaseFpsButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            if(1.0f / frameDuration > 1)
                            {
                                float fps = 1.0f / frameDuration;
                                frameDuration = 1.0f / (fps - 1);
                                fpsDisplayString.setString("FPS:" + std::to_string((int)std::round(1.0f / frameDuration)));
                            }
                        }
                        else if(playButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            animationPlaying = true;
                        }
                        else if(pauseButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            animationPlaying = false;
                        }
                    }
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Space:
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
                sf::Vertex(sf::Vector2f(spritesheet_pos_x + col * (cellWidth * spritesheetScaleFactor), spritesheet_pos_y), lineColor),
                sf::Vertex(sf::Vector2f(spritesheet_pos_x + col * (cellWidth * spritesheetScaleFactor), spritesheet_pos_y + (spriteSheetHeight * spritesheetScaleFactor)), lineColor)
            };

            window.draw(line, 2, sf::Lines);
        }

        // Draw row splits
        for (int row = 1; row < numRows; row++)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(spritesheet_pos_x, spritesheet_pos_y + row * (cellHeight * spritesheetScaleFactor)), lineColor),
                sf::Vertex(sf::Vector2f(spritesheet_pos_x + (spriteSheetWidth * spritesheetScaleFactor), spritesheet_pos_y + row * (cellHeight * spritesheetScaleFactor)), lineColor)
            };

            window.draw(line, 2, sf::Lines);
        }

        if (animationPlaying && clock.getElapsedTime().asSeconds() > frameDuration) {
            currFrameX++;
            if (currFrameX >= numCols) {
                currFrameX = 0;
                currFrameY++;
                if (currFrameY >= numRows) {
                    currFrameY = 0;
                }
            }

            // Set the new texture rectangle for the current frame
            frameSprite.setTextureRect(sf::IntRect(currFrameX * cellWidth, currFrameY * cellHeight, cellWidth, cellHeight));

            clock.restart();
        }

        // GUI
        window.draw(configBackground);
        window.draw(increaseRowsButton);
        window.draw(decreaseRowsButton);
        window.draw(increaseColsButton);
        window.draw(decreaseColsButton);
        window.draw(increaseFpsButton);
        window.draw(decreaseFpsButton);
        window.draw(spritesheetZoomOutButton);
        window.draw(spritesheetZoomInButton);
        window.draw(playButton);
        window.draw(pauseButton);
        window.draw(frameZoomOutButton);
        window.draw(frameZoomInButton);
        window.draw(minus);
        window.draw(plusHorizontal);
        window.draw(plusVertical);
        window.draw(frameMinus);
        window.draw(framePlusHorizontal);
        window.draw(framePlusVertical);
        window.draw(rowsDisplayString);
        window.draw(colsDisplayString);
        window.draw(spritesheetScaleDisplayString);
        window.draw(frameScaleDisplayString);
        window.draw(frameSizeDisplayString);
        window.draw(fpsDisplayString);

        window.display();
    }
    
    return EXIT_SUCCESS;
}