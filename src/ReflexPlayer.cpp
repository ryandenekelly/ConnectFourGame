#include "ComputerPlayer.hpp"
#include "Validator.hpp"
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
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(500ms);
    // NB: Misleading name; Can give an illeagal move - if top of column is greater than the board height!
    auto listOfLegalMoves = board->getTopOfColumns();
    std::array<int, 7> moveValues = {};

    // Iterate through all "legal" moves.
    for(int i=0; i<listOfLegalMoves.size(); i++)
    {
        // if the leagal move is actually ileagal give it a negative utility
        if(listOfLegalMoves[i] >= board->getHeight())
        {
            moveValues[i] = -1;
        }
        // find the score of the moves by counting how may streaks of the same token branch from that position
        else
        {
            Validator validator = Validator(board);
            std::vector<std::pair<Piece::Type, int>> streaks = validator.findStreaks(i, listOfLegalMoves[i], 4);
            // if a streak > 2 can exist there, assign a value to it.
            moveValues[i] = getMoveValue(streaks);
        }
    }
    // find the best move and its index frpm the list.
    auto maxElement = std::max_element(moveValues.begin(), moveValues.end());
    auto maxElementIndex = std::distance(moveValues.begin(), maxElement);

    int returnMove;
    // if there is no "good" move then pick a random move.
    if(maxElement == 0)
    {
        returnMove = rand() % (board->getWidth()-1);
        // make sure the random move value>0.
        while(listOfLegalMoves[returnMove] < 0)
        {
            returnMove = rand() % (board->getWidth()-1);
        }
    }
    // else there is a "good" move, so use that.
    else
    {
        returnMove = maxElementIndex;
    }

    return returnMove;
}

int ReflexPlayer::getMoveValue(std::vector<std::pair<Piece::Type, int>> streaks)
{
    int value = 0;
    for(std::pair<Piece::Type, int> streak : streaks)
    {
        // if own streak
        if(streak.first == getPiece())
        {
            // super high value to end game
            if(streak.second >= 3)
            {
                value += 400;
            }
            else
            {
                value += (10 * streak.second);
            }
        }
        // not a streak
        else if(streak.first == Piece::Empty)
        {
            value +=1;
        }
        // opp streak
        else
        {
            //high value to save from losing
            if(streak.second >= 3)
            {
                value += 300;
            }
            else
            {
                value += (20 * streak.second);
            }
        }
    }
    return value;
}

Piece::Type ReflexPlayer::getPiece()
{
    return Player::getPiece();
}