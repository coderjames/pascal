#include "unitnode.h"
#include "blocknode.h"

UnitNode::~UnitNode()
    {
    if( implementation_body )
        delete implementation_body;
    }


std::string UnitNode::pretty_print( int indent ) const
    {
    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    std::string result( "\n" + tabs + "UNIT: " + name );

    if( implementation_uses.empty() == false )
        {
        result += std::string( "\n\t" + tabs + "USES: " );

        for( std::list<std::string>::const_iterator it = implementation_uses.begin();
             it != implementation_uses.end();
             ++it )
            result += (*it + " ");
        }

    if( implementation_body )
        result += "\n" + implementation_body->pretty_print(indent+1);

    return( result );
    }
