#include <stdio.h>
#include <string.h>

typedef struct {
    char* ContentType;
    char* Authorization;
    char* Accept;
    char* UserAgent;
    char* CacheControl;
    char* AcceptLanguage;
} headers;

typedef struct {
    char* method;
    headers headers;
} fetchArguments;

headers defaultHeaders = {
    .ContentType = "text/html",
    .Authorization = "none",
    .Accept = "*/*",
    .UserAgent = "cfetch/v0.1a",
    .CacheControl = "no-cache",
    .AcceptLanguage = "en"
};


/*
FLAG LEGEND
-c ContentType
-a Authorization
-ac Accept
-u UserAgent
-cc CacheControl
-al AcceptLanguage
*/

int flagIsValid(char* argv) {
    char* flags[] = {"-c", "-a", "-ac", "-u", "-cc", "-al"};
    int length = sizeof(flags) / sizeof(flags[0]);
    if (!strcmp("--help", argv)) {
        printf("\nUsage: fetch [-c contenttype] [-a authorization] [-ac accept] [-u useragent] [-cc cachecontrol] [-al acceptlanguage] target_url\n\nNote that all of these options have suitable default values.\n\nOptions:\n\t-c\tSpecify the Content-Type header of the HTTP request.\n\t-a\tSpecify the Authorization header of the HTTP request.\n\n");
    }
    for (int i = 0; i < length; i++) {
        if (!strcmp(flags[i], argv)) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (i % 2 == 1) {
            int flagValid = flagIsValid(argv[i]);
            if (!strcmp("--help", argv[i])) {
                return 0;
            }
            if (!flagValid) {
                printf("Error: The argument '%s' is invalid. Use fetch --help to view available flags.\n", argv[i]);
                return -1;
            }
        }
    }
    return 0;
};