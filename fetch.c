#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    .UserAgent = "cfetch/v0.2a",
    .CacheControl = "no-cache",
    .AcceptLanguage = "en"
};


/*
FLAG LEGEND
[HEADERS]
-c ContentType
-u UserAgent
-cc CacheControl
-al AcceptLanguage
[OPTIONS]
-m method <GET|POST|PUT|DELETE>
-C credentials <omit|same-origin|include>
-b body
-bt bodytype (<application/json>)
-M mode
-ca cache <default|no-store|reload|no-cache|force-cache|only-if-cached>
-r redirect <follow|error|manual>
*/

const int flagLength = 11;
char* flags[11] = {"-c", "-u", "-cc", "-al", "-m", "-C", "-b", "-bt", "-M", "-ca", "-r"};
char** flagParameters;

void displayHelp() {
    printf("\nUsage: fetch [-c contenttype] [-u useragent] [-cc cachecontrol] [-al acceptlanguage] [-m <GET|POST|PUT|DELETE>] [-C <omit|same-origin|include>] [-b body] [-M <cors|no-cors|same-origin>] [-ca <default|no-store|reload|no-cache|force-cache|only-if-cached>] [-r <follow|error|manual>] [--help] target_url\n\nNote that all of these options have suitable default values specified in README.md.\n\nOptions:\n\t[HEADERS]\n\t-c\tSpecify the Content-Type header of the HTTP request.\n\t-a\tSpecify the Authorization header of the HTTP request.\n\t-ac\tSpecify the Accept header of the HTTP request\n\t-u\tSpecify the UserAgent (no spaces)\n\t-cc\tSpecify the Cache-Control header\n\t-al\tSpecify the Accept-Language header\n\t[OPTIONS]\n\t-m\tSpecify the HTTP method. Accepts <GET|POST|PUT|DELETE>\n\t-b\tThe content of the body. Only necessary on non GET requests. Don't forget to specify -c\n\n");
    return;
}

int flagIsValid(char* argv) {
    int length = sizeof(flags) / sizeof(flags[0]);
    if (!strcmp("--help", argv)) {
        displayHelp();
    }
    for (int i = 0; i < length; i++) {
        if (!strcmp(flags[i], argv)) {
            return 1;
        }
    }
    return 0;
}

int parameterIsValid(char* parameterFlag, char* parameter) {
    for (int i = 0; i < flagLength; i++) {
        char* currentFlag = flags[i];
        if (!strcmp(currentFlag, parameterFlag)) {
            // complete
        }
    }
}

int main(int argc, char* argv[]) {
    flagParameters = (char**) malloc(flagLength * sizeof(char*));
    printf("%p", flagParameters);
    if (argc == 1) {
        displayHelp();
    }
    for (int i = 1; i < argc; i++) {
        if (i % 2) {
            char* flag = argv[i];
            int flagValid = flagIsValid(flag);
            if (!strcmp("--help", argv[i])) {
                return 0;
            }
            if (!flagValid) {
                printf("Error: The argument '%s' is invalid. Use fetch --help to view available flags.\n", argv[i]);
                return -1;
            }
            continue;
        }
        char* parameterFlag = argv[i-1];
        char* parameter = argv[i];
        int parameterValid = parameterIsValid(parameterFlag, parameter);
    }
    return 0;
};