#ifndef STRING_UTILS_H
# define STRING_UTILS_H

int		mstrlen(const char *str);
char	*mstrdup(const char *str);
void	drop_blanks(char **str);
char	*mstrcat(char *dst, const char *src, unsigned int srclen);

#endif	/*STRING_UTILS_H*/
