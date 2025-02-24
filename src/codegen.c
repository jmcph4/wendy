#define _GNU_SOURCE /* asprintf */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "codegen.h"

const char* op2py(char* op) {
    if (op == NULL) return NULL;
    if (strncmp(op, "/", strlen(op)) == 0) return "//";
    if (strncmp(op, "||", strlen(op)) == 0) return "or";
    if (strncmp(op, "&&", strlen(op)) == 0) return "and";
    return op;
}

char* gen_expr(char* code, struct expr* expr) {
    if (expr == NULL) return NULL;

    switch (expr->type) {
        case EXPR_ARITH_OP:
            asprintf(
                &code,
                "(%s %s %s)",
                gen_expr(code, ((struct expr_arith_op*)expr)->lhs),
                op2py(((struct expr_arith_op*)expr)->op),
                gen_expr(code, ((struct expr_arith_op*)expr)->rhs)
            );
            return code;
        case EXPR_LOGIC_OP:
            asprintf(
                &code,
                "(%s %s %s)",
                gen_expr(code, ((struct expr_arith_op*)expr)->lhs),
                op2py(((struct expr_arith_op*)expr)->op),
                gen_expr(code, ((struct expr_arith_op*)expr)->rhs)
            );
            return code;
        case EXPR_INTEGER:
            asprintf(&code, "%ld", ((struct expr_int*)expr)->val);
            return code;
        case EXPR_STRING:
            asprintf(&code, "%s", ((struct expr_string*)expr)->val);
            return code;
        case EXPR_BOOLEAN:
            if (((struct expr_bool*)expr)->val) {
                asprintf(&code, "True");
            } else {
                asprintf(&code, "False");
            }
            return code;
        case EXPR_VARIABLE:
            asprintf(&code, "%s", ((struct expr_var*)expr)->name);
            return code;
        case EXPR_CALL:
            asprintf(&code, "%s()", ((struct expr_call*)expr)->name);
            return code;
    }
}

char* gen_stmt(char* code, struct stmt* stmt) {
    if (stmt == NULL) return NULL;

    switch (stmt->type) {
        case STMT_PRINT:
            asprintf(
                &code,
                "print(%s)\n",
                gen_expr(code, &((struct stmt_print*)stmt)->expr)
            );
            return code;
        case STMT_RET:
            asprintf(
                &code,
                "return (%s)\n",
                gen_expr(code, &((struct stmt_ret*)stmt)->expr)
            );
            return code;
        case STMT_ASSIGN:
            asprintf(
                &code,
                "%s = %s\n",
                ((struct stmt_assign*)stmt)->name,
                gen_expr(code, &((struct stmt_assign*)stmt)->expr)
            );
            return code;
        case STMT_WHILE:
            asprintf(
                &code,
                "while (%s):\n    %s\n",
                gen_expr(code, &((struct stmt_while*)stmt)->expr),
                gen_stmt(code, ((struct stmt_while*)stmt)->body)
            );
            return code;
        case STMT_ITE:
            asprintf(
                &code,
                "if (%s):\n    %s\nelse:\n    %s",
                gen_expr(code, &((struct stmt_ite*)stmt)->expr),
                gen_stmt(code, ((struct stmt_ite*)stmt)->if_body),
                gen_stmt(code, ((struct stmt_ite*)stmt)->else_body)
            );
            return code;
    }
}

char* gen_func(char* code, struct func* func) {
    if (func == NULL) return NULL;
    asprintf(&code, "def %s(", func->name);

    for(size_t i=0;i<func->arglen;i++) {
        if (i + 1 == func->arglen) {
            asprintf(&code, "%s", func->args[i].name);
        } else {
            asprintf(&code, "%s, ", func->args[i].name);
        }
    }

    asprintf(&code, "):\n");
    return code;
}

