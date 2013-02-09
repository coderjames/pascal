#ifndef _PROCEDURECALLNODE_H_
#define _PROCEDURECALLNODE_H_

#include <string>
#include <list>
#include <cassert>

#include "statementnode.h"

class ExpressionNode;

class ProcedureCallNode : public StatementNode
    {
    public:
        ProcedureCallNode( const char *_p ) : procedure_name(_p), arguments(NULL)
            { assert(_p != NULL); };

        ProcedureCallNode( const char *_p, std::list<ExpressionNode *> *_a ) :
            procedure_name(_p), arguments(_a)
            { assert(_p != NULL); assert(_a != NULL); };

        virtual ~ProcedureCallNode();

        virtual std::string pretty_print( int indent ) const;

    private:
        std::string procedure_name;
        std::list<ExpressionNode *> *arguments;
    } ;

#endif
