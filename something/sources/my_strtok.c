#include "cub3d.h"
# include <string.h>



char	*ft_strpbrk(const char *s, const char *charset)
{
	int		i;

	if (!s || !charset)
		return (0);
	while (*s)
	{
		i = -1;
		while (charset[++i])
			if (*s == charset[i])
				return ((char *)s);
		s++;
	}
	return (0);
}

int		check_char(char c, const char *charset)
{
	int		i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!check_char(s[i], accept))
			return (i);
		i++;
	}
	return (i);
}


char *my_strtok(char *s, char *delim)
{
    static char *olds;
    char *token;

    if (s == NULL)
        s = olds;
    s += ft_strspn(s, delim);
    if (*s == '\0')
    {
        olds = s;
        return (NULL);
    }
    token = s;
    s = ft_strpbrk(token, delim);
    if (s == NULL)
        olds = strchr(token, '\0');
    else
    {
        *s = '\0';
        olds = s + 1;
    }
    return (token);
}



// unsigned int is_delim(char c, char *delim)
// {
//     while(*delim != '\0')
//     {
//         if(c == *delim)
//             return 1;
//         delim++;
//     }
//     return 0;
// }

// char *my_strtok(char *str, char *delim)
// {
//     static char *backup_str;
    
//     if(!str)
//         str = backup_str;
//     if(!str)
//         return NULL;
//      while(1)
//     {
//         if(is_delim(*str, delim))
//         {
//             str++;
//             continue;
//         }
//         if(*str == '\0')
//             return NULL; 
//         break;
//     }
//     char *ret = str;
//     while(1)
//     {
//         if(*str == '\0')
//         {
//             backup_str = str;
//             return ret;
//         }
//         if(is_delim(*str, delim))
//         {
//             *str = '\0';
//             backup_str = str + 1;
//             return ret;
//         }
//         str++;
//     }
// }




