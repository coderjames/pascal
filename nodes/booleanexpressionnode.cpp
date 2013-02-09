#include <cstdio>
#include <cassert>
#include <cstring>

#include "booleanexpressionnode.h"

BooleanExpressionNode::BooleanExpressionNode( const char *_val )
    {
    assert( _val != NULL );

    if( _stricmp(_val, "true") == 0 )
        value = true;
    else
        value = false;

    result_type( &BooleanType );
    }

std::string BooleanExpressionNode::pretty_print( int indent ) const
    {
    std::string result;
    for( int i = 0; i < indent; ++i )
        result += "\t";

    if( value )
        result += "TRUE";
    else
        result += "FALSE";

    return( result );
    }

bool BooleanExpressionNode::get_value() const
    {
    return( value );
    }
