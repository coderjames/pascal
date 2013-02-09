#include "subroutinenode.h"
#include "blocknode.h"
#include "typenode.h"

SubroutineNode::~SubroutineNode()
    {
    if( parameters )
        {
        parameters->clear();
        delete parameters;
        }
        
    if( body )
        delete body;
        
    if( result_type )
        delete result_type;
    }


std::string SubroutineNode::pretty_print( int indent ) const
    {
    std::string result;

    for( int i = 0; i < indent; ++i )
        result += "\t";

    if( result_type )
        result += "FUNCTION ";
    else
        result += "PROCEDURE ";

    result += name;
    result += "( ";

    if( parameters )
        {
        for( std::map<std::string, TypeNode *>::const_iterator it = parameters->begin();
            it != parameters->end();
            ++it )
            {
            result += it->first; // parameter name
            result += " : ";
            result += it->second->pretty_print(0); // parameter type
            result += ", ";
            }
        }

    result += ") ";

    if( result_type )
        result += " : " + result_type->pretty_print(0);
        
    if( body )
        result += "\n" + body->pretty_print(indent + 1);
    else
        result += " FORWARD;";

    return( result );
    }
