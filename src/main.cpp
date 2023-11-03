#include <iostream>
#include <ostream>
#include <chrono>

#include "Board.hpp"
#include "Player.hpp"
#include "UserPlayer.hpp"
#include "ComputerPlayer.hpp"
#include "Game.hpp"
#include "WinValidator.hpp"
#include "Validator.hpp"
#include "QuickValidator.hpp"
#include "utils.hpp"
#include "test.hpp"


#define TEST 0

int main(int argc, char *argv[])
{
    
/*-------------------------------*/
    #if TEST
    test();
    return 0;
    #endif
/*-------------------------------*/

    // Create a new game
    Game game = Game();

    // Run the start menu
    game.startMenu();

    // add players according to game type.
        // two players; prompt two names.
        if(game.getGameType() == Game::TwoPlayer)
        {
            std::cout << "Please enter name for Player1:\n";
            std::string playerOneName;
            playerOneName = "PlayerOne";
            // std::cin >> playerOneName;

            std::cout << "Please enter name for Player2:\n";
            std::string playerTwoName;
            playerTwoName = "PlayerTwo";
            // std::cin >> playerTwoName;

            game.AddPlayer(playerOneName);
            game.AddPlayer(playerTwoName);
            

        }
        // one player; prompt one name and assign ai type
        else if(game.getGameType() == Game::OnePlayer)
        {
            std::cout << "Please enter your name:\n";

            std::string playerOneName;
            playerOneName = "PlayerOne";
            // std::cin >> playerOneName;

            game.AddPlayer(playerOneName);
            game.AddPlayer(game.getOpponentType());

            
        }
    game.initCurrentPlayer();
    /* Main gameplay loop*/

    //==========================//
    // game.changeTurn();
    // game.getCurrentPlayer()->getMove(game.getBoard());

    //===========================//

    // Print out the board at the start
    game.getBoard()->printBoard();
    while(1)
    {

        // Get move from agent, loop until a valid move is recieved
        bool validMove = false;
        QuickValidator::Streak streak;
        bool winningMove = false;
        int move; 
        Piece::Type currentPiece = game.getCurrentPlayer()->getPiece();
        while(!validMove)
        {   
            // Get the move from the player agent.
            move = game.getCurrentPlayer()->getMove(game.getBoard());
            if(game.getBoard()->checkMove(move))
            {
                validMove = true;
                QuickValidator validator = QuickValidator(game.getBoard());
                game.getBoard()->placePiece(move, currentPiece);
                streak = validator.isWinningMove(move);
                winningMove = (streak.count >=4) && (streak.type == game.getCurrentPlayer()->getPiece());
            }
            else
            {   
                // If move is invalid - re-prompt
                std::cout << "Invalid Move!\n";
            }

        }
        // Print out the board after the move
        game.getBoard()->printBoard();

        if(winningMove)
        {
            std::cout << game.getCurrentPlayer()->getPlayerName() << " wins!\n";
            return 0;
        }
        if(game.getBoard()->isBoardFull())
        {
            std::cout << "Board full!\n";
            return 0;
        }   
        
        // Switch the turn.
        game.changeTurn();
    }
    

    return 0;

}