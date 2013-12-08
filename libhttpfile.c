#define _GNU_SOURCE
#include <assert.h>
#include <curl/curl.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prefix(const char *a, const char*b) {
  int la = strlen(a);
  int lb = strlen(b);
  return 0 == strncmp(a, b, la > lb ? lb : la);
}

static int (*real_open)(const char* path, int flags, ...);

int open(const char* path, int flags, ...) {

  mode_t mode = 0;
  va_list arg;
  if ( flags & O_CREAT ) {
     va_start(arg, flags);
     mode = va_arg(arg, mode_t);
     va_end(arg);
  }

  if(!real_open) {
    real_open = dlsym(RTLD_NEXT, "open");
  }

  if(prefix(path, "http://") || prefix(path, "data:")) {
    printf("INTERPOSER: \"%s\" ->", path);
    CURL* h = curl_easy_init();
    curl_easy_setopt(h, CURLOPT_URL, path);
    char template[] = "/tmp/httplulzXXXXXX";
    mktemp(template);
    puts(template);
    FILE* f = fopen(template, "w");
    assert(f);
    curl_easy_setopt(h, CURLOPT_WRITEDATA, f);
    CURLcode ret = curl_easy_perform(h);
    if( ret != 0 ) {
      return -1;
    }
    curl_easy_cleanup(h);
    fclose(f);
    return real_open(template, flags, mode);
  }

  return real_open(path, flags, mode);
}
