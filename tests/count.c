#include <unistd.h>
#include <stdio.h>

int main()
{
    int n = 0;
    while(1) {
        printf("%d\n", n++);
        sleep(1);
    }
}
