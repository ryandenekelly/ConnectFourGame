#include <iostream>

#include "Board.hpp"
#include "Player.hpp"
#include "UserPlayer.hpp"
#include "Game.hpp"
#include "WinValidator.hpp"

int main(int argc, char *argv[])
{

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

            game.AddUserPlayer(playerOneName);
            game.AddUserPlayer(playerTwoName);
            
            game.initTurnSwitcher();

        }
        // one player; prompt one name and assign ai type
        else if(game.getGameType() == Game::OnePlayer)
        {
            std::cout << "Please enter your name:\n";
            std::string playerName;
            std::cin >> playerName;

            game.AddUserPlayer(playerName);
            game.AddComputerPlayer(game.getOpponentType());

            game.initTurnSwitcher();
        }

    /* Main gameplay loop*/

    // Print out the board at the start
    game.getBoard()->printBoard();
    while(1)
    {

        // Get move from agent, loop until a valid move is recieved
        bool validMove = false;
        int move; 
        Piece::Type currentPiece = game.getCurrentPlayer()->getPiece();
        while(!validMove)
        {   
            // Get the move from the player agent.
            move = game.getCurrentPlayer()->getMove();
            // Place the piece if the move is valid.
            validMove = game.getBoard()->placePiece(move, currentPiece);
            if(!validMove)
            {   
                // If move is invalid - re-prompt
                std::cout << "Invalid Move!\n";
                continue;
            }

        }
        // Print out the board after the move
        game.getBoard()->printBoard();



        {
            WinValidator validator = WinValidator(game.getBoard(), Piece::Red);
            if(validator.isGameOver())
            {
                std::cout << game.getCurrentPlayer()->getPlayerName() << " wins!\n";
                break;
            }
        }

        // if(game.isGameOver())
        // {
        //     break;
        // }        
        
        // Switch the turn.
        game.changeTurn();
    }
    







}