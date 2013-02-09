#ifndef _VARIABLENODE_H_
#define _VARIABLENODE_H_

#include <string>
#include <list>
#include <cassert>

#include "expressionnode.h"

class VariableNode : public ExpressionNode
    {
    public:
        // basic contructor
        VariableNode( const char *_id )
            : root(NULL), identifier_name(_id), dimensions(NULL), is_dereference(false)
            { assert( _id != NULL ); };

        // pointer dereference constructor
        VariableNode( VariableNode *_root, bool deref )
            : root(_root), dimensions(NULL), is_dereference(true)
            { assert( _root != NULL ); };

        // record-access constructor
        VariableNode( VariableNode *_root, const char *_fld )
            : root(_root), field_name(_fld), dimensions(NULL), is_dereference(false)
            { assert( _fld != NULL ); assert(_root != NULL); };

        // array-access constructor
        VariableNode( VariableNode *_root, std::list<ExpressionNode *> *_dm )
            : root(_root), dimensions(_dm), is_dereference(false)
            { assert( _root != NULL ); assert(_dm != NULL ); };

        virtual ~VariableNode();

        virtual std::string pretty_print( int indent ) const;
        virtual ASTNode *evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env );

        // normally, the type of an expression cannot be set externally
        // but variable types may need to be changed as more information is learned
        void set_type( TypeNode *_t ) { result_type(_t); };

        bool operator==(const VariableNode &rhs) const;
        bool operator!=(const VariableNode &rhs) const { return !(*this == rhs); };

    private:
        VariableNode *root; // for when the var is not just a simple identifier
        std::string identifier_name;
        std::string field_name;
        std::list<ExpressionNode *> *dimensions;
        bool is_dereference;
    } ;

#endif
