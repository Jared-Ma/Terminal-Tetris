#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[argc+1]) {
    printf("argc: %i\n", argc);
    printf("argv: [ ");
    for (size_t i = 0; i < argc; ++i) {
        printf("%s ", argv[i]);
    }
    printf("]\n");
    
    return EXIT_SUCCESS;
}
