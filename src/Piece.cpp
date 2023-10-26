#include "Piece.hpp"
#include <string>


Piece::Piece()
{
    m_type = Piece::Empty;
}
Piece::Piece(Piece::Type type)
{
    m_type = type;
}


Piece::Type Piece::getType()
{
    return m_type;
}

std::string Piece::getTypeString()
{
    if(m_type == Type::Empty)
    {
        return "Empty";
    }
    else if(m_type == Type::Red)
    {
        return "Red";
    }
    else if(m_type == Type::Blue)
    {
        return "Blue";
    }
    else
    {
        return "Invalid Type";
    }
    
}