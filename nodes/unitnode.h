#ifndef _UNITNODE_H_
#define _UNITNODE_H_

#include <string>
#include <list>

#include "../astnode.hpp"
class BlockNode;

class UnitNode : public ASTNode
    {
    public:
        // when only an implementation body section is present
        UnitNode( std::string _name, BlockNode *_impl_body ) :
                name( _name ), implementation_body(_impl_body) {};

        // when only the implementation uses and body sections are present (no interface sections)
        UnitNode( std::string _name, std::list<std::string> *_impl_uses, BlockNode *_impl_body ) :
                name( _name ), implementation_uses(*_impl_uses), implementation_body(_impl_body) {};

        virtual ~UnitNode();
        virtual std::string pretty_print( int indent ) const;

    private:
        std::string name;
        std::list<std::string> implementation_uses;
        BlockNode *implementation_body;
    } ;

#endif
