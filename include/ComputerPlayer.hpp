#ifndef COMPUTER_PLAYER_HPP
#define COMPUTER_PLAYER_HPP

#include "Player.hpp"

class ComputerPlayer : public Player
{
    public:
        ComputerPlayer();
};

class ReflexPlayer : public ComputerPlayer
{
    public:
        ReflexPlayer();
};

class MiniMaxPlayer : public ComputerPlayer
{
    public:
        MiniMaxPlayer();
};

class ExpMaxPlayer : public ComputerPlayer
{
    public:
        ExpMaxPlayer();
};

#endif