#ifndef CODEGEN_H_
#define CODEGEN_H_

#include "ast.h"

char* gen_func(char* code, struct func* func);
char* gen_expr(char* code, struct expr* expr);
char* gen_stmt(char* code, struct stmt* stmt);

#endif /* CODEGEN_H_ */

