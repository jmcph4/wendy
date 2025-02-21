#ifndef AST_H_
#define AST_H_

#include <stdbool.h>
#include <stdint.h>

enum type { VOID, INT, BOOL, STRING };

struct arg { char* name; enum type type; };
struct var { char* name; enum type type; };

struct expr_arith_op { char op; union expr* lhs; union expr* rhs; };
struct expr_logic_op { char op; union expr* lhs; union expr* rhs; };
struct expr_int { uint64_t val; };
struct expr_bool { bool val; };
struct expr_string { char* val; };
struct expr_var { char* name; enum type type; };
struct expr_call { char* name; struct arg* args; };

union expr {
    struct expr_arith_op arith_op;
    struct expr_logic_op logic_op;
    struct expr_int integer;
    struct expr_bool boolean;
    struct expr_string string;
    struct expr_var var;
    struct expr_call call;
};

struct stmt_print { union expr expr; };
struct stmt_ret { union expr expr; };
struct stmt_assign { char* name; union expr expr; };
struct stmt_while { union expr expr; union stmt* body; };
struct stmt_ite {
    union expr expr;
    union stmt* if_body;
    union stmt* else_body;
};

union stmt {
    struct stmt_print print;
    struct stmt_ret ret;
    struct stmt_assign assign;
    struct stmt_while swhile;
    struct stmt_ite ite;
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
    union stmt* body;
    enum type ret;
};

#endif /* AST_H_ */ 

