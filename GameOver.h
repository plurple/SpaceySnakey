#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <SFML/Graphics.hpp>

class GameOver
{
    public:
        GameOver(float width, float height, std::string str);
        ~GameOver();
        void draw(sf::RenderWindow &window);

    protected:

    private:
        sf::Font font;
        sf::Text text[3];
};

#endif // GAMEOVER_H
