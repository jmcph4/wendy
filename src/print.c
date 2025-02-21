#include <stdio.h>

#include "ast.h"
#include "print.h"

const char* type2str(enum type type) {
    switch (type) {
        case VOID:
            return "void";
            break;
        case INT:
            return "int";
            break;
        case BOOL:
            return "bool";
            break;
        case STRING:
            return "string";
            break;
    }

    return "";
}

void print_var(struct var* v, unsigned int indent) {
    if (v == NULL) return;
    for (size_t i=0;i<indent;i++) printf("    ");
    printf("%s %s;\n", type2str(v->type), v->name);
}

void print_func(struct func* f, unsigned int indent) {
    if (f == NULL) return;

    for (unsigned int i=0;i<indent;i++) printf("    ");
    printf("fun %s(", f->name);
    for (size_t i=0;i<f->arglen;i++) {
        if (i + 1 == f->arglen) { 
            printf("%s: %s", f->args[i].name, type2str(f->args[i].type));
        } else {
            printf("%s: %s, ", f->args[i].name, type2str(f->args[i].type));
        }
    }
    printf(") : %s {\n", type2str(f->ret));

    for (size_t i=0;i<f->funclen;i++) print_func(&f->funcs[i], indent + 1);
    for (size_t i=0;i<f->varlen;i++) print_var(&f->vars[i], indent + 1);

    for (unsigned int i=0;i<indent;i++) printf("    ");
    printf("}\n");
}
