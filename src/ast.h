#ifndef AST_H_
#define AST_H_

#include <stdbool.h>
#include <stdint.h>

enum type { VOID, INT, BOOL, STRING };

struct arg { char* name; enum type type; };
struct var { char* name; enum type type; };

struct expr_arith_op { char op; struct expr* lhs; struct expr* rhs; };
struct expr_logic_op { char op; struct expr* lhs; struct expr* rhs; };
struct expr_int { uint64_t val; };
struct expr_bool { bool val; };
struct expr_string { char* val; };
struct expr_var { char* name; enum type type; };
struct expr_call { char* name; struct arg* args; };

struct expr {
    enum { 
        EXPR_ARITH_OP,
        EXPR_LOGIC_OP,
        EXPR_INTEGER,
        EXPR_STRING,
        EXPR_VARIABLE,
        EXPR_CALL
    } type;
    union {
        struct expr_arith_op arith_op;
        struct expr_logic_op logic_op;
        struct expr_int integer;
        struct expr_bool boolean;
        struct expr_string string;
        struct expr_var var;
        struct expr_call call;
    } data;
};

struct stmt_print { struct expr expr; };
struct stmt_ret { struct expr expr; };
struct stmt_assign { char* name; struct expr expr; };
struct stmt_while { struct expr expr; struct stmt* body; };
struct stmt_ite {
    struct expr expr;
    struct stmt* if_body;
    struct stmt* else_body;
};

struct stmt {
    enum {
        STMT_PRINT,
        STMT_RET,
        STMT_ASSIGN,
        STMT_WHILE,
        STMT_ITE,
    } type;
    union {
        struct stmt_print print;
        struct stmt_ret ret;
        struct stmt_assign assign;
        struct stmt_while swhile;
        struct stmt_ite ite;
    } data;
};

struct func {
    char* name;
    size_t arglen;
    struct arg* args;
    size_t varlen;
    struct var* vars;
    size_t funclen;
    struct func* funcs;
    size_t bodylen;
    struct stmt* body;
    enum type ret;
};

#endif /* AST_H_ */ 

