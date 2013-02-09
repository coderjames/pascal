#include <cstdio>

#include "environment.h"

#include "assignmentnode.h"
#include "variablenode.h"
#include "expressionnode.h"
#include "typenode.h"

AssignmentNode::~AssignmentNode()
    {
    if( lhs )
        delete lhs;

    if( rhs )
        delete rhs;
    }

std::string AssignmentNode::pretty_print( int indent ) const
    {
    assert( lhs );
    assert( rhs );

    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    return( tabs + lhs->pretty_print(0) + " := " + rhs->pretty_print(0) );
    }


ASTNode *AssignmentNode::evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env )
    {
    VariableNode *var = lookup_variable(lhs, vars_env);
    if( var == NULL )
        {
        printf( "\nVariable '%s' not in scope in statement:\n%s\n", lhs->pretty_print(0).c_str(),
                this->pretty_print(2).c_str() );
        }
    else
        {
        ASTNode *rhs_value = rhs->evaluate( types_env, vars_env );
        if( rhs_value == NULL )
            {
            if( dynamic_cast<VariableNode*>(rhs) )
                {
                printf( "\nAttempted to use uninitialized variable '%s'",
                        rhs->pretty_print(0).c_str() );
                }
            else
                {
                printf( "\nRight-hand side of assignment did not produce a value:\n%s\n",
                    this->pretty_print(2).c_str() );
                }
            }
        else
            {
            ExpressionNode *rhs_typed = dynamic_cast<ExpressionNode *>(rhs_value);
            if( rhs_typed == NULL ) // rhs_value isn't actually an ExpressionNode
                {
                printf( "\nRight-hand side of assignment did not produce an expression:\n%s\n",
                    this->pretty_print(2).c_str() );
                }
            else
                {
                if( rhs_typed->result_type() == NULL )
                    {
                    printf( "\nExpression on right-hand side of assignment seems to be missing a result type." );
                    printf( "\n%s\n", this->pretty_print(2).c_str() );
                    }
                else if( var->result_type() == NULL )
                    {
                    printf( "\nVariable on left-hand side of assignment seems to not have a type." );
                    printf( "\n%s\n", this->pretty_print(2).c_str() );
                    }
                else if( rhs_typed->result_type() == var->result_type() )
                    {
                    set_variable( var, rhs_typed, vars_env );
                    }
                else
                    {
                    printf( "\nAttempted assignment between incompatible types in statement:" );
                    printf( "\n%s\n\tA variable of type '%s' cannot hold a value of type '%s'\n",
                        this->pretty_print(2).c_str(), var->result_type()->pretty_print(0).c_str(),
                        rhs_typed->result_type()->pretty_print(0).c_str() );
                    }
                }
            }
        }

    // statements don't return values, they have side-effects (like an assignment)
    return( NULL );
    }
