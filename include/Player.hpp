#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Piece.hpp"

#include <string>


class Player
{
    public:
        Player();
    

        Player(Piece::Type type, std::string name);

        void setPiece(Piece::Type type);
        Piece::Type getPiece();

        int getPlayerScore();
        void setPlayerScore(int score);

        void setPlayerName(std::string name);
        std::string getPlayerName();

        virtual int getMove();


    
    private:
        Piece::Type m_playerPiece;
        int m_playerScore;
        std::string m_playerName;


};

#endif