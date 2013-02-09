#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>

#include "numberexpressionnode.h"

NumberExpressionNode::NumberExpressionNode( const char *_val )
    {
    assert( _val != NULL );
    value = atoi( _val );
    result_type( &IntegerType );
    }

std::string NumberExpressionNode::pretty_print( int indent ) const
    {
    assert( sizeof(int) <= 4 );
    char buffer[11] = "----------"; // big enough for x_xxx_xxx_xxx + null
    buffer[10] = '\0';

    sprintf(buffer,"%d",value);

    // shouldn't ever happen, but better test for it anyway
    assert( strlen(buffer) > 0 );

    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    return tabs + std::string(buffer);
    }

int NumberExpressionNode::get_value() const
    {
    return value;
    }
