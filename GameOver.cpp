#include "GameOver.h"

GameOver::GameOver(float width, float height, std::string str)
{
    //ctor
    if(!font.loadFromFile("RobotoCondensed-Light.ttf"))
    {
        return;
    }

    text[0].setFont(font);
    text[0].setColor(sf::Color::White);
    text[0].setCharacterSize(50);
    text[0].setString("GAME OVER");
    text[0].setPosition(sf::Vector2f(width / 2 - 130, 20));

    text[1].setFont(font);
    text[1].setColor(sf::Color::White);
    text[1].setString(str);
    text[1].setPosition(sf::Vector2f(width / 2 - 90, 150));

    text[2].setFont(font);
    text[2].setColor(sf::Color::White);
    text[2].setString("Press Enter to Return to Main Menu");
    text[2].setPosition(sf::Vector2f(width / 2 - 200, 500));

}

GameOver::~GameOver()
{
    //dtor
}

void GameOver::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < 3; i++)
    {
        window.draw(text[i]);
    }
}


