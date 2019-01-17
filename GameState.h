#ifndef GAMESTATE_H
#define GAMESTATE_H

enum class GameStates
{
    STATE_WAITING,
    STATE_MENU,
    STATE_OPTIONS,
    STATE_PLAY,
    STATE_GAMEOVER
};


class GameState
{
    public:
        GameState();
        ~GameState();
        GameStates getState();
        void setState(GameStates newState);


    protected:

    private:
        GameStates gameState = GameStates::STATE_WAITING;
};

#endif // GAMESTATE_H
