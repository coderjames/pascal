#ifndef _BLOCKNODE_H_
#define _BLOCKNODE_H_

#include <string>
#include <list>
#include <map>

#include "../astnode.hpp"
class StatementNode;
class TypeNode;
class SubroutineNode;
class ExpressionNode;

class BlockNode : public ASTNode
    {
    public:
        BlockNode( std::list<StatementNode *> *_body );
        bool add_types( std::map<std::string, TypeNode *> *_t);
        bool add_variables( std::map<std::string, TypeNode *> *_v);
        bool add_labels( std::list<int> *_l );
        bool add_subroutines( std::list<SubroutineNode *> *_r );
        bool add_constants( std::map<std::string, ExpressionNode *> *_c );

        virtual ~BlockNode();

        virtual std::string pretty_print( int indent ) const;
        virtual ASTNode *evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env );

    protected:
        // reduces the block's collection of types (IN PLACE)
        // by replacing "base" types that are just identifiers (strings)
        // which are really complex types with pointers to the actual base types.
        // example:
        // TYPE INTPTR = ^INTEGER;
        // VAR ptrptr : ^INTPTR;
        // displays as "ptrptr : POINTS_TO(INTPTR)"
        // but should be reduced to: "ptrptr : POINTS_TO(POINTS_TO(INTEGER))"
        //     TypeNode("INTPTR", NULL) -> TypeNode("POINTS_TO", &IntegerType)
        //bool resolve_types( std::map<std::string, TypeNode *> *env );
        //        env is the collection of known types in the surrounding environment
        //        also commands each global variable and each statement in the body
        //        to resolve their types (which will hopefully complain about any
        //        type mismatches)

    private:
        std::list<int> *labels;
        std::map<std::string, ExpressionNode *> *constants;
        std::map<std::string, TypeNode *> *types;
        std::map<std::string, TypeNode *> *variables;
        std::list<SubroutineNode *> *subroutines;
        std::list<StatementNode *> body;
    } ;

#endif
