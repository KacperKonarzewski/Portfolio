#include "ft_printf.h"

static char* get_flag(const char* str, int per_index)
{
	char*	flag;
	int		total_length;

	total_length = get_flag_length(str, per_index);
	
	flag = ft_substr(str, per_index + 1, total_length);
	printf("%s", flag);
	return (flag);	
}

static t_list*	find_all_conv(const char* str)
{
	t_list*	all_conv;
	int		i;
	char*		flag;

	i = -1;
	flag = NULL;
	all_conv = NULL;
	while(str[++i])
	{
		if (str[i] == '%')
		{
			flag = get_flag(str, i);
			if (flag == NULL)
				return NULL;
			if (all_conv == NULL)
				all_conv = ft_lstnew(flag);
		}
	}
}

int	ft_printf(const char* str, ...)
{
	t_list*	all_conv;
	va_list	arg_ls;

	va_start(arg_ls, str);
	
	all_conv = find_all_conv(str);

	va_end(arg_ls);
	return (0);
}