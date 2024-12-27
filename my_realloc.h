#ifndef MY_REALLOC_H
#define MY_REALLOC_H

void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;

	if (ptr == NULL)
	return (malloc(new_size);

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
}

new_ptr = malloc(new_size);
if (new_ptr == NULL)
	return (NULL);

	memcpy(new_ptr, ptr, (old_size) ? old_size : new_size);
	free(ptr);

	return (new_ptr);

#endif
