#include "stdio.h"

#include "validator.c"

//im using main mostly for temporary parsing tests at this point, like so:
//im just gonna commit a bunch of checkpoints dont mind me
int main(int argc, char** argv) {
    frontend fe = make_frontend("test.c+");

    lex(&fe);
    parse(&fe);
    validate(&fe);
    print_block(&fe.global);

    return 0;
}