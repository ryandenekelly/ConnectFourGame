#include "ComputerPlayer.hpp"
#include "QuickValidator.hpp"
#include "utils.hpp"

#include <chrono>
#include <thread>


#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

ReflexPlayer::ReflexPlayer()
{

}

int ReflexPlayer::getMove(Board * board)
{

    //delay
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    std::array<int, 7> moveValues = {};

    // Iterate through all "legal" moves.
    for(int i=0; i<board->getWidth(); i++)
    {
        // find the score of the moves by counting how may streaks of the same token branch from that position
        QuickValidator validator = QuickValidator(board);
        auto streak = validator.getStreak(i);
        // if a streak > 2 can exist there, assign a value to it.
        moveValues[i] = getMoveValue(streak);
    }
    // find the best move and its index frpm the list.
    auto maxElement = std::max_element(moveValues.begin(), moveValues.end());
    auto maxElementIndex = std::distance(moveValues.begin(), maxElement);

    return maxElementIndex;
}

int ReflexPlayer::getMoveValue(QuickValidator::Streak streak)
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

Piece::Type ReflexPlayer::getPiece()
{
    return Player::getPiece();
}