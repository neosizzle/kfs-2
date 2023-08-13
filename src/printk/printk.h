#ifndef __PRINTK__H__
#define __PRINTK__H__
#include "video.h"

void printk(char *str, ...);
void printk_color(enum vga_color color, char *str, ...);
#endif  //!__PRINTK__H__