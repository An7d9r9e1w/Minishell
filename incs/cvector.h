#ifndef CVECTOR_H
# define CVECTOR_H

typedef struct s_cvector
{
	char			*arr;
	unsigned int	capacity;
	unsigned int	size;
}	t_cvector;

t_cvector		*cvector_create(void);
void			cvector_free(t_cvector *cv);
int				cvector_write(t_cvector *cv, char *str, unsigned int length);

#endif	/*CVECTOR_H*/
