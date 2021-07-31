#ifndef STRING_UTILS_H
# define STRING_UTILS_H

int		mstrlen(const char *str);
int		mstrlcpy(char *dst, const char *src, int dstsize);
char	*mstrdup(const char *str);
char	*mstrcat(char *dst, const char *src, unsigned int srclen);
void	drop_blanks(char **str);
char	**convert_into_solid_arr(char **strs, unsigned int len);

#endif	/*STRING_UTILS_H*/
