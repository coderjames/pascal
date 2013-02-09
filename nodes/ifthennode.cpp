#include "ifthennode.h"
#include "expressionnode.h"

IfThenNode::~IfThenNode()
    {
    if( test )
        delete test;
        
    if( body )
        delete body;
    }

std::string IfThenNode::pretty_print( int indent ) const
    {
    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    return( tabs + "IF " + test->pretty_print(0) + " THEN\n" + body->pretty_print(indent + 1) );
    }
