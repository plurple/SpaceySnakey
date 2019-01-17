#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/Graphics.hpp>


class Collectible
{
    public:
        Collectible();
        ~Collectible();
        void Render(sf::RenderWindow& window);

    protected:

    private:
    sf::Vector2f m_Position{30,20};
    bool isAlive;
    int GrowAmount;
};

#endif // COLLECTABLE_H
