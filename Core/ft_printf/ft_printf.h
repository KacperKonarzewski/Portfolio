#ifndef FTPRINTF
# define FTPRINTF

#include "libft.h"
#include "stdarg.h"

int	ft_printf(const char* str, ...);
int	find_in_set(char c, const char* charset);
int	get_flag_length(const char* str, int per_index);

#endif