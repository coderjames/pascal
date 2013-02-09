#ifndef _IFTHENNODE_H_
#define _IFTHENNODE_H_

#include <string>
#include <cassert>

#include "statementnode.h"

class ExpressionNode;

class IfThenNode : public StatementNode
    {
    public:
        IfThenNode( ExpressionNode *_t, StatementNode *_b ) : test(_t), body(_b)
            { assert( _t != NULL ); assert( _b != NULL ); };
        virtual ~IfThenNode();

        virtual std::string pretty_print( int indent ) const;

    private:
        ExpressionNode *test;
        StatementNode *body;
    } ;

#endif
