#include "Game.hpp"
#include "Player.hpp"
#include "UserPlayer.hpp"
#include "ComputerPlayer.hpp"
#include <iostream>

Game::Game()
{
    m_board = new Board();
    m_playerOne = NULL;
    m_playerTwo = NULL;
    m_currentPlayer = NULL;
    m_score = 0;
    m_winner = NULL;
    m_boardFull = false;
}

Game::~Game()
{
    delete m_board;
    delete m_playerOne;
    delete m_playerTwo;
}

bool Game::AddPlayer(std::string& playerName)
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

bool Game::AddPlayer(Game::OpponentType opponentType)
{

    if(m_playerOne == NULL)
    {
        switch(opponentType)
        {
            case Game::Reflex:
                m_playerOne = new ReflexPlayer();
                return true;
            
            case Game::MiniMax:
                m_playerOne = new MiniMaxPlayer();
                return true;
            
            default:
            return false;
        }
    }
    else if(m_playerTwo == NULL)
    {
        switch(opponentType)
        {
            case Game::Reflex:
                m_playerTwo = new ReflexPlayer(Piece::Blue);
                return true;
            
            case Game::MiniMax:
                m_playerTwo = new MiniMaxPlayer(Piece::Blue);
                return true;
            
            default:
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Game::opponentMenu()
{
    bool startGame = false;
    bool runOpponentMenu = true;
    while(runOpponentMenu)
    {
        std::cout << "\nPlease select an opponent type:\n";
        std::cout << "1) Dumb\n" << "2) Smarter\n" << "B) Back\n";
        
        char oppSelection = 0;
        std::cin >> oppSelection;

        switch(std::toupper(oppSelection))
        {
            case '1':
                std::cin.ignore();
                std::cin.clear();
                m_opponentType = OpponentType::Reflex; 
                runOpponentMenu = false; 
                startGame = true;
                break;

            case '2':
                std::cin.ignore();
                std::cin.clear();
                m_opponentType = OpponentType::MiniMax;
                runOpponentMenu = false;
                startGame = true;
                break;

            case 'B':
                std::cin.ignore();
                std::cin.clear();
                runOpponentMenu = false;
                startGame = false;
                break;

            default:
                std::cin.ignore();
                std::cout.clear();
                std::cout << "Invalid Selection!\n";
                break;

        }
    }
    return startGame;
}

bool Game::startMenu()
{
    bool startGame = false;
    bool runStartMenu = true;
    while(runStartMenu)
    {
        std::cout << "ConnectFour\n\nPlease select an option from the menu:\n\n";
        std::cout << "1) One Player\n" << "2) Two Player\n" << "X) Exit\n";

        char menuSelection = 0;
        std::cin >> menuSelection;

        switch(std::toupper(menuSelection))
        {
            case '1':
                std::cin.ignore();
                std::cin.clear();
                m_gameType = GameType::OnePlayer;
                startGame = opponentMenu();
                runStartMenu = !startGame;
                break;
            case '2':
                std::cin.ignore();
                std::cin.clear();
                m_gameType = GameType::TwoPlayer;
                runStartMenu = false;
                startGame = true;
                break;
            case 'X':
                std::cin.ignore();
                std::cin.clear();
                runStartMenu = false;
                startGame = false;
                break;
            default:
                std::cin.ignore();
                std::cin.clear();
                std::cout << "Invalid input!\n";
                break;
        }
    }
    
    return startGame;
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

bool Game::initCurrentPlayer()
{
    if(m_playerOne == NULL || m_playerTwo == NULL)
    {
        return false;
    }

    srand(time(NULL));
    m_currentPlayer = (rand() % (2)) == 0 ? m_playerOne : m_playerTwo;
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

void Game::setBoardFull()
{
    m_boardFull = true;
}

bool Game::isBoardFull()
{
    return m_boardFull;
}