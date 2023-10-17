#include "Player.hpp"
#include "Piece.hpp"

#include <iostream>

Player::Player()
{
    m_playerPiece = Piece::Empty;
    m_playerScore = 0;
    m_playerName = "NULL";
}

Player :: Player(Piece::Type type, std::string name)
{
    m_playerPiece = type;
    m_playerScore = 0;
    m_playerName = name;
}

void Player::setPiece(Piece::Type type)
{
    m_playerPiece = type;
}
Piece::Type Player::getPiece()
{
    return m_playerPiece;
}

int Player::getPlayerScore()
{
    return m_playerScore;
}
void Player::setPlayerScore(int score)
{
    m_playerScore = score;
}

void Player::setPlayerName(std::string name)
{
    m_playerName = name;
}
std::string Player::getPlayerName()
{
    return m_playerName;
}

int Player::getMove()
{
    return 0;
}