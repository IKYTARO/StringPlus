#include "my_string.h"

char *my_strerror(int errnum) {
    static char unknown_error[64];
    char *result = MY_NULL;

    if (errnum >= 0 && errnum < ERRLIST_SIZE) {
        static const char *error_messages[] = ERROR_LIST;
        result = (char *)error_messages[errnum];
    } else {
        my_sprintf(unknown_error, "Unknown error %d", errnum);
        result = unknown_error;
    }

    return result;
}