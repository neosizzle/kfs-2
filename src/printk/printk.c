#include "video.h"
#include "string.h"
#include "types.h"


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
				int num = *(int **)(va_idx);

				itoa(num, int_str);
				terminal_writestring(int_str);
			}
			else
				terminal_putchar('?', VGA_COLOR_LIGHT_GREY);
			++i;
		}
	}
}

void test(char* a, int b)
{
	char **a_addr = &a;
	int **b_addr = a_addr + 1;
	char addr_str[123];

	itoa((uint32_t)&a, addr_str);
	terminal_writestring(addr_str);
	terminal_writestring("\n");
	itoa((uint32_t)&b, addr_str);
	terminal_writestring(addr_str);

	// itoa((uint32_t)&b, addr_str);
	// terminal_writestring("\n");
	// itoa((uint32_t)b_addr, addr_str);
	// terminal_writestring(addr_str);
	itoa(*b_addr, addr_str);
	terminal_writestring(addr_str);
}