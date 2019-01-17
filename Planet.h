#ifndef PLANET_H
#define PLANET_H
#include <SFML/Graphics.hpp>


class Planet
{
public:
    Planet();
    ~Planet();
    void Render(sf::RenderWindow& window);
    void RotatePlanet(sf::Vector2f sunPosition);
    sf::Vector2f GetPlanetPosition();

protected:

private:
    sf::Vector2f m_PlannetPosition;
    sf::CircleShape m_Plannet{20.0f};
};

#endif // PLANET_H
