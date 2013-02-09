#include "procedurecallnode.h"

ProcedureCallNode::~ProcedureCallNode()
    {
    if( arguments )
        {
        arguments->clear();
        delete arguments;
        }
    }

std::string ProcedureCallNode::pretty_print( int indent ) const
    {
    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    return( tabs + "<proc: " + procedure_name + ">" );
    }

