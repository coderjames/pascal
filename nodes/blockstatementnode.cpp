#include "blockstatementnode.h"

BlockStatementNode::~BlockStatementNode()
    {
    if( statements )
        {
        statements->clear(); // this calls the destructor of each element in the list
        delete statements;
        }
    }


std::string BlockStatementNode::pretty_print( int indent ) const
    {
    std::string result = "\n";
    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    result += tabs + "BEGIN";

    for( std::list<StatementNode *>::const_iterator it = statements->begin();
        it != statements->end();
        ++it )
        {
        result += "\n" + (*it)->pretty_print(indent);
        }

    result += "\n" + tabs + "END";

    return( result );
    }
