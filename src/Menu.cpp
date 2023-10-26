#include "Menu.hpp"
#include "Game.hpp"

#include <iostream>

Menu::Menu()
{

}

bool Menu::startMenu()
{
    bool runStartMenu = true;
    while(runStartMenu)
    {
        std::cout << "ConnectFour\n\n Please select an option from the menu:\n";
        std::cout << "1) One Player\n" << "2) Two Player\n" << "X) Exit\n";

        char menuSelection = 0;
        menuSelection = '2';
        // std::cin >> menuSelection;

        switch(menuSelection)
        {
            case '1':
                m_gameTypeSelection = Game::OnePlayer;
                opponentMenu();
                return true;

            case '2':
                m_gameTypeSelection = Game::TwoPlayer;
                return true;

            case 'X':
                runStartMenu = false;
                break;
            default:
                break;
        }
    }
    
    return false;
}

bool Menu::opponentMenu()
{
    bool runOpponentMenu = true;
    while(runOpponentMenu)
    {
        std::cout << "Please select an opponent type:\n";
        std::cout << "1) Reflex\n" << "2) MiniMax\n" << "3) ExpMax\n" << "B) Back\n";
        
        char oppSelection = 0;
        std::cin >> oppSelection;
        
        switch(oppSelection)
        {
            case '1':
                m_opponentTypeSelection = Game::Reflex;
                return true;  


            case '2':
                m_opponentTypeSelection = Game::MiniMax;
                return true;

            case '3':
                m_opponentTypeSelection = Game::ExpMax;
                return Game::ExpMax;

            case 'B':
                return false;

            default:
                std::cout << "Invalid Selection!\n";
                break;

        }
    }
    return false;
}

Game::GameType Menu::getGameTypeSelection()
{
    return m_gameTypeSelection;
}

Game::OpponentType Menu::getOpponentTypeSelection()
{
    return m_opponentTypeSelection;
}