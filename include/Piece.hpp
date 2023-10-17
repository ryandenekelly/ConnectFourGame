#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>

class Piece
{
    public:
        enum Type
        {
            Empty,
            Red,
            Blue
        };

        Piece();
        Piece(Piece::Type type);
        Type getType();
        std::string getTypeString();

    private:

        Type m_type;

};

#endif