#include <tools.h>

#include <string.h>

char __tools_getDriveLetter(int id) {
    const char letters[] = {
        'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p', 'q', 'r',
        's', 't', 'u', 'v', 'w', 'x',
        'y', 'z', 0
    };

    size_t len = strlen(letters);

    size_t index = (size_t)id % len;

    return letters[index];
}
