#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define FLAG_NO 11

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

char* flags[FLAG_NO] = {"-c", "-u", "-cc", "-al", "-m", "-C", "-b", "-bt", "-M", "-ca", "-r"};

void displayHelp() {
    printf("\nUsage: fetch [-c contenttype] [-u useragent] [-cc cachecontrol] [-al acceptlanguage] [-m <GET|POST|PUT|DELETE>] [-C <omit|same-origin|include>] [-b body] [-M <cors|no-cors|same-origin>] [-ca <default|no-store|reload|no-cache|force-cache|only-if-cached>] [-r <follow|error|manual>] [--help] target_url\n\nNote that all of these options have suitable default values specified in README.md.\n\nOptions:\n\t[HEADERS]\n\t-c\tSpecify the Content-Type header of the HTTP request.\n\t-a\tSpecify the Authorization header of the HTTP request.\n\t-ac\tSpecify the Accept header of the HTTP request\n\t-u\tSpecify the UserAgent (no spaces)\n\t-cc\tSpecify the Cache-Control header\n\t-al\tSpecify the Accept-Language header\n\t[OPTIONS]\n\t-m\tSpecify the HTTP method. Accepts <GET|POST|PUT|DELETE>\n\t-b\tThe content of the body. Only necessary on non GET requests. Don't forget to specify -c\n\n");
    return;
}

int contains(char* list[], char* item, size_t length) {
    for (int i = 0; i < length; i++) {
        if (!strcmp(list[i], item)) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 1 || contains(argv, "--help", argc)) {
        displayHelp();
        return 0;
    }
    for (int i = 1; i < argc; i += 2) {
        char* flag = argv[i];
        int flagValid = contains(flags, flag, FLAG_NO);
        if (!flagValid) {
            printf("Error: The argument '%s' is invalid. Use fetch --help to view available flags.\n", argv[i]);
            return -1;
        }
        continue;
    }
    return 0;
};
