#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Snake.h"
#include "Collectable.h"
#include "Sun.h"
#include "Planet.h"
#include "GameState.h"


class Game
{
    public:
        Game(float width, float height, int players);//constructor
        ~Game();//deconstructor
        void GameOver(GameState& gameState);//determines win condition

        std::string Run(sf::RenderWindow &window, GameState & gameState);//used to play the game
        void displayTimer(sf::RenderWindow& window);//displays the time left on screen
        std::string Winner(std::vector<Snake>& m_snakes);//string of who won


    protected:

    private:

        int m_screenWidth{800};
        int m_screenHeight{600};

        std::vector<Snake> m_snakes;//vector of snakes
        std::vector<Collectable> m_collectables;//vector of collectables
        int noSnakes{0};//number of snakes in game
        sf::Font myFont;//create a font
        sf::Text Timer;//creates a text for the timer
        sf::Clock timer;//creates a clock to act as timer
        std::string winner;//to store the winner text
        int timeLeft;//used to store the time remaining



};

#endif // GAME_H
