#ifndef _LABELEDSTATEMENTNODE_H_
#define _LABELEDSTATEMENTNODE_H_

#include <string>
#include <cassert>

#include "statementnode.h"

class LabeledStatementNode : public StatementNode
    {
    public:
        LabeledStatementNode( int _lbl, StatementNode *_stmt ) : label(_lbl), statement(_stmt)
                { assert(_stmt != NULL); };
        virtual ~LabeledStatementNode();
        virtual std::string pretty_print( int indent ) const;

    private:
        int label;
        StatementNode *statement;
    } ;



#endif
