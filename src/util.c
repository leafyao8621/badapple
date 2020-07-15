#include <stdio.h>
#include <stdlib.h>
#include <png.h>

static unsigned char buf[5760];
static png_bytep row_ptr_buf[24];

void initialize(void) {
    unsigned char *iter_buf = buf;
    png_bytep *iter_row_ptr_buf = row_ptr_buf;
    for (int i = 0; i < 24; ++i, iter_buf += 240, ++iter_row_ptr_buf) {
        *iter_row_ptr_buf = iter_buf;
    }
}
void read_image(const char *fn) {
    FILE *fin = fopen(fn, "rb");
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop info = png_create_info_struct(png);
    png_init_io(png, fin);
    png_set_sig_bytes(png, 0);
    png_read_info(png, info);
    png_read_image(png, row_ptr_buf);
    png_destroy_read_struct(&png, &info, 0);
    fclose(fin);
}

void print_image(char val) {
    unsigned char *iter = buf;
    for (int i = 0; i < 24; ++i) {
        for (int j = 0; j < 80; ++j, iter += 3) {
            if (val) {
                printf("%02X%02X%02X ", iter[0], iter[1], iter[2]);
            } else {
                putchar(*iter < 0x7f ? ' ' : '*');
            }
        }
        putchar(10);
    }
}
