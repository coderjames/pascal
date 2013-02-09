#include "whileloopnode.h"
#include "expressionnode.h"

WhileLoopNode::~WhileLoopNode()
    {
    if( test )
        delete test;
        
    if( body )
        delete body;
    }

std::string WhileLoopNode::pretty_print( int indent ) const
    {
    std::string result;

    for( int i = 0; i < indent; ++i )
        result += "\t";

    result += "WHILE " + test->pretty_print(0) + " DO\n" + body->pretty_print(indent + 1);
    
    return( result );
    }
