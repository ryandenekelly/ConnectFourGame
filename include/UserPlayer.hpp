#ifndef USER_PLAYER_HPP
#define USER_PLAYER_HPP

#include "Player.hpp"
#include "Board.hpp"

class UserPlayer : public Player
{
    public:
        UserPlayer();
        UserPlayer(Piece::Type type, std::string name);
        virtual int getMove(Board * board);
};

#endif