#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

static void show_pid(char *buffer)
{
    char *res;
    int times = 0;

    while((res = strsep(&buffer, " ")) != NULL) {
        if (! strlen(res)) {
            continue;
        }

        if (times == 3) {
            printf("%s\n", res);
            return;
        }
        times ++;
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[4096];
    bool have_broser = false;
    const char *b2g_ps = "adb shell b2g-ps";
    
    fp = popen(b2g_ps, "r");
    assert(fp);

    while(fgets(buffer, 4095, fp) != NULL) {
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = 0;
        }

        if (! strncmp(buffer, "Browser", 7)) {
            have_broser = true;
            show_pid(buffer);
        } else if (! strncmp(buffer, "CastApp", 7)) {
            have_broser = true;
            show_pid(buffer);
        }
    }
    pclose(fp);

    if (! have_broser) {
        exit(1);
    }
    return 0;
}

