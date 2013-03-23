#include <stdio.h>
#include <errno.h>
#include "backup.h"
#include "backup_test_helpers.h"

// Test for #6317 (nonexistent destination directory causes segfault) 
const int expect_result = EINVAL;
int   error_count=0;
bool  ok=true;

static void expect_error(int error_number, const char *error_string, void *error_extra) {
    if (error_count!=0)              { ok=false; fprintf(stderr, "%s:%d error function called twice\n", __FILE__, __LINE__); }
    error_count++;
    if (error_number!=expect_result) { ok=false; fprintf(stderr, "%s:%d error_number=%d expected %d\n", __FILE__, __LINE__, error_number, expect_result); }
    if (error_string==NULL)          { ok=false; fprintf(stderr, "%s:%d expect error_string nonnull\n", __FILE__, __LINE__); }
    printf("error_string=%s\n", error_string);
    if (error_extra!=NULL)           { ok=false; fprintf(stderr, "%s:%d expect error_extra NULL\n", __FILE__, __LINE__); }
}
    
const char *BACKUP_NAME = __FILE__;

int main(int argc __attribute__((__unused__)), const char *argv[] __attribute__((__unused__))) {
    cleanup_dirs(); // remove destination dir
    setup_source();
    setup_dirs();
    // No destination dir
    pthread_t thread;
    start_backup_thread_with_funs(&thread, get_src(), NULL, simple_poll_fun, NULL, expect_error, NULL, expect_result);
    finish_backup_thread(thread);
    if (ok && error_count!=1) {
        ok=false;
        fprintf(stderr, "%s:%d expect error_count==1 but it is %d\n", __FILE__, __LINE__, error_count);
    }
    if (ok) {
        pass();
    } else {
        fail();
    }
    printf(": test6317()\n");
    return 0;
}
