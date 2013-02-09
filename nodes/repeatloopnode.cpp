#include "repeatloopnode.h"
#include "expressionnode.h"

RepeatLoopNode::~RepeatLoopNode()
    {
    if( test )
        delete test;

    if( body )
        delete body;
    }

std::string RepeatLoopNode::pretty_print( int indent ) const
    {
    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    std::string result(tabs);

    result += "REPEAT\n" + body->pretty_print(indent+1) + "\n" + tabs + "UNTIL " + test->pretty_print(0);

    return( result );
    }

