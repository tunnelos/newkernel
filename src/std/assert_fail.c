#include <assert_fail.h>
#include <terminal80x25.h>
#include <stdio.h>

void __assert_fail(
    const char *__assertion, 
    const char *__file, 
    unsigned int __line, 
    const char *__function
) {
    // __terminal_clear();
    // __terminal_reset();

    //printf("\n%s:%d: %s: Assertion '%s' failed.\n", __file, __line, __function, __assertion);
    printf("\n%s:", __file);
    printf("%d: ", __line);
    printf("%s(): ", __function);
    printf("Assertion '%s' failed.\n", __assertion);

    while(true) {
        ;;
    }
}