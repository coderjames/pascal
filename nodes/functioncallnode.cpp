#include "functioncallnode.h"

FunctionCallNode::~FunctionCallNode()
    {
    if( args )
        {
        args->clear();
        delete args;
        }
    }

std::string FunctionCallNode::pretty_print( int indent ) const
    {
    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    return( tabs + "<func call: " + function_name + ">" );
    }
