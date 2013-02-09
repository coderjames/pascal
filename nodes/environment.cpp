#include "environment.h"
#include "variablenode.h"

VariableNode *lookup_variable(VariableNode *var, VariableEnvironment *environment)
    {
    if( (var == NULL) || (environment == NULL) )
        return( NULL );

    for( VariableEnvironment::iterator it = environment->begin();
        it != environment->end();
        ++it )
        {
        if( var == it->first )
            return( it->first );       /// actually the same physical VariableNode

        if( (*var) == (*(it->first)) ) /// equivalent nodes (more likely)
            return( it->first );       /// return the one in the environment so that updates
                                       /// to it will update the value stored in the env
        }

    return( NULL );
    }

void set_variable( VariableNode *var, ExpressionNode *value, VariableEnvironment *environment)
    {
    if( (var == NULL) || (environment == NULL) )
        return;

    // don't check for the value being NULL because that is allowed

    for( VariableEnvironment::iterator it = environment->begin();
        it != environment->end();
        ++it )
        {
        if( var == it->first )
            it->second = value;
        }
    }

ExpressionNode *get_value( VariableNode *var, VariableEnvironment *environment )
    {
    if( (var == NULL) || (environment == NULL) )
        return( NULL );

    for( VariableEnvironment::iterator it = environment->begin();
        it != environment->end();
        ++it )
        {
        if( var == it->first )
            return( it->second );       /// actually the same physical VariableNode

        if( (*var) == (*(it->first)) ) /// equivalent nodes (more likely)
            return( it->second );
        }

    return( NULL );
    }
