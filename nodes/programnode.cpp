#include <cassert>
#include <cstdio>

#include "programnode.h"
#include "blocknode.h"

ProgramNode::~ProgramNode()
    {
    if( body )
        delete body;
    }


std::string ProgramNode::pretty_print( int indent ) const
    {
    std::string result = std::string("\nPROGRAM: ") + name;
    std::string tabs;

    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    if( uses.empty() == false )
        {
        result += std::string( "\n\t" + tabs + "USES: " );

        for( std::list<std::string>::const_iterator it = uses.begin(); it != uses.end(); ++it )
            result += (*it + " ");
        }

    if( body )
        result += std::string("\n") + body->pretty_print(indent);

    return( result );
    }


ASTNode *ProgramNode::evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env )
    {
    // pointers are expected to come in NULL. If they don't, something strange is happening...
    assert( types_env == NULL );
    assert( vars_env == NULL );

    types_env = new TypeEnvironment;
    vars_env = new VariableEnvironment;

    // do something with the uses statements

    ASTNode *result = NULL;
    if( body )
        result = body->evaluate(types_env, vars_env);
    else
        {
        printf( "\n\tProgramNode has no body to evaluate." );
        fflush( stdout );
        }

    delete types_env;
    delete vars_env;

    return( result );
    }
