#ifndef _STATEMENTNODE_H_
#define _STATEMENTNODE_H_

#include <string>

#include "../astnode.hpp"

// pure virtual class, as all statements are more specific
// but providing this class allows a stricter enforcement of the grammar
// when building the AST, as certain branches can be forced to have the
// correct StatementNode or ExpressionNode type.
class StatementNode : public ASTNode
    {
    public:
        virtual ~StatementNode() {};

        virtual std::string pretty_print( int indent ) const = 0;

    protected:
        StatementNode() {};

    private:
    } ;

#endif
