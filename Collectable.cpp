#include "Collectable.h"
#include <iostream>

Collectable::Collectable()
{
    //ctor
    m_collectable.setOrigin(m_collectable.getRadius(), m_collectable.getRadius());
}

Collectable::~Collectable()
{
    //dtor
}



bool Collectable::GetAlive()
{

    return m_isAlive;

}

void Collectable::SetAlive()
{

    m_isAlive = !m_isAlive;

}

int Collectable::GetGrowAmount()
{
    return m_GrowAmount;
}


sf::Vector2f Collectable::GetPosition()
{

    return m_Position;

}


void Collectable::Spawn()
{
    m_Position.x=((rand()%760+20)/20)*20;
    m_Position.y=((rand()%560+20)/20)*20;
    bool validPosition = false;
    do
    {
        float distanceToSun = ((m_Position.x - 400) * (m_Position.x - 400) + (m_Position.y - 300) * (m_Position.y - 300));
        if (distanceToSun <= ((10+50)*(10+50)+40*40))
        {

            m_Position.x=((rand()%760+20)/20)*20;
            m_Position.y=((rand()%560+20)/20)*20;
        }
        else
            validPosition = true;


    }
    while(validPosition == false);



    m_collectable.setPosition(m_Position);
    m_GrowAmount=rand()%5+1;
    switch(m_GrowAmount)
    {
    case 1:
        m_collectable.setFillColor(sf::Color::Magenta);
        break;
    case 2:
        m_collectable.setFillColor(sf::Color::Yellow);
        break;
    case 3:
        m_collectable.setFillColor(sf::Color::Cyan);
        break;
    case 4:
        m_collectable.setFillColor(sf::Color::Blue);
        break;
    case 5:
        m_collectable.setFillColor(sf::Color::Red);
        break;
    }
    m_isAlive=true;
}

void Collectable::Render(sf::RenderWindow& window)
{


    // draw our circle shape to the window
    if (m_isAlive)
        window.draw(m_collectable);

}
