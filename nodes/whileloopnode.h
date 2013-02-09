#ifndef _WHILELOOPNODE_H_
#define _WHILELOOPNODE_H_

#include <string>
#include <cassert>

#include "statementnode.h"

class ExpressionNode;

class WhileLoopNode : public StatementNode
    {
    public:
        WhileLoopNode( ExpressionNode *_t, StatementNode *_b ) : test(_t), body(_b)
            { assert(_t != NULL); assert(_b != NULL); };

        virtual ~WhileLoopNode();

        virtual std::string pretty_print( int indent ) const;

    private:
        ExpressionNode *test;
        StatementNode *body;
    } ;


#endif
