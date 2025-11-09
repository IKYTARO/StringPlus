#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_strerror_basic) {
    int test_errors[] = {
        0,        // Success
        EPERM,    // Operation not permitted
        ENOENT,   // No such file or directory
        ESRCH,    // No such process
        EINTR,    // Interrupted system call
        EIO,      // Input/output error
        E2BIG,    // Argument list too long
        ENOEXEC,  // Exec format error
        EBADF,    // Bad file descriptor
        ECHILD,   // No child processes
        EAGAIN,   // Resource temporarily unavailable
        ENOMEM,   // Cannot allocate memory
        EACCES,   // Permission denied
        EFAULT,   // Bad address
        ENOTBLK,  // Block device required
        EBUSY,    // Device or resource busy
        EEXIST,   // File exists
        EXDEV,    // Invalid cross-device link
        ENODEV,   // No such device
        ENOTDIR,  // Not a directory
        EISDIR,   // Is a directory
        EINVAL,   // Invalid argument
        ENFILE,   // Too many open files in system
        EMFILE,   // Too many open files
        ENOTTY,   // Inappropriate ioctl for device
        ETXTBSY,  // Text file busy
        EFBIG,    // File too large
        ENOSPC,   // No space left on device
        ESPIPE,   // Illegal seek
        EROFS,    // Read-only file system
        EMLINK,   // Too many links
        EPIPE,    // Broken pipe
        EDOM,     // Numerical argument out of domain
        ERANGE,   // Numerical result out of range
        -1        // Terminator
    };

    for (int i = 0; test_errors[i] != -1; i++) {
        ck_assert_str_eq(my_strerror(test_errors[i]), strerror(test_errors[i]));
    }
}
END_TEST

START_TEST(test_strerror_negative) {
    int errnum = -1;
    char expected[64];
    sprintf(expected, "Unknown error %d", errnum);
    ck_assert_str_eq(my_strerror(errnum), expected);
}
END_TEST

START_TEST(test_strerror_large) {
    int errnum = ERRLIST_SIZE + 100;
    char expected[64];
    sprintf(expected, "Unknown error %d", errnum);
    ck_assert_str_eq(my_strerror(errnum), expected);
}
END_TEST

START_TEST(test_strerror_zero) { ck_assert_str_eq(my_strerror(0), strerror(0)); }
END_TEST

START_TEST(test_strerror_middle) {
    int mid = ERRLIST_SIZE / 2;
    ck_assert_str_eq(my_strerror(mid), strerror(mid));
}
END_TEST

START_TEST(test_strerror_repeat_calls) {
    const char *first = my_strerror(2);
    const char *second = my_strerror(2);
    ck_assert_str_eq(first, second);
}
END_TEST

Suite *suite_strerror(void) {
    Suite *suite = suite_create("MY_STRERROR");
    TCase *tcase = tcase_create("TCase_my_strerror");

    tcase_add_test(tcase, test_strerror_basic);
    tcase_add_test(tcase, test_strerror_negative);
    tcase_add_test(tcase, test_strerror_large);
    tcase_add_test(tcase, test_strerror_zero);
    tcase_add_test(tcase, test_strerror_middle);
    tcase_add_test(tcase, test_strerror_repeat_calls);

    suite_add_tcase(suite, tcase);
    return suite;
}
