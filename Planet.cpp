#include "Planet.h"

Planet::Planet()
{
    //ctor
    m_Plannet.setOrigin(m_Plannet.getRadius(), m_Plannet.getRadius());
    m_Plannet.setFillColor(sf::Color::Blue);
    m_PlannetPosition.x=250;
    m_PlannetPosition.y=200;


}

Planet::~Planet()
{
    //dtor
}

void Planet::Render(sf::RenderWindow& window)
{

    m_Plannet.setPosition(m_PlannetPosition);
    window.draw(m_Plannet);
}

void Planet::RotatePlanet(sf::Vector2f sunPosition)
{
    constexpr float m_angle = 0.2f;
    sf::Vector2f zeroPos = m_PlannetPosition - sunPosition;

    m_PlannetPosition.x = zeroPos.x * cos(m_angle) + zeroPos.y * sin(m_angle);
    m_PlannetPosition.y = zeroPos.y * cos(m_angle) - zeroPos.x * sin(m_angle);
    m_PlannetPosition += sunPosition;
}

sf::Vector2f Planet::GetPlanetPosition()
{
    return m_PlannetPosition;
}

