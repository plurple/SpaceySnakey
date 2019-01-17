#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>



class Menu
{
public:
    Menu(float width, float height);//constructor
    ~Menu();//deconstructor
    void draw(sf::RenderWindow &window);//function to draw to the screen
    void moveUp();
    void moveDown();
    int getSelectedItem() {return selectedItem;}//return selectedItem when called

protected:

private:
    sf::Font font;//create a font
    sf::Text menu[4]; //create an array of size 4 of texts
    int selectedItem = 1;//create an int to track wich item is being selected on the menu
};

#endif // MENU_H
