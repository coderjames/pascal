#include "stringexpressionnode.h"

std::string StringExpressionNode::pretty_print( int indent ) const
    {
    return( "'" + value + "'" );
    }

std::string StringExpressionNode::get_value() const
    {
    return value;
    }
