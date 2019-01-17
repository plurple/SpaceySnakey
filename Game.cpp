#include "Game.h"
#include <sstream>

Game::Game(float width, float height, int players)
{
    //ctor
    //sets up the 5 collectables
    for(int i=0; i<5; i++)
    {
        m_collectables.push_back(Collectable());
    }
    m_snakes.push_back(Snake("Player1"));//sets up the player 1 snake
    noSnakes++;
    if(players == 1)
    m_snakes.push_back(Snake("AI"));//when 1 player makes an AI snake
    else
    m_snakes.push_back(Snake("Player2"));//when 2 player makes a player 2 snake
    noSnakes++;
    myFont.loadFromFile("RobotoCondensed-Light.ttf");//loads the font


}

Game::~Game()
{
    //dtor
}

std::string Game::Run(sf::RenderWindow & m_window, GameState& gameState)
{
    srand(time(NULL));//seed the random number

    // We can still output to the console window


    sf::Clock clock;



    Sun sun;//create the sun
    Planet planet;//create the planet

    // Main loop that continues until we call Close()
    while (m_window.isOpen())
    {
        // Handle any pending SFML event// draw our circle shape to the window

        // These cover keyboard, mouse,joystick etc.
        //same as in main
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                case sf::Keyboard::Left:
                    if(m_snakes[0].GetDirection() != EDirection::eEast)
                        m_snakes[0].ChangeDirection(EDirection::eWest);
                    break;
                case sf::Keyboard::Right:
                    if(m_snakes[0].GetDirection() != EDirection::eWest)
                        m_snakes[0].ChangeDirection(EDirection::eEast);
                    break;
                case sf::Keyboard::Up:
                    if(m_snakes[0].GetDirection() != EDirection::eSouth)
                        m_snakes[0].ChangeDirection(EDirection::eNorth);
                    break;
                case sf::Keyboard::Down:
                    if(m_snakes[0].GetDirection() != EDirection::eNorth)
                        m_snakes[0].ChangeDirection(EDirection::eSouth);
                    break;
                    if (m_snakes[1].GetName() == "Player2")//if you have 2 players activate player 2 controls
                    {
                        case sf::Keyboard::A:
                    if(m_snakes[1].GetDirection() != EDirection::eEast)
                        m_snakes[1].ChangeDirection(EDirection::eWest);
                    break;
                case sf::Keyboard::D:
                    if(m_snakes[1].GetDirection() != EDirection::eWest)
                        m_snakes[1].ChangeDirection(EDirection::eEast);
                    break;
                case sf::Keyboard::W:
                    if(m_snakes[1].GetDirection() != EDirection::eSouth)
                        m_snakes[1].ChangeDirection(EDirection::eNorth);
                    break;
                case sf::Keyboard::S:
                    if(m_snakes[1].GetDirection() != EDirection::eNorth)
                        m_snakes[1].ChangeDirection(EDirection::eSouth);
                    break;
                    }
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        //loop through snakes to move the snakes
        for(Snake& s : m_snakes)
        {
            if(s.GetisAlive())
            {
                s.Move(m_collectables, m_snakes, sun.GetSunPosition(), planet.GetPlanetPosition());
            }
        }

        //loop through the snakes to check if colliding with any other snake
        for(size_t i = 0; i < m_snakes.size(); i++)
        {
            for(size_t j = 0; j < m_snakes.size(); j++)
            {
                if(m_snakes[i].SnakeCollision(m_snakes[j]) && i != j && m_snakes[i].GetisAlive())
                {

                    m_snakes[i].SetisAlive();
                }

            }

        }

        //loop through snakes to check if colliding with collectables
        for(Snake& s : m_snakes)
        {
            if(s.GetisAlive())
            {
                s.CollectCollectable(m_collectables);
            }
        }


        //check if the collectables are dead if so spawn one 2% of the time
        for(Collectable& c : m_collectables)
        {
            if(!c.GetAlive())
            {
                if(rand()%50==0)
                {
                    c.Spawn();
                }
            }
        }

        //loop through the snakes and check collisions against self
        for(Snake& s :m_snakes)
        {
            if(s.SnakeSelfCollision() && s.GetisAlive())
            {

                s.SetisAlive();
            }
        }

        //loop through the snakes and check collision against the sun
        for(Snake& s : m_snakes)
        {
            if(s.SunCollision(sun.GetSunPosition()) && s.GetisAlive())
            {

                s.SetisAlive();
            }
        }

        //loop through the snakes and check collision against planets
        for(Snake& s : m_snakes)
        {
            if(s.PlanetCollision(planet.GetPlanetPosition()) && s.GetisAlive())
            {

                s.SetisAlive();
            }
        }

        //loop through snakes check if any snames have died if so reduces the number of snakes and checks wincondition
        for(Snake& s : m_snakes)
        {
            if(!s.GetisAlive())
                noSnakes--;
            if(noSnakes <= 1)
            {
                GameOver(gameState);
                return winner;
            }
        }

        //checks if 90 seconds has passed if so checks winconditions
        if (timer.getElapsedTime().asSeconds() >= 90.0)
        {
            GameOver(gameState);
            return winner;
        }







        m_window.clear();


        //loop through snakes and draw them and there scores
        for(Snake& s : m_snakes)
        {
            if(s.GetisAlive())
                s.Render(m_window);
            s.DisplayScore(m_window);
        }

        //loop through the collectables and draw them to screen
        for(Collectable& c : m_collectables)
        {
            if(c.GetAlive())
            {
                c.Render(m_window);
            }
        }

        displayTimer(m_window);//draw the time left to screen






        sun.Render(m_window);//draw the sun

        planet.RotatePlanet(sun.GetSunPosition());//rotate the planet
        planet.Render(m_window);//draw the planet




        // Get the window to display its contents
        m_window.display();

        while (clock.getElapsedTime().asMilliseconds()<100);
        clock.restart();
    }


    return false;

}

void Game::GameOver(GameState & gameState)
{
    winner = Winner(m_snakes);
    gameState.setState(GameStates::STATE_GAMEOVER);//changes the gamestate to gameover screen

}

template <typename T> std::string ToString(const T& val)
{
  std::ostringstream strm;
  strm << val;
  return strm.str();
}

//function to draw timer
void Game::displayTimer(sf::RenderWindow& window)
{


    timeLeft = 90 - timer.getElapsedTime().asSeconds();

    Timer.setFont(myFont);
    Timer.setColor(sf::Color::White);
    Timer.setString(ToString(timeLeft));
    Timer.setPosition(sf::Vector2f(800 / 2 - 20, 20));

    window.draw(Timer);

}

//function to determine winner
std::string Game::Winner(std::vector<Snake>& m_snakes)
{
    if(m_snakes[0].GetisAlive() && !(m_snakes[1].GetisAlive()))
    return "Player1 wins!";
    else if(!(m_snakes[0].GetisAlive()) && m_snakes[1].GetisAlive())
    return "Player2 wins!";
    else
    {
        if(m_snakes[0].GetScore() < m_snakes[1].GetScore())
        return std::string("Player2 wins with a score of ") + ToString(m_snakes[1].GetScore());
        else if(m_snakes[0].GetScore() > m_snakes[1].GetScore())
        return std::string("Player1 wins with a score of ") + ToString(m_snakes[0].GetScore());
        else
        return "It was a draw :(";
    }

}



