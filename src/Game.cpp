#include "Game.hpp"
#include "Player.hpp"
#include "UserPlayer.hpp"
#include <iostream>

Game::Game()
{
    m_board = new Board();
    m_playerOne = NULL;
    m_playerTwo = NULL;
    m_currentPlayer = NULL;
    m_score = 0;
    m_winner = NULL;
}

Game::~Game()
{
    delete m_board;
    delete m_playerOne;
    delete m_playerTwo;
}

bool Game::AddUserPlayer(std::string& playerName)
{   
    if(m_playerOne == NULL)
    {
        m_playerOne = new UserPlayer(Piece::Red, playerName);
        return true;
    }
    else if(m_playerTwo == NULL)
    {
        m_playerTwo = new UserPlayer(Piece::Blue, playerName);
        return true;
    }
    else
    {
        return false;
    }
    

}

bool Game::AddComputerPlayer(Game::OpponentType opponentType)
{
    return true;
}

bool Game::opponentMenu()
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
                m_opponentType = OpponentType::Reflex;  
                return true;

            case '2':
                m_opponentType = OpponentType::MiniMax;
                return true;

            case '3':
                m_opponentType = OpponentType::ExpMax;
                return true;

            case 'B':
                return false;

            default:
                std::cout << "Invalid Selection!\n";
                break;

        }
    }
    return false;
}

bool Game::startMenu()
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
                m_gameType = GameType::OnePlayer;
                opponentMenu();
                return true;

            case '2':
                m_gameType = GameType::TwoPlayer;
                return true;

            case 'X':
                runStartMenu = false;
                break;
            default:
                break;
        }
    }
    
    return true;
}
void Game::startGame()
{
    // TODO
}

void Game::changeTurn()
{
    // if the current player is player one, then set currwent player to player two
    if(m_currentPlayer->getPlayerName() == m_playerOne->getPlayerName())
    {
        m_currentPlayer = m_playerTwo;
    }
    // if the current player wasnt player one then it is player two - so switch to player one.
    else
    {
        m_currentPlayer = m_playerOne;
    }
}

Game::GameType Game::getGameType()
{
    return m_gameType;
}

Game::OpponentType Game::getOpponentType()
{
    return m_opponentType;
}

bool Game::initTurnSwitcher()
{
    if(m_playerOne == NULL || m_playerTwo == NULL)
    {
        return false;
    }

    m_currentPlayer = m_playerOne;
    return true;
}

Board* Game::getBoard()
{
    return m_board;
}


void Game::endGame()
{
    
}


Player* Game::getCurrentPlayer()
{
    return m_currentPlayer;
}