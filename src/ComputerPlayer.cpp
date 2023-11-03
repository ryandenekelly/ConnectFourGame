#include "ComputerPlayer.hpp"
#include "utils.hpp"

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

int ComputerPlayer::getMoveValue(QuickValidator::Streak streak)
{
    int value = 0;
    // if own streak
    if(streak.type == getPiece())
    {
        // super high value to end game
        value = streak.count >= 3 ? 400 : 10 * streak.count;
    }
    else if(streak.type == Piece::Empty)
    {
        value = 1;
    }
    // opp streak
    else
    {
        value = streak.count >= 3 ? 200 : 10 * streak.count;
    }

    return value;
}
