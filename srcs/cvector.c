#include <stdlib.h>

#include <cvector.h>

static int	cvector_realloc(t_cvector *cv, unsigned int new_size)
{
	char			*arr;
	char			*cur_arr;
	char			*cur_cv;
	unsigned int	count;

	if (!new_size)
		return (-1);
	arr = malloc(sizeof(char) * new_size);
	if (!arr)
		return (-1);
	if (new_size < cv->count)
		cv->count = new_size;
	count = cv->count;
	cur_arr = arr;
	cur_cv = cv->arr;
	while (count--)
		*cur_arr++ = *cur_cv++;
	free(cv->arr);
	cv->arr = arr;
	cv->size = new_size;
	return (0);
}

t_cvector	*cvector_create(void)
{
	t_cvector	*cv;

	cv = malloc(sizeof(t_cvector));
	if (!cv)
		return (0);
	cv->size = 1024;
	cv->count = 0;
	cv->arr = malloc(sizeof(char) * cv->size);
	if (cv->arr)
		return (cv);
	free(cv);
	return (0);
}

void	cvector_free(t_cvector *cv)
{
	if (cv)
	{
		if (cv->arr)
			free(cv->arr);
		free(cv);
	}
}

int	cvector_write(t_cvector *cv, char *str, unsigned int length)
{
	char			*cur_cv;
	unsigned int	size;

	size = cv->size;
	while (cv->count + 1 + length > size)
		size <<= 1;
	if (size > cv->size)
		if (cvector_realloc(cv, size))
			return (1);
	cur_cv = cv->arr + cv->count;
	while (length--)
		*cur_cv++ = *str++;
	*cur_cv = 0;
	cv->count += cur_cv - (cv->arr + cv->count);
	return (0);
}
