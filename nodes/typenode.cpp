#include "typenode.h"

TypeNode::~TypeNode()
    {
    if( base_type )
        delete base_type;
    }


std::string TypeNode::pretty_print( int indent ) const
    {
    std::string result( name );

    if( base_type )
        result += "(" + base_type->pretty_print(indent) + ")";
        
    return( result );
    }
