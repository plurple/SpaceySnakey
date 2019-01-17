#include "Snake.h"
#include <iostream>
#include <sstream>

Snake::Snake(std::string name) : m_name(name)
{
    //ctor
    m_isAlive = true;
    m_segment.setOrigin(m_segment.getRadius(), m_segment.getRadius());
    m_segment.setFillColor(sf::Color::Green);
    if(m_name != "Player1")
    m_segment.setFillColor(sf::Color::White);

    m_Position.x=rand()%((400+400)/20)*20;//randomise the snakes starting position
    m_Position.y=rand()%((300+300)/20)*20;
    m_snakeSegments.push_front(m_Position);//put the head on the linked list
    font.loadFromFile("RobotoCondensed-Light.ttf");//load the font

}

Snake::~Snake()
{
    //dtor
}

template <typename T> std::string ToString(const T& val)
{
  std::ostringstream strm;
  strm << val;
  return strm.str();
}

void Snake::Move(std::vector<Collectable>& collect, std::vector<Snake>& snake, sf::Vector2f sunPosition, sf::Vector2f planetPosition)
{

    switch(m_direction)
    {
    case EDirection::eNorth:
        m_Position.y-=2*m_movementStep;
        m_snakeSegments.push_front(m_Position);
        if(m_growAmount>0)
            m_growAmount--;
        else
            m_snakeSegments.pop_back();
        break;
    case EDirection::eEast:
        m_Position.x+=2*m_movementStep;
        m_snakeSegments.push_front(m_Position);
        if(m_growAmount>0)
            m_growAmount--;
        else
            m_snakeSegments.pop_back();
        break;
    case EDirection::eSouth:
        m_Position.y+=2*m_movementStep;
        m_snakeSegments.push_front(m_Position);
        if(m_growAmount>0)
            m_growAmount--;
        else
            m_snakeSegments.pop_back();
        break;
    case EDirection::eWest:
        m_Position.x-=2*m_movementStep;
        m_snakeSegments.push_front(m_Position);
        if(m_growAmount>0)
            m_growAmount--;
        else
            m_snakeSegments.pop_back();
        break;
    }
    //snake Artificial intelligence
    if(m_name == "AI")
    {
        sf::Vector2f goal = FindCollectables(collect);//find the closest collectable
        if (hasGoal)
        {
            moveToGoal(goal);//move towards the goal
        }
        //if no goal random movement
        else
        {
            int randomDirection = rand()%4;
            switch(randomDirection)
            {
            case 0:
                if(m_direction != EDirection::eSouth)
                ChangeDirection(EDirection::eNorth);
                break;
            case 1:
                if(m_direction != EDirection::eWest)
                ChangeDirection(EDirection::eEast);
                break;
            case 2:
                if(m_direction != EDirection::eNorth)
                ChangeDirection(EDirection::eSouth);
                break;
            case 3:
                if(m_direction != EDirection::eEast)
                ChangeDirection(EDirection::eWest);
                break;
            default:
                break;
            }
        }

        if(m_Position.x - (m_movementStep * 1) < m_movementStep)
        {
            ChangeDirection(EDirection::eSouth);
            m_Position.y+=2*m_movementStep;
            m_snakeSegments.push_front(m_Position);
        m_snakeSegments.pop_back();
            ChangeDirection(EDirection::eEast);
        }
        if(m_Position.x + (m_movementStep * 1) > 780)
        {
            ChangeDirection(EDirection::eNorth);
            m_Position.y-=2*m_movementStep;
            m_snakeSegments.push_front(m_Position);
        m_snakeSegments.pop_back();
            ChangeDirection(EDirection::eWest);
        }
        if(m_Position.y - (m_movementStep * 1) < m_movementStep)
        {
            ChangeDirection(EDirection::eWest);
            m_Position.x-=2*m_movementStep;
            m_snakeSegments.push_front(m_Position);
        m_snakeSegments.pop_back();
            ChangeDirection(EDirection::eSouth);
        }
        if(m_Position.y + (m_movementStep * 1) > 580)
        {
            ChangeDirection(EDirection::eEast);
            m_Position.x+=2*m_movementStep;
            m_snakeSegments.push_front(m_Position);
        m_snakeSegments.pop_back();
            ChangeDirection(EDirection::eNorth);
        }

        float distanceToSun = ((m_Position.x - sunPosition.x) * (m_Position.x - sunPosition.x) + (m_Position.y - sunPosition.y) * (m_Position.y - sunPosition.y));
        float TouchingSun = ((10 + 50) * (10 + 50));

        if (distanceToSun <= (TouchingSun + 40*40))
        {

            if(m_direction == EDirection::eEast && m_Position.y >=300)
            {
                ChangeDirection(EDirection::eSouth);
            }
            if(m_direction == EDirection::eEast && m_Position.y <300)
            {
                ChangeDirection(EDirection::eNorth);
            }
            if(m_direction == EDirection::eWest && m_Position.y >=300)
            {
                ChangeDirection(EDirection::eSouth);
            }
            if(m_direction == EDirection::eWest && m_Position.y <300)
            {
                ChangeDirection(EDirection::eNorth);
            }
            if(m_direction == EDirection::eNorth && m_Position.x >=400)
            {
                ChangeDirection(EDirection::eEast);
            }
            if(m_direction == EDirection::eNorth && m_Position.x <400)
            {
                ChangeDirection(EDirection::eWest);
            }
            if(m_direction == EDirection::eSouth && m_Position.x >=400)
            {
                ChangeDirection(EDirection::eEast);
            }
            if(m_direction == EDirection::eSouth && m_Position.x <400)
            {
                ChangeDirection(EDirection::eWest);
            }
        }



    }

    m_segment.setPosition(m_Position);

    if (m_Position.x>800-m_movementStep)
        ChangeDirection(EDirection::eWest);
    if (m_Position.x<0)
        ChangeDirection(EDirection::eEast);
    if (m_Position.y>600-m_movementStep)
        ChangeDirection(EDirection::eNorth);
    if (m_Position.y<0)
        ChangeDirection(EDirection::eSouth);
}



