#include "withnode.h"
#include "variablenode.h"

WithNode::~WithNode()
    {
    if( records )
        {
        records->clear();
        delete records;
        }
    
    if( body )
        delete body;
    }

std::string WithNode::pretty_print( int indent ) const
    {
    std::string result;
    std::string tabs;

    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    result = tabs + "WITH ";

    for( std::list<VariableNode *>::const_iterator it = records->begin();
        it != records->end();
        ++it )
        {
        result += (*it)->pretty_print(0) + ", ";
        }

    result += " DO\n" + body->pretty_print(indent + 1);

    return( result );
    }
