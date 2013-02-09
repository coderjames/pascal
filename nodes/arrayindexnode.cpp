#include "arrayindexnode.h"

ArrayIndexNode::~ArrayIndexNode()
    {
    if( elements )
        {
        elements->clear();
        delete elements;
        }
    }

std::string ArrayIndexNode::pretty_print( int indent ) const
    {
    std::string result("[ ");

    for( std::list<ExpressionNode *>::const_iterator it = elements->begin();
        it != elements->end();
        ++it )
        {
        result += (*it)->pretty_print(0) + ", ";
        }

    result += " ]";
    return( result );
    }
