#include "video.h"
#include "string.h"
#include "types.h"

void printk_color(enum vga_color color, char *str, ...)
{
	void **va_idx = (void **)(&str);
	char int_str[256];

	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] != '%')
			terminal_putchar(str[i], color);
		else
		{
			if (str[i + 1] == 's')
			{
				va_idx += 1;
				char *_str = *(char **)(va_idx);
				terminal_writestring_color(_str, color);
			}
			else if (str[i + 1] == 'd')
			{
				va_idx += 1;
				int num = (int)*(int **)(va_idx);

				itoa(num, int_str);
				terminal_writestring_color(int_str, color);
			}
			else if (str[i + 1] == 'c')
			{
				va_idx += 1;
				char _char = (char)*(char *)va_idx;
				terminal_putchar(_char, VGA_COLOR_LIGHT_GREY);
			}
			else if (str[i + 1] == 'x')
			{
				va_idx += 1;
				int num = (int)*(int **)(va_idx);

				itoa_hex(num, int_str);
				terminal_writestring_color(int_str, color);
			}
			else
				terminal_putchar('?', VGA_COLOR_LIGHT_GREY);
			++i;
		}
	}
}


void printk(char *str, ...)
{
	void **va_idx = (void **)(&str);
	char int_str[256];

	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] != '%')
			terminal_putchar(str[i], VGA_COLOR_LIGHT_GREY);
		else
		{
			if (str[i + 1] == 's')
			{
				va_idx += 1;
				char *_str = *(char **)(va_idx);
				terminal_writestring(_str);
			}
			else if (str[i + 1] == 'd')
			{
				va_idx += 1;
				int num = (int)*(int **)(va_idx);

				itoa(num, int_str);
				terminal_writestring(int_str);
			}
			else if (str[i + 1] == 'c')
			{
				va_idx += 1;
				char _char = (char)*(char *)va_idx;
				terminal_putchar(_char, VGA_COLOR_LIGHT_GREY);
			}
			else if (str[i + 1] == 'x')
			{
				va_idx += 1;
				int num = (int)*(int **)(va_idx);

				itoa_hex(num, int_str);
				terminal_writestring(int_str);
			}
			else
				terminal_putchar('?', VGA_COLOR_LIGHT_GREY);
			++i;
		}
	}
}