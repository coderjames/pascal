#ifndef _EXPRESSIONNODE_H_
#define _EXPRESSIONNODE_H_

#include <string>
#include <cassert>

#include "../astnode.hpp"
class TypeNode;


// pure virtual class, as all expressions are more specific
// but providing this class allows a stricter enforcement of the grammar
// when building the AST, as certain branches can be forced to have the
// correct StatementNode or ExpressionNode type.
class ExpressionNode : public ASTNode
    {
    public:
        virtual ~ExpressionNode() {};

        virtual std::string pretty_print( int indent ) const = 0;
        virtual const TypeNode *result_type() const { return( type ); };

    protected:
        virtual void result_type( TypeNode *_t ) { type = _t; };
        ExpressionNode() { type = NULL; };
        TypeNode *type;

    private:
    } ;

#endif
