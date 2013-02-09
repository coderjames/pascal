#include "forloopnode.h"
#include "forrange.h"

ForLoopNode::~ForLoopNode()
    {
    if( range )
        delete range;
        
    if( body )
        delete body;
    }


std::string ForLoopNode::pretty_print( int indent ) const
    {
    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    return( tabs + "FOR " +
            counter_name + " := " + range->pretty_print() +
            " DO\n" +
            body->pretty_print(indent + 1) );
    }
