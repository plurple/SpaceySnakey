#ifndef OPTIONS_H
#define OPTIONS_H
#include <SFML/Graphics.hpp>


class Options
{
    public:
        Options(float width, float height);
        ~Options();
        void moveRight();
        void moveLeft();
        int draw(sf::RenderWindow &window);


    protected:

    private:
    sf::Font font;
    sf::Text options[4];
    int selectedItem = 1;

};

#endif // OPTIONS_H
