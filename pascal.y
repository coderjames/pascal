/* This is a Pascal grammar file for use with the LEMON parser generator
available from: http://www.hwaci.com/sw/lemon/ */

/* the generated parser contains calls to assert(), so we need this */
%include {#include <cassert>}

/* the generated parser needs to be aware of the quex:: namespace
    because the minor token type is a quex::Token* */
%include {#include "tiny_lexer"}

/* and this header provides all the class declarations for building the AST */
%include {
#include <string>
#include "astnode.hpp"
#include "nodes/ast.h"
#include "nodes/expressionnode.h"
#include "nodes/statementnode.h"
#include "nodes/binaryexpressionnode.h"
#include "nodes/unaryexpressionnode.h"
#include "nodes/functioncallnode.h"
#include "nodes/arrayindexnode.h"
#include "nodes/variablenode.h"
#include "nodes/blocknode.h"
#include "nodes/programnode.h"
#include "nodes/unitnode.h"
#include "nodes/typenode.h"
#include "nodes/blockstatementnode.h"
#include "nodes/assignmentnode.h"
#include "nodes/ifthennode.h"
#include "nodes/whileloopnode.h"
#include "nodes/forloopnode.h"
#include "nodes/procedurecallnode.h"
#include "nodes/withnode.h"
#include "nodes/gotonode.h"
#include "nodes/labeledstatementnode.h"
#include "nodes/numberexpressionnode.h"
#include "nodes/stringexpressionnode.h"
#include "nodes/booleanexpressionnode.h"
#include "nodes/repeatloopnode.h"
#include "nodes/forrange.h"
#include "nodes/subroutinenode.h"
#include "nodes/arraytypenode.h"
#include "nodes/settypenode.h"
#include "nodes/recordtypenode.h"

/* convert std::basic_string<unsigned char> to std::string<char> */
std::string ustr2str( std::basic_string<unsigned char> ustr )
    {
    const char *tmp_signed = reinterpret_cast<const char *>(ustr.c_str());

    return( std::string(tmp_signed) );
    }
}

/* give the tokens a unique prefix different from the QUEX token IDs */
%token_prefix  LEMON_

%token_type    { quex::Token* }

%syntax_error
    {
    printf( "\nERROR: Parser encountered a syntax error." );
    printf( "\n\terror was on line %d at column %d",
            TOKEN->line_number(), TOKEN->column_number() );
    printf( "\n\tBad LEMON token id was '%d'", yymajor );
    }

%extra_argument { AST *ast }

pascal_program ::= PROGRAM IDENTIFIER(n) SEMICOLON uses_section(u) block(b) PERIOD .
    {
    ast->set_program( new ProgramNode(ustr2str(n->get_text()), u, b) );
    }

pascal_program ::= PROGRAM IDENTIFIER(n) program_heading SEMICOLON block(b) PERIOD .
    {
    ast->set_program( new ProgramNode(ustr2str(n->get_text()), b) );
    }

pascal_program ::= UNIT IDENTIFIER(n) SEMICOLON INTERFACE uses_section block IMPLEMENTATION uses_section(impl_u) block(b) PERIOD .
    {
    ast->set_program( new UnitNode(ustr2str(n->get_text()), impl_u, b) );
    }

%type program_heading {std::list<std::string> *}
program_heading(h) ::= LPAREN identifier_list(i_l) RPAREN .
    { h = i_l; }

%type identifier_list {std::list<std::string> *}
identifier_list(i_l) ::= IDENTIFIER(n) .
    {
    i_l = new std::list<std::string>;
    i_l->push_back( ustr2str(n->get_text()) );
    }
identifier_list(i_l_bigger) ::= identifier_list(i_l_orig) COMMA IDENTIFIER(n) .
    {
    i_l_bigger = i_l_orig;
    i_l_bigger->push_back( ustr2str(n->get_text()) );
    }


%type uses_section {std::list<std::string> *}
uses_section(u) ::= USES uses_list(u_l) SEMICOLON .
    { u = u_l; }
uses_section(u) ::= .
    { u = new std::list<std::string>; }

%type uses_list {std::list<std::string> *}
uses_list(u) ::= IDENTIFIER(n) .
    {
    u = new std::list<std::string>;
    u->push_back( ustr2str(n->get_text()) );
    }
uses_list(u_bigger) ::= uses_list(u_orig) COMMA IDENTIFIER(n) .
    {
    u_bigger = u_orig;
    u_bigger->push_back( ustr2str(n->get_text()) );
    }

/* require all label declarations to come first */
%type block {BlockNode *}
%type block1 {BlockNode *}
%type block2 {BlockNode *}
%type block3 {BlockNode *}
%type block4 {BlockNode *}
%type block5 {BlockNode *}

block(b) ::= block1(b1).
    { b = b1; }
block(b) ::= label_declaration(l_d) SEMICOLON block1(b1) .
    {
    b = b1;
    // handle the label declarations
    b->add_labels( l_d );
    }

/* then all constant declarations */
block1(b1) ::= block2(b2).
    { b1 = b2; }
block1(b1) ::= constant_declaration(c_d) SEMICOLON block2(b2) .
    {
    b1 = b2;
    // handle the constant declarations
    b1->add_constants( c_d );
    }

/* followed by any type declarations */
block2(b2) ::= block3(b3).
    { b2 = b3; }
block2(b2) ::= type_declaration(t_d) SEMICOLON block3(b3) .
    {
    b2 = b3;
    // handle the type declarations
    b2->add_types( t_d );
    }

/* then any global variable declarations */
block3(b3) ::= block4(b4).
    { b3 = b4; }
block3(b3) ::= variable_declaration(v_d) SEMICOLON block4(b4) .
    {
    b3 = b4;
    // handle the variable declarations
    b3->add_variables( v_d );
    }

/* then any forward procedure and function declarations */
block4(b4) ::= block5(b5).
    { b4 = b5; }
block4(b4) ::= proc_and_func_declaration(pfd) SEMICOLON block5(b5).
    {
    b4 = b5;
    // handle the procedure and function declarations
    b4->add_subroutines( pfd );
    }

/* then the program statements */
block5(b5) ::= BEGIN statement_list(s_l) END.
    {
    b5 = new BlockNode(s_l);
    }

%type label_declaration {std::list<int> *}
label_declaration(l_d) ::= LABEL label_list(l_l).
    { l_d = l_l; }

%type label_list {std::list<int> *}
label_list(lst) ::= label(lbl).
    { lst = new std::list<int>; lst->push_back(lbl); }
label_list(lst_big) ::= label_list(lst_orig) COMMA label(lbl).
    { lst_big = lst_orig; lst_big->push_back(lbl); }

%type constant_declaration {std::map<std::string, ExpressionNode *> *}
constant_declaration(cd) ::= CONST IDENTIFIER(n) EQUALS constant(c).
    {
    cd = new std::map<std::string, ExpressionNode *>;
    cd->insert( std::pair<std::string, ExpressionNode *>(ustr2str(n->get_text()), c) );
    }
constant_declaration(cdb) ::= constant_declaration(cdo) SEMICOLON IDENTIFIER(n) EQUALS constant(c).
    {
    cdb = cdo;
    cdb->insert( std::pair<std::string, ExpressionNode *>(ustr2str(n->get_text()), c) );
    }

%type type_declaration {std::map<std::string, TypeNode *> *}
type_declaration(t_d) ::= TYPE IDENTIFIER(n) EQUALS type(t).
    {
    t_d = new std::map<std::string, TypeNode *>;
    t_d->insert( std::pair<std::string,TypeNode* >(ustr2str(n->get_text()), t) );
    }

type_declaration(t_d_bigger) ::= type_declaration(t_d_orig) SEMICOLON IDENTIFIER(n) EQUALS type(t).
    {
    t_d_bigger = t_d_orig;
    t_d_bigger->insert( std::pair<std::string,TypeNode* >(ustr2str(n->get_text()), t) );
    }

%type variable_declaration {std::map<std::string, TypeNode *> *}
variable_declaration(v_d) ::= VAR variableid_list(v_l) COLON type(t).
    {
    /* this is the bottom of the recursion, so need to create the new empty variable->type
        mapping */
    v_d = new std::map<std::string, TypeNode *>;

    /* given the grammar, we know that v_l will not be empty at this point */
    /* now add an entry for each variable name associating it with the specified type
        in the var->type mapping (which will eventually be used as part of the environment
        and for type-checking) */
    for( std::list<std::string>::const_iterator it = v_l->begin();
        it != v_l->end();
        ++it )
        {
        v_d->insert( std::pair<std::string,TypeNode* >(*it, t) );
        }
    }
variable_declaration(v_d_bigger) ::= variable_declaration(v_d_orig) SEMICOLON variableid_list(v_l) COLON type(t).
    {
    /* v_d_orig was already created, so we're just going to extend that existing mapping with
        additional var->type pairs */
    v_d_bigger = v_d_orig;

    /* add an entry for each variable name associating it with the specified type
        in the var->type mapping (which will eventually be used as part of the environment
        and for type-checking) */
    for( std::list<std::string>::const_iterator it = v_l->begin();
        it != v_l->end();
        ++it )
        {
        v_d_bigger->insert( std::pair<std::string,TypeNode* >(*it, t) );
        }
    }

%type variableid_list {std::list<std::string> *}
variableid_list(v_l) ::= IDENTIFIER(n).
    {
    v_l = new std::list<std::string>;
    v_l->push_back( ustr2str(n->get_text()) );
    }

variableid_list(v_l_bigger) ::= variableid_list(v_l_orig) COMMA IDENTIFIER(n).
    {
    v_l_bigger = v_l_orig;
    v_l_bigger->push_back( ustr2str(n->get_text()) );
    }

%type constant {ExpressionNode *}
constant(c) ::= NUMBER(num).
    {
    const char *tmp_signed = reinterpret_cast<const char *>(num->get_text().c_str());
    c = new NumberExpressionNode( atoi(tmp_signed) );
    }
/* not supported yet. constant ::= REAL */
constant(c) ::= STRING(s).
    { c = new StringExpressionNode( ustr2str(s->get_text()) ); }
constant ::= constid.
constant ::= PLUS constid.
constant ::= MINUS constid.


%type type {TypeNode *}
type(t) ::= simple_type(s).
    { t = s; }
type(t) ::= structured_type(s).
    { t = s; }
//type ::= POINTS_TO typeid. // want to point to more complicated types than just named ones
type(t) ::= POINTS_TO simple_type(s).
    { t = new TypeNode("POINTS_TO", s); }
type(t) ::= POINTS_TO structured_type(s).
    { t = new TypeNode("POINTS_TO", s); }

%type simple_type {TypeNode *}
simple_type(s) ::= LPAREN identifier_list(i_l) RPAREN.
    { s = new SetTypeNode( *i_l ); }
//simple_type ::= constant DOTDOT constant.
simple_type(s) ::= typeid(t).
    { s = new TypeNode(t); free(t); }
simple_type(s) ::= TYPE_INTEGER.
    { s = &IntegerType; }
simple_type(s) ::= TYPE_STRING.
    { s = &StringType; }
simple_type(s) ::= TYPE_BOOLEAN.
    { s = &BooleanType; }
simple_type(s) ::= TYPE_CHAR.
    { s = &CharType; }

%type structured_type {TypeNode *}
structured_type(lhs) ::= ARRAY LBRACKET index_list(il) RBRACKET OF type(rhs).
    { lhs = new ArrayTypeNode(il, rhs); }
structured_type(lhs) ::= RECORD field_list(fl) END.
    { lhs = new RecordTypeNode( fl ); }
structured_type(lhs) ::= SET OF simple_type(rhs).
    { lhs = new SetTypeNode( rhs ); }
structured_type(lhs) ::= FILE OF type(rhs).
    { lhs = new TypeNode("FILE", rhs); }
structured_type(lhs) ::= PACKED structured_type(rhs).
    { lhs = new TypeNode("PACKED", rhs); }

%type index_list {std::list<int> *}
index_list(i_l) ::= NUMBER(num).
    {
    i_l = new std::list<int>;

    const char *tmp_signed = reinterpret_cast<const char *>(num->get_text().c_str());
    i_l->push_back( atoi(tmp_signed) );
    }
index_list(ilb) ::= index_list(ilo) COMMA NUMBER(num).
    {
    ilb = ilo;

    const char *tmp_signed = reinterpret_cast<const char *>(num->get_text().c_str());
    ilb->push_back( atoi(tmp_signed) );
    }


%type field_list {std::map<std::string, TypeNode *> *}
field_list(fl) ::= fixed_part(fp).
    {
    if( fp )
        fl = fp;
    else
        {
        printf( "\nERROR: record definition cannot be empty\n" );
        }
    }
field_list(fl) ::= fixed_part(fp) SEMICOLON variant_part.
    { fl = fp; }
field_list ::= variant_part.


%type fixed_part {std::map<std::string, TypeNode *> *}
fixed_part(fp) ::= record_field(rf).
    { fp = rf; }
fixed_part(fpb) ::= fixed_part(fpo) SEMICOLON record_field(rf).
    {
    assert( fpo != NULL );

    fpb = fpo;
    if( rf != NULL ) // don't add final empty groups to the mapping
        {
        // add each element in the additional record field to the existing fixed part
        for(std::map<std::string, TypeNode *>::const_iterator it = rf->begin();
            it != rf->end();
            ++it)
            {
            if( fpo->count(it->first) )
                {
                printf("\nERROR: duplicate field name (%s) in record\n", it->first.c_str() );
                }
            else
                fpb->insert( *it );
            }
        }
    }

%type record_field {std::map<std::string, TypeNode *> *}
record_field(rf) ::= fieldid_list(fields) COLON type(t).
    {
    rf = new std::map<std::string, TypeNode *>;

    for( std::list<std::string>::const_iterator it = fields->begin();
        it != fields->end();
        ++it )
        {
        rf->insert( std::pair<std::string,TypeNode* >(*it, t) );
        }
    }
record_field(rf) ::= .
    { rf = NULL; }

%type fieldid_list {std::list<std::string> *}
fieldid_list(fl) ::= IDENTIFIER(n).
    {
    fl = new std::list<std::string>;
    fl->push_back( ustr2str(n->get_text()) );
    }
fieldid_list(flb) ::= fieldid_list(flo) COMMA IDENTIFIER(n).
    {
    flb = flo;
    flb->push_back( ustr2str(n->get_text()) );
    }

variant_part ::= CASE tag_field OF variant_list.


tag_field ::= typeid.
tag_field ::= IDENTIFIER COLON typeid.

variant_list ::= variant.
variant_list ::= variant_list SEMICOLON variant.

variant ::= case_label_list COLON LPAREN field_list RPAREN.
variant ::= .

case_label_list ::= constant.
case_label_list ::= case_label_list COMMA constant.


%type proc_and_func_declaration {std::list<SubroutineNode *> *}
proc_and_func_declaration(pfd) ::= proc_or_func(pf).
    {
    assert( pf != NULL );
    pfd = new std::list<SubroutineNode *>;
    pfd->push_back( pf );
    }
proc_and_func_declaration(pfdb) ::= proc_and_func_declaration(pfdo) SEMICOLON proc_or_func(pf).
    {
    assert( pfdo != NULL );
    assert( pf != NULL );
    pfdb = pfdo;
    pfdb->push_back( pf );
    }

%type proc_or_func {SubroutineNode *}
proc_or_func(pf) ::= PROCEDURE IDENTIFIER(name) parameters(params) SEMICOLON  block_or_forward(body).
    { pf = new SubroutineNode( ustr2str(name->get_text()), params, body, NULL ); }
proc_or_func(pf) ::= PROCEDURE IDENTIFIER(name) SEMICOLON  block_or_forward(body).
    { pf = new SubroutineNode( ustr2str(name->get_text()), NULL, body, NULL ); }
proc_or_func(pf) ::= FUNCTION IDENTIFIER(name) parameters(params) COLON type(rt) SEMICOLON block_or_forward(body).
    {
    //printf( "\nDBUG(pascal.y): new func defn from id@%p = %s", (name), name->get_text().c_str() );
    pf = new SubroutineNode( ustr2str(name->get_text()), params, body, rt );
    }
proc_or_func(pf) ::= FUNCTION IDENTIFIER(name) COLON type(rt) SEMICOLON block_or_forward(body).
    { pf = new SubroutineNode( ustr2str(name->get_text()), NULL, body, rt ); }

%type block_or_forward {BlockNode *}
block_or_forward(bf) ::= block(b).          { bf = b; }
block_or_forward(bf) ::= FORWARD SEMICOLON. { bf = NULL; }

%type parameters {std::map<std::string, TypeNode *> *}
parameters(p) ::= LPAREN formal_parameter_list(fpl) RPAREN. { p = fpl; }


%type formal_parameter_list {std::map<std::string, TypeNode *> *}
formal_parameter_list(fpl) ::= formal_parameter_section(fps).
    { fpl = fps; }
formal_parameter_list(fplb) ::= formal_parameter_list(fplo) SEMICOLON formal_parameter_section(fps).
    {
    fplb = fplo;

    for( std::map<std::string, TypeNode *>::const_iterator it = fps->begin();
        it != fps->end();
        ++it )
        {
        fplb->insert( *it );
        }
    }

%type formal_parameter_section {std::map<std::string, TypeNode *> *}
formal_parameter_section(fps) ::= parameterid_list(pl) COLON type(t).
    {
    /* this is the bottom of the recursion, so need to create the new empty param->type
        mapping */
    fps = new std::map<std::string, TypeNode *>;

    /* given the grammar, we know that v_l will not be empty at this point */
    /* now add an entry for each variable name associating it with the specified type
        in the var->type mapping (which will eventually be used as part of the environment
        and for type-checking) */
    for( std::list<std::string>::const_iterator it = pl->begin();
        it != pl->end();
        ++it )
        {
        fps->insert( std::pair<std::string,TypeNode* >(*it, t) );
        }
    }
formal_parameter_section ::= VAR parameterid_list COLON type.
    { assert( false ); }
formal_parameter_section ::= PROCEDURE IDENTIFIER parameters.
    { assert( false ); }
formal_parameter_section ::= PROCEDURE IDENTIFIER.
    { assert( false ); }
formal_parameter_section ::= FUNCTION IDENTIFIER parameters COLON type.
    { assert( false ); }
formal_parameter_section ::= FUNCTION IDENTIFIER COLON type.
    { assert( false ); }

%type parameterid_list {std::list<std::string> *}
parameterid_list(pl) ::= IDENTIFIER(n).
    {
    assert( n != NULL );
    pl = new std::list<std::string>;
    pl->push_back( ustr2str(n->get_text()) );
    }
parameterid_list(plb) ::= parameterid_list(plo) COMMA IDENTIFIER(n).
    {
    assert( n != NULL );
    assert( plo != NULL );
    plb = plo;
    plb->push_back( ustr2str(n->get_text()) );
    }

%type statement_list {std::list<StatementNode *> *}
statement_list(s_l) ::= statement(s).
    {
    s_l = new std::list<StatementNode *>;
    if( s ) // if the statement list is empty, don't push a NULL entry
        s_l->push_back( s );
    }
statement_list(s_l_bigger) ::= statement_list(s_l_orig) SEMICOLON statement(s).
    {
    s_l_bigger = s_l_orig;
    if( s ) // don't add the final "empty" statement to the list
        s_l_bigger->push_back(s);
    }

%type statement {StatementNode *}
statement(s) ::= variable(v) ASSIGNMENT expression(e).
    {
    assert( v != NULL );
    assert( e != NULL );
    s = new AssignmentNode(v,e);
    }
statement(s) ::= BEGIN statement_list(s_l) END.
    { s = new BlockStatementNode(s_l); }
//statement ::= IF expression THEN statement ELSE statement.
statement(s) ::= IF expression(test) THEN statement(body).
    { s = new IfThenNode(test,body); }
statement ::= CASE expression OF case_list END.
statement(s) ::= WHILE expression(test) DO statement(body).
    { s = new WhileLoopNode(test,body); }
statement(s) ::= REPEAT statement(body) UNTIL expression(test).
    { s = new RepeatLoopNode(body,test); }
statement(s) ::= FOR varid(i) ASSIGNMENT for_list(range) DO statement(body).
    {
    assert( i != NULL );
    assert( range != NULL );
    assert( body != NULL );
    s = new ForLoopNode( i, range, body );
    }
statement(s) ::= procid(i).
    { assert(i != NULL); s = new ProcedureCallNode(i); }
statement(s) ::= procid(i) LPAREN expression_list(args) RPAREN.
    { assert( i != NULL ); s = new ProcedureCallNode( i, args ); }
statement(s) ::= GOTO label(lbl).
    { s = new GotoNode(lbl); }
statement(s) ::= WITH record_variable_list(rvl) DO statement(body).
    { s = new WithNode( rvl, body ); }
statement(s) ::= label(l) COLON statement(rhs).
    { s = new LabeledStatementNode(l, rhs); }
statement(s) ::= .
    { s = NULL; }

%type variable {VariableNode *}
variable(v) ::= varid(i).
    {
    assert( i != NULL );
    v = new VariableNode(i);
    
    //printf( "\nDBUG(pascal.y): new variable(@%p) from varid(@%p)=%s", v, i, i );
    free(i);
    }
variable(v) ::= variable(i) LBRACKET subscript_list(sl) RBRACKET.
    {
    assert( i != NULL );
    assert( sl != NULL );
    v = new VariableNode(i, sl);
    }
variable(v) ::= variable(i) PERIOD fieldid(f).
    {
    assert( i != NULL );
    assert( f != NULL );
    v = new VariableNode(i, f);
    }
variable(v) ::= variable(i) POINTS_TO.
    {
    assert( i != NULL );
    v = new VariableNode( i, true );
    }
//variable ::= ADDRESS_OF variable. // this is implemented as a unary expression instead

%type subscript_list {std::list<ExpressionNode *> *}
subscript_list(s_l) ::= expression(e).
    { s_l = new std::list<ExpressionNode *>; s_l->push_back(e); }
subscript_list(slb) ::= subscript_list(slo) COMMA expression(e).
    { assert( slo != NULL ); slb = slo; slb->push_back(e); }

case_list ::= case_label_list COLON statement.
case_list ::= case_list SEMICOLON case_label_list COLON statement.

%type for_list {ForRange *}
for_list(fl) ::= expression(begin) TO expression(end).
    {
    assert( begin != NULL );
    assert( end != NULL );
    fl = new ForRange( begin, end, true );
    }
for_list(fl) ::= expression(begin) DOWNTO expression(end).
    {
    assert( begin != NULL );
    assert( end != NULL );
    fl = new ForRange( begin, end, false );
    }

%type expression_list {std::list<ExpressionNode *> *}
expression_list(e_l) ::= expression(e).
    { e_l = new std::list<ExpressionNode *>; e_l->push_back(e); }
expression_list(e_l_big) ::= expression_list(e_l_orig) COMMA expression(e).
    { assert( e_l_orig != NULL ); e_l_big = e_l_orig; e_l_big->push_back(e); }

%type label {int}
label(lbl) ::= NUMBER(num).
    {
    const char *tmp_signed = reinterpret_cast<const char *>(num->get_text().c_str());
    lbl = atoi(tmp_signed);
    }

%type record_variable_list {std::list<VariableNode *> *}
record_variable_list(rvl) ::= variable(v).
    {
    rvl = new std::list<VariableNode *>;
    rvl->push_back( v );
    }
record_variable_list(rvl_b) ::= record_variable_list(rvl_o) COMMA variable(v).
    {
    assert( rvl_o != NULL );
    rvl_b = rvl_o;
    rvl_b->push_back( v );
    }

%type expression {ExpressionNode *}
expression(e) ::= expression(lhs) relational_op(op) additive_expression(rhs).
    {
    e = new BinaryExpressionNode( lhs, op, rhs );
    }
expression(e) ::= additive_expression(a_e). { assert(a_e != NULL); e = a_e; }

%type relational_op {BinaryOperator}
relational_op(op) ::= LESS_THAN.     {op = BINOP_LESS_THAN;}
relational_op(op) ::= LESS_EQUAL.    {op = BINOP_LESS_EQUAL;}
relational_op(op) ::= EQUALS.        {op = BINOP_EQUAL;}
relational_op(op) ::= NOTEQUAL.      {op = BINOP_NOTEQUAL;}
relational_op(op) ::= GREATER_EQUAL. {op = BINOP_GREATER_EQUAL;}
relational_op(op) ::= GREATER_THAN.  {op = BINOP_GREATER_THAN;}

%type additive_expression {ExpressionNode *}
additive_expression(a_e) ::= additive_expression(lhs) additive_op(op) multiplicative_expression(rhs).
    {
    assert( lhs != NULL );
    assert( rhs != NULL );
    a_e = new BinaryExpressionNode( lhs, op, rhs );
    }
additive_expression(a_e) ::= multiplicative_expression(m_e). { assert(m_e != NULL); a_e = m_e; }

%type additive_op {BinaryOperator}
additive_op(op) ::= PLUS.  { op = BINOP_PLUS; }
additive_op(op) ::= MINUS. { op = BINOP_MINUS; }
additive_op(op) ::= OR.    { op = BINOP_OR; }

%type multiplicative_expression {ExpressionNode *}
multiplicative_expression(m_e) ::= multiplicative_expression(lhs) multiplicative_op(op) unary_expression(rhs).
    {
    assert( lhs != NULL );
    assert( rhs != NULL );
    m_e = new BinaryExpressionNode( lhs, op, rhs );
    }
multiplicative_expression(m_e) ::= unary_expression(u_e). { m_e = u_e; }

%type multiplicative_op {BinaryOperator}
multiplicative_op(op) ::= STAR.  { op = BINOP_MULTIPLY; }
multiplicative_op(op) ::= SLASH. { op = BINOP_REAL_DIVIDE; }
multiplicative_op(op) ::= DIV.   { op = BINOP_INTEGER_DIVIDE; }
multiplicative_op(op) ::= MOD.   { op = BINOP_MOD; }
multiplicative_op(op) ::= AND.   { op = BINOP_AND; }
multiplicative_op(op) ::= IN.    { op = BINOP_IN; }

%type unary_expression {ExpressionNode *}
unary_expression(u_e) ::= unary_op(op) unary_expression(rhs).
    {
    u_e = new UnaryExpressionNode( op, rhs );
    }
unary_expression(u_e) ::= ADDRESS_OF variable(v).
    { /* this one is split out to enforce rhs to be a variable */
    u_e = new UnaryExpressionNode( UNOP_ADDRESS_OF, v );
    }
unary_expression(u_e) ::= primary_expression(p_e). { u_e = p_e; }

%type unary_op {UnaryOperator}
unary_op(op) ::= PLUS.  { op = UNOP_PLUS; }
unary_op(op) ::= MINUS. { op = UNOP_MINUS; }
unary_op(op) ::= NOT.   { op = UNOP_NOT; }

%type primary_expression {ExpressionNode *}
primary_expression(p_e) ::= variable(v).
    { assert(v != NULL); p_e = v; }
primary_expression(p_e) ::= BOOLEAN(b).
    { p_e = new BooleanExpressionNode( b->get_text().c_str() ); }
primary_expression(p_e) ::= NUMBER(n).
    {
    unsigned char *tmp_unsigned = const_cast<unsigned char *>( n->get_text().c_str() );
    char *tmp_signed = reinterpret_cast<char *>(tmp_unsigned);

    p_e = new NumberExpressionNode( tmp_signed );
    }
/* not yet implemented primary_expression ::= REAL. */
primary_expression(p_e) ::= STRING(s).
    {
    // this complicated expression removes the first and last characters of the string (the quotes)
    // and removes the const-ness from the returned pointer.
    unsigned char *tmp_unsigned = const_cast<unsigned char *>( s->get_text().substr(1,s->get_text().length() - 2).c_str() );

    // now we remove the unsigned-ness from the returned pointer, since apparently you
    // can't get a free cast from string<unsigned char> to string<char>.
    // i.e. you can't build std::string(tmp_unsigned) because it defaults to std::string<char>
    char *tmp_signed = reinterpret_cast<char *>(tmp_unsigned);

    // make sure nothing bizarre happened during all that casting and chopping
    assert( tmp_signed != NULL );

    p_e = new StringExpressionNode( std::string(tmp_signed) );
    }
primary_expression(p_e) ::= NIL.
    { p_e = new NumberExpressionNode( 0 ); }
primary_expression(p_e) ::= funcid(f) LPAREN expression_list(args) RPAREN.
    {
    assert( f != NULL );
    assert( args != NULL );
    p_e = new FunctionCallNode(f, args);
    free(f);
    }
primary_expression(p_e) ::= LBRACKET element_list(e_l) RBRACKET.
    {
    assert( e_l != NULL );
    p_e = new ArrayIndexNode(e_l);
    }
primary_expression(p_e) ::= LPAREN expression(e) RPAREN.
    {
    assert( e != NULL );
    p_e = e;
    }

%type element_list {std::list<ExpressionNode *> *}
element_list(e_l) ::= element(e). { e_l = new std::list<ExpressionNode *>; e_l->push_back(e); }
element_list(e_l_b) ::= element_list(e_l_o) COMMA element(e).
    {
    assert( e_l_o != NULL );
    e_l_b = e_l_o;
    e_l_b->push_back(e);
    }
//element_list ::= .

%type element {ExpressionNode *}
element(elem) ::= expression(expr). { elem = expr; }
element ::= expression DOTDOT expression.

%type constid {char *}
constid(I) ::= IDENTIFIER(n) .
    {
    unsigned char *tmp_unsigned = const_cast<unsigned char *>( n->get_text().c_str() );
    char *tmp_signed = reinterpret_cast<char *>(tmp_unsigned);

    I = strdup(tmp_signed);
    }

%type typeid {char *}
typeid(I) ::= IDENTIFIER(n) .
    {
    unsigned char *tmp_unsigned = const_cast<unsigned char *>( n->get_text().c_str() );
    char *tmp_signed = reinterpret_cast<char *>(tmp_unsigned);

    I = strdup(tmp_signed);
    }

%type funcid {char *}
funcid(I) ::= IDENTIFIER(n) .
    {
    unsigned char *tmp_unsigned = const_cast<unsigned char *>( n->get_text().c_str() );
    char *tmp_signed = reinterpret_cast<char *>(tmp_unsigned);

    I = strdup(tmp_signed);
    //printf( "\nDBUG(pascal.y): new funcid(@%p)=%s", I, tmp_signed );
    }

%type procid {char *}
procid(I) ::= IDENTIFIER(n) .
    {
    unsigned char *tmp_unsigned = const_cast<unsigned char *>( n->get_text().c_str() );
    char *tmp_signed = reinterpret_cast<char *>(tmp_unsigned);

    I = strdup(tmp_signed);
    //printf( "\nDBUG(pascal.y): new procid(@%p)=%s", I, tmp_signed );
    }

%type fieldid {char *}
fieldid(I) ::= IDENTIFIER(n) .
    {
    unsigned char *tmp_unsigned = const_cast<unsigned char *>( n->get_text().c_str() );
    char *tmp_signed = reinterpret_cast<char *>(tmp_unsigned);

    I = strdup(tmp_signed);
    }

%type varid {char *}
varid(I) ::= IDENTIFIER(n) .
    {
    unsigned char *tmp_unsigned = const_cast<unsigned char *>( n->get_text().c_str() );
    char *tmp_signed = reinterpret_cast<char *>(tmp_unsigned);

    I = strdup(tmp_signed);
    //printf( "\nDBUG(pascal.y): new varid(@%p)=%s", I, tmp_signed );
    }
