#ifndef MENU_HPP
#define MENU_HPP

#include "Game.hpp"

class Menu
{   
    public:
        Menu();

        bool startMenu();
        Game::GameType getGameTypeSelection();
        Game::OpponentType getOpponentTypeSelection();

    private:
        Game::GameType m_gameTypeSelection;
        Game::OpponentType m_opponentTypeSelection;
        bool opponentMenu();
        


};

#endif
