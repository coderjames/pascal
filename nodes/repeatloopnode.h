#ifndef _REPEATLOOPNODE_H_
#define _REPEATLOOPNODE_H_

#include <string>
#include <cassert>

#include "statementnode.h"

class ExpressionNode;

class RepeatLoopNode : public StatementNode
    {
    public:
        RepeatLoopNode( StatementNode *_b, ExpressionNode *_t ) : test(_t), body(_b)
            { assert( _t != NULL ); assert( _b != NULL ); };
        
        virtual ~RepeatLoopNode();
        
        virtual std::string pretty_print( int indent ) const;

    private:
        ExpressionNode *test;
        StatementNode *body;
    } ;

#endif
