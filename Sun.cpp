#include "Sun.h"

Sun::Sun()
{
    //ctor
    m_Sun.setOrigin(m_Sun.getRadius(), m_Sun.getRadius());
    m_Sun.setFillColor(sf::Color::Yellow);
    m_SunPosition.x=400;
    m_SunPosition.y=300;
    m_Sun.setPosition(m_SunPosition);
}

Sun::~Sun()
{
    //dtor
}

void Sun::Render(sf::RenderWindow& window)
{
    window.draw(m_Sun);
}

sf::Vector2f Sun::GetSunPosition()
{
    return m_SunPosition;
}
