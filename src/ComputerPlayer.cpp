#include "ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer()
{

}

ComputerPlayer::ComputerPlayer(Piece::Type type)
{
    setPiece(type);
    setPlayerScore(0);
    setPlayerName("CPU");
}


int ComputerPlayer::getMove(Board * board)
{
    return -1;
}

// Piece::Type ComputerPlayer::getPiece()
// {
//     return Player::getPiece();
// }