#ifndef PRINT_H_
#define PRINT_H_

#include "ast.h"

const char* type2str(enum type type);
void print_func(struct func* f, unsigned int indent);
void print_var(struct var* v, unsigned int indent);

#endif /* PRINT_H_ */

