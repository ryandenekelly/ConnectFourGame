#include <iostream>
#include <ostream>

#include "Board.hpp"
#include "Player.hpp"
#include "UserPlayer.hpp"
#include "Game.hpp"
#include "WinValidator.hpp"
#include "utils.hpp"


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
            move = game.getCurrentPlayer()->getMove(game.getBoard());
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


        // NB: I know that checking the whole board at the end of each turn
        // for a win condition is not the best way to do it, but it's implemneted
        // and I can't be bothered changing it. I will change it if speed because an issue.

        //TODO: Make win validation check just the siz direction around the piece that was placed
        //** it's O(8*4) vs ~O(7*6*2 + 28*2) **//
        {
            WinValidator validator = WinValidator(game.getBoard());
            if(validator.isGameOver() && !game.isBoardFull())
            {
                std::cout << game.getCurrentPlayer()->getPlayerName() << " wins!\n";
                break;
            }
            else if(game.isBoardFull())
            {
                std::cout << "Board is full!\n";
                break;
            }
        }      
        
        // Switch the turn.
        game.changeTurn();
    }
    

    return 0;

}