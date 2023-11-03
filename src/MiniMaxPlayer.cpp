#include "ComputerPlayer.hpp"
#include "utils.hpp"

#include <algorithm>
#include <thread>


MiniMaxPlayer::MiniMaxPlayer()
{

}

int MiniMaxPlayer::getMove(Board * board)
{
    int move = minimax(board, 0, m_treeDepth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), true).column;
    return move;
}

int MiniMaxPlayer::getMoveValue(QuickValidator::Streak streak)
{
    int value = 0;
    // if own streak
    if(streak.type == Piece::Blue)
    {
        // super high value to end game
        value = streak.count >= 4 ? 1e6 : 10 * streak.count;
    }
    else if(streak.type == Piece::Red)
    {
        value = streak.count >= 4 ? -1e6 : -(10 * streak.count);
    }
    // opp streak
    else
    {
        value = 0;
    }

    return value;
}

MiniMaxPlayer::Node MiniMaxPlayer::minimax(Board * board, int node, int depth, int alpha, int beta, bool maxPlayer)
{
    // board->printBoard();
    QuickValidator validator = QuickValidator(board);
    for(int i=0; i<7; i++)
    {
        QuickValidator::Streak streak = validator.isWinningMove(i);
    
        int moveValue = getMoveValue(streak);
        

        if(std::abs(moveValue)==1e6)
        {
            // board->printBoard();
            // validator.getStreak(i, true);
            return {i, moveValue};
        }

        if(depth == 0 || board->isBoardFull() || std::abs(moveValue)==1e6)
        {
            // board->printBoard();
            return {node, moveValue};
        }
    }

    int value = 0;
    if(maxPlayer)
    {
        value = std::numeric_limits<int>::min();

        std::vector<int> legalMoves = board->getLegalMoves();
        srand(time(NULL));
        int column = legalMoves[rand() % legalMoves.size()];

        for(auto move : legalMoves)
        {
            Board board_copy = *board;

            if(!board_copy.placePiece(move, Piece::Blue))
            {
                continue;
            }

            int newScore = minimax(&board_copy, move, depth-1, alpha, beta, false).value;

            // if(depth == m_treeDepth ){std::cout << "[ "<< move << "," << newScore << "]";}

            if(newScore > value)
            {
                value = newScore;
                column = move;
            }
            alpha = std::max(alpha, value);
            if(alpha >= beta)
            {
                break;
            }
            
        }
        return {column, value};
    }
    else
    {
        value = std::numeric_limits<int>::max();

        std::vector<int> legalMoves = board->getLegalMoves();
        srand(time(NULL));
        int column = rand() % legalMoves.size();

        for(auto move : legalMoves)
        {
            Board board_copy = *board;

            if(!board_copy.placePiece(move, Piece::Red))
            {
                continue;
            }

            int newScore = minimax(&board_copy, move, depth-1, alpha, beta, true).value;

            if(newScore < value)
            {
                value = newScore;
                column = move;
            }
            beta = std::min(beta, value);
            if(alpha >= beta)
            {
                break;
            }
        }
        return {column, value};
    }
}

Piece::Type MiniMaxPlayer::getPiece()
{
    return Player::getPiece();
}