#ifndef _AST_H_
#define _AST_H_

class ProgramNode;
class UnitNode;
class ASTNode;

class AST
    {
    public:
        AST();
        ~AST();

        // have two explicit constructors instead of allowing generic ASTNode*
        // so that you can't build an AST that is rooted by anything other than
        // a program or unit
        void set_program( ProgramNode *p );
        void set_program( UnitNode *p );

        void pretty_print() const;
        void evaluate();

    protected:
        ASTNode *program; // may be a ProgramNode* or a UnitNode*
    } ;

#endif
