#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Board.hpp"
#include <memory>

class Game
{   
    public:
        Game();
        ~Game();

        enum GameType
        {
            OnePlayer,
            TwoPlayer
        };

        enum OpponentType
        {
            Reflex,
            MiniMax,
            ExpMax
        };

        bool AddPlayer(std::string& playerName);
        bool AddPlayer(Game::OpponentType opponentType);
        void startGame();

        void changeTurn();
        bool startMenu();
        bool opponentMenu();
        bool initCurrentPlayer();
        void endGame();

        Board* getBoard();

        GameType getGameType();
        OpponentType getOpponentType();

        Player* getCurrentPlayer();

        void setBoardFull();
        bool isBoardFull();




    private:
        GameType m_gameType;
        OpponentType m_opponentType;
        Board *m_board;
        Player *m_playerOne;
        Player *m_playerTwo;
        Player *m_currentPlayer;
        int m_score;
        Player* m_winner;
        bool m_boardFull;

        


};

#endif