
#include "Menu.h"
#include "Game.h"
#include "GameOver.h"
#include "Options.h"
#include "GameState.h"

//unfortunatly couldn't think of another way to save these variables between classes and the main function.
std::string stringHack; // save who won the last game
int players = 1; //save number of players


int main()
{
    sf::RenderWindow m_window(sf::VideoMode(800, 600), "C++ Snake ICA : T7094911"); // create the game window

    GameState gameState; // create the gamestatee class
    gameState.setState(GameStates::STATE_MENU); // set the state to the main menu
    Menu menu(m_window.getSize().x, m_window.getSize().y); //create the main menu class
    Options options(m_window.getSize().x, m_window.getSize().y); //create the options class


    //check that the window remains open
    while (m_window.isOpen())
    {
        sf::Event event; //allows the use of the sfml event system


        while (m_window.pollEvent(event))
            {
            //switch statement for different type of events
            switch(event.type)
            {
            //when the window is closed
            case sf::Event::Closed:
                m_window.close();
                break;
                //when a Key is pressed
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                //when the Up arrow is pressed
                case sf::Keyboard::Up:
                    menu.moveUp();//call the moveup function from menu class
                    break;
                case sf::Keyboard::Down: //when the down arrow is pressed
                    menu.moveDown(); //call the movedown function from menu class
                    break;
                case sf::Keyboard::Left://when the left arrow is pressed
                    options.moveLeft(); // call the moveleft function from the options class
                    break;
                case sf::Keyboard::Right://when the right arrow is pressed
                    options.moveRight();// call the moveright function from the options class
                    break;
                case sf::Keyboard::Return://when the return key is pressed
                    if(gameState.getState() == GameStates::STATE_MENU)// if the current game state is menu
                    {
                        switch (menu.getSelectedItem()) //switch statement to decide which menu item is selected
                        {
                        case 1:
                            gameState.setState(GameStates::STATE_PLAY);//when selecting the 1st item change the gamestate to play
                            break;
                        case 2:
                            gameState.setState(GameStates::STATE_OPTIONS);//when selecting the 2nd item change the gamestate to options
                            break;
                        case 3:
                            m_window.close();//when selecting the 3rd item close the window
                            break;
                        }
                    }
                    else if (gameState.getState() == GameStates::STATE_GAMEOVER) //when return key is pressed and in the game over screen
                        gameState.setState(GameStates::STATE_MENU); // set the gamestate to menu
                    else if (gameState.getState() == GameStates::STATE_OPTIONS)//when return key is pressed and in the options screen
                        gameState.setState(GameStates::STATE_MENU);// set the gamestate to menu
                    break;
                default:
                    break;
                }
            default:
                break;

            }
        }
        if(gameState.getState() == GameStates::STATE_PLAY)//when gamestate is play
        {
            Game snakeGame(m_window.getSize().x, m_window.getSize().y, players);//create an instance of a game
            stringHack = snakeGame.Run(m_window, gameState); //set the winner of the last game once returned from the games run function
        }


        m_window.clear();//clear the window of everything

        if (gameState.getState() == GameStates::STATE_MENU)//when gamestate is menu
            menu.draw(m_window);//draw the menu screen to the window
        if (gameState.getState() == GameStates::STATE_OPTIONS)//when gamestate is options
        {

            players = options.draw(m_window);//draw the options screen to the window
        }
        if (gameState.getState() == GameStates::STATE_GAMEOVER)//when the gamestate is gameover
        {
            GameOver gameOver(m_window.getSize().x, m_window.getSize().y, stringHack);//create an instance of the gamover class
            gameOver.draw(m_window);//draw the gameover screen to the window
        }

        m_window.display();//display the window now that everything is drawn
    }

    return 0;
}
