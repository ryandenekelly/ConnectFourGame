#include "UserPlayer.hpp"
#include <iostream>

UserPlayer::UserPlayer()
{

}

UserPlayer::UserPlayer( Piece::Type type, std::string name)
{
    setPiece(type);
    setPlayerScore(0);
    setPlayerName(name);
}

int UserPlayer::getMove(Board * board)
{

    std::cout << "Please enter a column to place your piece:\n";
    int move;
    std::cin >> move;

    return move;

}