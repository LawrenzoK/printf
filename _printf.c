#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * custom_printf - Custom printf function
 * @format: format string
 *
 * Return: number of characters printed
 */

int custom_printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buf_idx = 0;
	va_list list;
	char buf[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buf[buf_idx++] = format[i];
			if (buf_idx == BUFF_SIZE)
				flush_buffer(buf, &buf_idx);
			printed_chars++;
		}
		else
		{
			flush_buffer(buf, &buf_idx);
			flags = fetch_flags(format, &i);
			width = fetch_width(format, &i, list);
			precision = fetch_precision(format, &i, list);
			size = fetch_size(format, &i);
			++i;
			printed = process_print(format, &i, list, buf,
					flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}
	flush_buffer(buf, &buf_idx);

	va_end(list);

	return (printed_chars);
}

/**
 * flush_buffer - Flushes the contents of the buffer if it exists
 * @buf: array of chars
 * @buf_idx: index at which to add next char, represents the length.
 */

void flush_buffer(char buf[], int *buf_idx)
{
	if (*buf_idx > 0)
		write(1, &buf[0], *buf_idx);
	*buf_idx = 0;
}
