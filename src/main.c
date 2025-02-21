#include <stdlib.h>

#include "ast.h"
#include "print.h"

int main(void) {
    struct arg x_arg = { .name = "x", .type = INT };
    struct var some_var = { .name = "tmp", .type = STRING };
    struct func foo = {
        .name = "example_function",
        .arglen = 1,
        .args = &x_arg,
        .varlen = 1,
        .vars = &some_var,
        .funclen = 0,
        .funcs = NULL,
        .bodylen = 0,
        .body = NULL,
        .ret = INT,
    };

    print_func(&foo, 0);

    return EXIT_SUCCESS;
}

