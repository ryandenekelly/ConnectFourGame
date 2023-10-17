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

}


bool Game::checkVerticalWin()
{
    Board *board = getBoard();
    
    // Go along the width of the board.
    for(int x_pos = 0; x_pos < board->getWidth(); x_pos++)
    {
        // Go up the column looking for streaks.
        Piece::Type streakType = Piece::Empty;
        int streakCount = 0;
        
        for(int y_pos=0; y_pos < board->getHeight(); y_pos++)
        {
            Piece currentPiece = board->getPiece(x_pos, y_pos);
            // if you reach an empty piece, that means no streak; Move to the next column.
            if(currentPiece.getType() == Piece::Empty)
            {
                break;
            }
            // if steakType is still empty, a streak has not been started - so we start it.
            if(streakType == Piece::Empty)
            {
                streakType = currentPiece.getType();
                streakCount++;
                continue;
            }
            // if the current streakType is the same as the current type, then increment the streak type
            if(streakType == currentPiece.getType())
            {
                streakCount++;
            }
            // else it is not the same, so switch the type and reset the streak.
            else
            {
                
                streakType = currentPiece.getType();
                streakCount = 1;
                continue;
            }
            if(streakCount>=4)
            {
                std::cout << getCurrentPlayer()->getPlayerName() << " Wins!\n";
                return true;
            }

        }
    }
    return false;
}

bool Game::checkHorizontalWin()
{
    Board *board = getBoard();

    // go up the column.
    for(int y_pos=0; y_pos < board->getHeight(); y_pos++)
    {
        Piece::Type streakType = Piece::Empty;
        int streakCount = 0;

        // go accross the rows looking for streaks
        for(int x_pos=0; x_pos < board->getWidth(); x_pos++)
        {
            Piece currentPiece = board->getPiece(x_pos, y_pos);
            // if you reach an empty piece, that means no streak; Move to the next column.
            if(currentPiece.getType() == Piece::Empty)
            {
                break;
            }
            // if steakType is still empty, a streak has not been started - so we start it.
            if(streakType == Piece::Empty)
            {
                streakType = currentPiece.getType();
                streakCount++;
                continue;
            }
            // if the current streakType is the same as the current type, then increment the streak type
            if(streakType == currentPiece.getType())
            {
                streakCount++;
            }
            // else it is not the same, so switch the type and reset the streak.
            else
            {
                
                streakType = currentPiece.getType();
                streakCount = 1;
                continue;
            }
            if(streakCount>=4)
            {
                std::cout << getCurrentPlayer()->getPlayerName() << " Wins!\n";
                return true;
            }
        }
    }
    return false;
}

bool Game::checkDiagonalWin()
{
    Board *board = getBoard();
    int h = board->getHeight();
    int w = board->getWidth();

    // valid streak origins from left side
    for(int origin_x = 0, origin_y = h-4; origin_x>=0 && origin_y>= 0; origin_y--)
    {
        for(int streak_x = origin_x, streak_y = origin_y; streak_x<w && streak_y<h; streak_x++, streak_y++)
        {
            // TODO: comparison here
        }
    }

    // valid streak origins from bottom side
    for(int origin_x = w-4, origin_y = 0; origin_x>0 && origin_y>= 0; origin_x--)
    {
        for(int streak_x = origin_x, streak_y = origin_y; streak_x<w && streak_y<h; streak_x++, streak_y++)
        {
            // TODO: comparison here
        }
    }
    return false;
}

bool Game::checkBoardFull()
{
    return false;
}


bool Game::isGameOver()
{
    // NB: short-circuit evaluation.
    return checkBoardFull() || checkVerticalWin() || checkHorizontalWin() || checkDiagonalWin();
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