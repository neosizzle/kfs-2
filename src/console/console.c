#include "video.h"
#include "printk.h"
#include "screen.h"
#include "string.h"
#include "gdt.h"

extern void reboot();
char console_buff[1024];
int console_buff_idx;

struct console_input {
	char console_buff[1024];
	int console_buff_idx;
};

struct console_input console_inputs[MAX_SCREENS];

static void console_clear_buff_all(void)
{
	for (int i = 0; i < MAX_SCREENS; i++)
	{
		for (int j = 0; j < 1024; j++)
			console_inputs[i].console_buff[j] = 0;
		console_inputs[i].console_buff_idx = 0;
	}
	
}

void console_clear_buff(void)
{
	int curr_screen = get_curr_screen();

	for (int i = 0; i < 1024; i++)
		console_inputs[curr_screen].console_buff[i] = 0;
	console_inputs[curr_screen].console_buff_idx = 0;
}

void console_print_prompt(void)
{
	terminal_writestring_color("[jng@kfs1]", VGA_COLOR_CYAN);
	terminal_writestring("$ ");
}

void console_print_prompt_rest(void)
{
	screen_writestring_color_rest("[jng@kfs1]", VGA_COLOR_CYAN);
	screen_writestring_color_rest("$ ", VGA_COLOR_LIGHT_GREY);
}

/**
 * Init console, prints prompt
*/
void init_console(void)
{
	console_print_prompt();
	console_print_prompt_rest();
	console_clear_buff_all();
}

void console_add_to_buff(char c)
{
	int curr_screen = get_curr_screen();

	if (console_inputs[curr_screen].console_buff_idx >= 1023)
		return;
	console_inputs[curr_screen].console_buff[console_inputs[curr_screen].console_buff_idx++] = c;
}

int console_process_buff(void)
{
	int curr_screen = get_curr_screen();
	char *input = console_inputs[curr_screen].console_buff;

	if (!strcmp(input, "halt"))
	{
		__asm__ ("hlt");
		return 0;
	}
	if (!strcmp(input, "reboot"))
	{
		__asm__ ("ljmpw $0xFFFF, $0x0000");
		return 0;
	}
	if (!strcmp(input, "gdt"))
	{
		printk("\n%x\n", (uint32_t)_gdt_table);
		return 0;
	}
	if (!strcmp(input, "kstack"))
	{
		// print 16 rows of 8 bytes of stack
		uint8_t *stack_addr = (uint8_t *) GDT_ADDR - 0x20;

		printk("\n");
		for (int i = 0; i < 16; i++)
		{
			printk_color(VGA_COLOR_LIGHT_BLUE, "%x:", stack_addr);
			for (int j = 0; j < 8; j++)
			{
				printk(" %x ", *stack_addr);
				++stack_addr;
			}
			printk("\n");
		}
		
		return 0;
	}
	printk("\n%s\n", console_inputs[curr_screen].console_buff);
	return 0;
}