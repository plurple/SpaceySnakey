#include "GameState.h"

GameState::GameState()
{
    //ctor
}

GameState::~GameState()
{
    //dtor
}

GameStates GameState::getState()
{
    return gameState;
}

void GameState::setState(GameStates newState)
{
    gameState = newState;
}
