#include <stdio.h>
#include <string.h>
#include "cpp.h"

int main()
{
    printf("Welcome in ÉShell!\n");

    while (true) {
        // Show a ladder (ÉShell) on the left of the screen
        printf("╬═╬ ");
        char command[1024];
        scanf("%s", command);

        if (!strcmp(command, "exit")) {
            return 0;
        }
    }
}
