#include "unaryexpressionnode.h"

std::string unop2string( UnaryOperator op )
    {
    switch( op )
        {
        case UNOP_PLUS:
            return( std::string("+") );

        case UNOP_MINUS:
            return( std::string("-") );

        case UNOP_NOT:
            return( std::string("NOT") );

        case UNOP_ADDRESS_OF:
            return( std::string("ADDRESS_OF") );

        default:
            return( std::string("UNKNOWN UNOP") );
        }
    }


UnaryExpressionNode::~UnaryExpressionNode()
    {
    if( rhs )
        delete rhs;
    }

std::string UnaryExpressionNode::pretty_print( int indent ) const
    {
    assert( rhs );

    return( unop2string(op) + "(" + rhs->pretty_print(indent) + ")" );
    }
