#include "Options.h"

Options::Options(float width, float height)
{
    //ctor
    if(!font.loadFromFile("RobotoCondensed-Light.ttf"))
    {
        return;
    }

    options[0].setFont(font);
    options[0].setColor(sf::Color::White);
    options[0].setCharacterSize(50);
    options[0].setString("OPTIONS");
    options[0].setPosition(sf::Vector2f(width / 2 - 130, 20));

    options[1].setFont(font);
    options[1].setColor(sf::Color::Magenta);
    options[1].setString("1 Player");
    options[1].setPosition(sf::Vector2f(width / 2 - 150, 150));

    options[2].setFont(font);
    options[2].setColor(sf::Color::White);
    options[2].setString("2 Player");
    options[2].setPosition(sf::Vector2f(width / 2 + 150, 150));

    options[3].setFont(font);
    options[3].setColor(sf::Color::White);
    options[3].setString("Press Enter to Return to Main Menu");
    options[3].setPosition(sf::Vector2f(width / 2 - 200, 500));

}

Options::~Options()
{
    //dtor
}

int Options::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < 4; i++)
    {
        window.draw(options[i]);
    }
    if(selectedItem == 2)
    return 2;
    else
    return 1;
}

void Options::moveRight()
{
    if (selectedItem == 1)
    {
        options[1].setColor(sf::Color::White);
        selectedItem++;
        options[2].setColor(sf::Color::Magenta);
    }
}

void Options::moveLeft()
{
    if (selectedItem == 2)
    {
        options[2].setColor(sf::Color::White);
        selectedItem--;
        options[1].setColor(sf::Color::Magenta);
    }

}
