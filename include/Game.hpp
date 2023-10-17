#include "Player.hpp"
#include "Board.hpp"
#include <memory>

class Game
{   
    public:
        Game();

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

        bool AddUserPlayer(std::string& playerName);
        bool AddComputerPlayer(Game::OpponentType opponentType);
        void startGame();

        void changeTurn();
        bool startMenu();
        bool opponentMenu();
        bool initTurnSwitcher();
        void endGame();

        Board* getBoard();

        GameType getGameType();
        OpponentType getOpponentType();

        Player* getCurrentPlayer();

        void makeMove();        
        
        bool checkBoardFull();
        bool checkVerticalWin();
        bool checkHorizontalWin();
        bool checkDiagonalWin();
        bool isGameOver();



    private:
        GameType m_gameType;
        OpponentType m_opponentType;
        Board *m_board;
        Player *m_playerOne;
        Player *m_playerTwo;
        Player *m_currentPlayer;
        int m_score;
        Player* m_winner;

        


};

