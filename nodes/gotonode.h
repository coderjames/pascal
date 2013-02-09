#ifndef _GOTONODE_H_
#define _GOTONODE_H_

#include <string>

#include "statementnode.h"

class GotoNode : public StatementNode
    {
    public:
        GotoNode( int _lbl ) : label(_lbl) {};
        virtual ~GotoNode() {};
        virtual std::string pretty_print( int indent ) const;
            
    private:
        int label;
    } ;

#endif
