#include "gotonode.h"

#include <cstdio>
#include <cassert>
#include <cstring>

std::string GotoNode::pretty_print( int indent ) const
    {
    assert( sizeof(int) <= 4 );
    char buffer[11] = "----------"; // big enough for x_xxx_xxx_xxx + null
    buffer[10] = '\0';

    sprintf( buffer, "%d", label );

    // shouldn't ever happen, but better test for it anyway
    assert( strlen(buffer) > 0 );

    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    return( tabs + "GOTO( " + std::string(buffer) + " )" );
    }
