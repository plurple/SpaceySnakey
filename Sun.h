#ifndef SUN_H
#define SUN_H
#include <SFML/Graphics.hpp>

class Sun
{
public:
    Sun();
    ~Sun();
    void Render(sf::RenderWindow& window);
    sf::Vector2f GetSunPosition();

protected:

private:
    sf::Vector2f m_SunPosition;
    sf::CircleShape m_Sun{50.0f};
};

#endif // SUN_H
