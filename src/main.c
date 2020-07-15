#include <stdio.h>
#include <unistd.h>
#include "util.h"

int main(void) {
    initialize();
    char buf[1000];
    for (int i = 0; i < 6571; ++i) {
        sprintf(buf, "frames/badapple%04d.png", i + 1);
        read_image((const char*)buf);
        printf("\033[12A");
        print_image(0);
        usleep(33333);
    }
    return 0;
}
