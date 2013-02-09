#ifndef _ASTNODE_HPP_
#define _ASTNODE_HPP_

#include <string>
#include <list>
#include <utility>

// forward references provided to allow for pointers in environments
class TypeNode;
class VariableNode;
class ExpressionNode;

typedef std::list<TypeNode*> TypeEnvironment;
typedef std::list< std::pair<VariableNode*, ExpressionNode*> > VariableEnvironment;

class ASTNode
    {
    public:
        ASTNode() {};
        virtual ~ASTNode() {};
        virtual std::string pretty_print( int indent ) const = 0;
        virtual ASTNode *evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env )
            { return(this); };

    protected:
    } ;

#endif
