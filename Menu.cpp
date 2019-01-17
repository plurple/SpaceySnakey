#include "Menu.h"

Menu::Menu(float width, float height)
{
    if(!font.loadFromFile("RobotoCondensed-Light.ttf"))//load the font and check for errors in loading
    {
        return;
    }

    menu[0].setFont(font);                                  //{
    menu[0].setColor(sf::Color::White);                     //
    menu[0].setCharacterSize(50);                           //set the various details for the text same for the 3 below
    menu[0].setString("MAIN MENU");                         //
    menu[0].setPosition(sf::Vector2f(width / 2 - 130, 20)); //}

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::Magenta);
    menu[1].setString("Play");
    menu[1].setPosition(sf::Vector2f(width / 2 - 20, height / (4) * 1));

    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setString("Options");
    menu[2].setPosition(sf::Vector2f(width / 2 - 40, height / (4) * 2));

    menu[3].setFont(font);
    menu[3].setColor(sf::Color::White);
    menu[3].setString("Exit");
    menu[3].setPosition(sf::Vector2f(width / 2 - 20, height / (4) * 3));


}

Menu::~Menu()
{
    //dtor
}

void Menu::draw(sf::RenderWindow &window)
{
    //loop through the 4 text items so they are drawn to screen
    for (int i = 0; i < 4; i++)
    {
        window.draw(menu[i]);
    }
}

//used to select the menu item below the currently selected
void Menu::moveDown()
{
    if (selectedItem == 1 || selectedItem == 2)
    {
        menu[selectedItem].setColor(sf::Color::White);
        selectedItem++;
        menu[selectedItem].setColor(sf::Color::Magenta);
    }
}

//used to select the menu item above the currently selected
void Menu::moveUp()
{
    if (selectedItem == 2 || selectedItem == 3)
    {
        menu[selectedItem].setColor(sf::Color::White);
        selectedItem--;
        menu[selectedItem].setColor(sf::Color::Magenta);
    }

}
