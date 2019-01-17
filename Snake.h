#ifndef SNAKE_H
#define SNAKE_H

#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "Collectable.h"
#include <iostream>


//an enum class to deal with directions
enum class EDirection
{
    eNorth,
    eEast,
    eSouth,
    eWest
};

class Snake
{
public:
    Snake(std::string name);
    virtual ~Snake();
    void Move(std::vector<Collectable>& collect, std::vector<Snake>& snake, sf::Vector2f sunPosition, sf::Vector2f planetPosition);
    void Render(sf::RenderWindow& window);
    void ChangeDirection(EDirection newDirection);
    void setGrowAmount();
    void CollectCollectable(std::vector<Collectable>& collect);
    bool SnakeCollision(const Snake& other) const;
    bool SnakeSelfCollision() const;
    bool SunCollision(sf::Vector2f sunPosition);
    bool PlanetCollision(sf::Vector2f planetPosition);
    bool GetisAlive();
    void SetisAlive();
    EDirection GetDirection();
    void DisplayScore(sf::RenderWindow& window);
    int GetScore();
    sf::Vector2f FindCollectables(std::vector<Collectable>& collect);
    void moveToGoal(sf::Vector2f goal);
    std::string GetName();



protected:

private:
    std::string m_name;
    sf::Vector2f m_Position{300,200};
    const float m_movementStep{10.0f};
    std::list<sf::Vector2f> m_snakeSegments;
    int m_growAmount{0};
    int m_score{0};
    bool m_isAlive{false};
    sf::Font font;
    sf::Text snakesScore;
    EDirection m_direction{EDirection::eEast};
    sf::CircleShape m_segment{m_movementStep};
    bool hasGoal{false};
};

#endif // SNAKE_H
