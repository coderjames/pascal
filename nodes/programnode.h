#ifndef _PROGRAMNODE_H_
#define _PROGRAMNODE_H_

#include <string>
#include <list>

#include "../astnode.hpp"

class BlockNode;

class ProgramNode : public ASTNode
    {
    public:
        // when only the body block is present (no uses list)
        ProgramNode( std::string _name, BlockNode *_body ) : name( _name ), body(_body) {};

        // when both the body block and a uses list are present
        ProgramNode( std::string _name, std::list<std::string> *_uses, BlockNode *_body ) :
            name( _name ), uses(*_uses), body(_body) {};

        virtual ~ProgramNode();
        virtual std::string pretty_print( int indent ) const;
        virtual ASTNode *evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env );

    private:
        std::string name;
        std::list<std::string> uses;
        BlockNode *body;
    } ;

#endif
