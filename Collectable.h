#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/Graphics.hpp>

class Collectable
{
public:
    Collectable();
    ~Collectable();

    void Render(sf::RenderWindow& window);
    bool GetAlive();
    void SetAlive();
    int GetGrowAmount();
    sf::Vector2f GetPosition();
    void Spawn();



protected:

private:
    sf::Vector2f m_Position{60,200};
    bool m_isAlive{0};
    int m_GrowAmount{1};
    const float m_Size{10.0f};

    sf::CircleShape m_collectable{m_Size};

};

#endif // COLLECTABLE_H
