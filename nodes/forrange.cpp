#include "forrange.h"
#include "expressionnode.h"

ForRange::~ForRange()
    {
    if( begin )
        delete begin;
    
    if( end )
        delete end;
    }

std::string ForRange::pretty_print() const
    {
    return( begin->pretty_print(0) +
            (incrementing ? " TO " : " DOWNTO ") +
            end->pretty_print(0) );
    }
