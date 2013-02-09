#ifndef _ASSIGNMENTNODE_H_
#define _ASSIGNMENTNODE_H_

#include <string>
#include <cassert>

#include "statementnode.h"
class VariableNode;
class ExpressionNode;

class AssignmentNode : public StatementNode
    {
    public:
        AssignmentNode( VariableNode *v, ExpressionNode *e ) : lhs(v), rhs(e)
            {
            assert( v != NULL );
            assert( e != NULL );
            };
        virtual ~AssignmentNode();
        virtual std::string pretty_print( int indent ) const;
        virtual ASTNode *evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env );

    private:
        VariableNode *lhs;
        ExpressionNode *rhs;
    } ;

#endif
