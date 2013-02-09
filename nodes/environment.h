#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

// contains the two environment typedefs
#include "../astnode.hpp"

class VariableNode;
class ExpressionNode;

VariableNode *lookup_variable(VariableNode *var, VariableEnvironment *environment);
void set_variable( VariableNode *var, ExpressionNode *value, VariableEnvironment *environment);
ExpressionNode *get_value( VariableNode *var, VariableEnvironment *environment );

#endif