sf::Vector2f Snake::FindCollectables(std::vector<Collectable>& collect)
{
    float ShortestDistance{100000000.0f}; //some large number so first collectable that spawns gets assigned
    sf::Vector2f goal;
    for(auto& c : collect)
    {
        if (c.GetAlive())
        {
            float length = ((m_Position.x - c.GetPosition().x) * (m_Position.x - c.GetPosition().x) + (m_Position.y - c.GetPosition().y) * (m_Position.y - c.GetPosition().y));
            if (length < ShortestDistance)
            {
                ShortestDistance = length;
                hasGoal = true;
                goal = c.GetPosition();
            }
        }

    }
    return goal;
}

void Snake::moveToGoal(sf::Vector2f goal)
{
    sf::Vector2f direction = m_Position - goal;
    if(((direction.x > direction.y && direction.x > 0) || (direction.y == 0 && direction.x >0)) && (m_direction != EDirection::eEast))
        ChangeDirection(EDirection::eWest);
    else if (((direction.x > direction.y && direction.x < 0) || (direction.y == 0 && direction.x <0)) && (m_direction != EDirection::eWest))
        ChangeDirection(EDirection::eEast);
    else if (((direction.x < direction.y && direction.y > 0) || (direction.x == 0 && direction.y >0)) && (m_direction != EDirection::eSouth))
        ChangeDirection(EDirection::eNorth);
    else if (((direction.x < direction.y && direction.y < 0) || (direction.x == 0 && direction.y <0)) && (m_direction != EDirection::eNorth))
        ChangeDirection(EDirection::eSouth);


}

std::string Snake::GetName()
{
    return m_name;
}


void Snake::ChangeDirection(EDirection newDirection)
{
    m_direction=newDirection;

}

void Snake::Render(sf::RenderWindow& window)
{

    // draw our circle shape to the window
    for(auto& s: m_snakeSegments)
    {
        m_segment.setPosition(s);
        window.draw(m_segment);
    }

}



void Snake::DisplayScore(sf::RenderWindow& window)
{


    snakesScore.setFont(font);
    if(m_name == "Player1")
    {

        snakesScore.setColor(sf::Color::White);
        snakesScore.setString(m_name + ": " + ToString(m_score));
        snakesScore.setPosition(sf::Vector2f(150, 20));
    }
    else if(m_name == "Player2")
    {

        snakesScore.setColor(sf::Color::White);
        snakesScore.setString(m_name + ": " + ToString(m_score));
        snakesScore.setPosition(sf::Vector2f(550, 20));
    }
    else if(m_name == "AI")
    {

        snakesScore.setColor(sf::Color::White);
        snakesScore.setString(m_name + ": " + ToString(m_score));
        snakesScore.setPosition(sf::Vector2f(550, 20));
    }

    window.draw(snakesScore);

}



void Snake::setGrowAmount()
{
    m_growAmount++;
}

//colectable collision handling
void Snake::CollectCollectable(std::vector<Collectable>& collect)
{
    for(auto &c: collect)
    {
        if (c.GetAlive())
            if(m_Position == c.GetPosition())
            {

                c.SetAlive();
                m_growAmount += c.GetGrowAmount();
                m_score += c.GetGrowAmount();
            }
    }
}

int Snake::GetScore()
{
    return m_score;
}

bool Snake::SnakeCollision(const Snake& other) const
{

    for (auto& otherSegment : other.m_snakeSegments)
    {
        if (m_snakeSegments.front() == otherSegment)
            return true;
    }

    return false;
}

bool Snake::SnakeSelfCollision() const
{
    auto tail = m_snakeSegments.begin();
    std::advance(tail, 1);

    while(tail != m_snakeSegments.end())
    {
        if(m_snakeSegments.front() == *tail)
            return true;

        tail++;
    }

    return false;
}

bool Snake::SunCollision(sf::Vector2f sunPosition)
{
    float length = ((m_Position.x - sunPosition.x) * (m_Position.x - sunPosition.x) + (m_Position.y - sunPosition.y) * (m_Position.y - sunPosition.y));
    float distance = ((10 + 50) * (10 + 50));
    if (length <= distance)
        return true;

    return false;
}

bool Snake::PlanetCollision(sf::Vector2f planetPosition)
{
    int i = 0;
    for(auto& segment : m_snakeSegments)
    {
        float length = ((segment.x - planetPosition.x) * (segment.x - planetPosition.x) + (segment.y - planetPosition.y) * (segment.y - planetPosition.y));
        float distance = ((10 + 20) * (10 + 20));
        if (length <= distance)
        {
            m_snakeSegments.resize(i);
            if(m_snakeSegments.size() == 0)
                return true;
            else
                return false;
        }
        i++;
    }

    return false;
}

bool Snake::GetisAlive()
{
    return m_isAlive;
}

void Snake::SetisAlive()
{
    m_isAlive = !m_isAlive;
}

EDirection Snake::GetDirection()
{
    return m_direction;
}


