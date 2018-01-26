#include "ft_malloc.h"

void	  *create_block(t_block *block, size_t size)
{
  t_block *next;
  t_block *tmp;

	next = NULL;
  if (block && block->next)
  {
    tmp = block;
    while (tmp && tmp->next)
      tmp = tmp->next;
    next = tmp;
  }
  if (next && next->state == FREE && size < next->size)
  {
    next->state = USED;
    next->next = ((void*)next + sizeof(t_block) + size);
    next->next->state = FREE;
    next->next->size = (int)next->size - (int)size - sizeof(t_block);
		next->next->next = NULL;
    next->size = size;
    return ((void*)next + sizeof(t_block));
  }
  else
  {
    block->state = USED;
    block->next = ((void*)block + sizeof(t_block) + size);
    block->next->state = FREE;
    block->next->size = (int)block->size - (int)size - sizeof(t_block);
		block->next->next = NULL;
    block->size = size;
		return ((void*)block + sizeof(t_block));
  }
	return (NULL);
}

int     create_page(size_t size, t_block **block)
{
  if ((*block = (void *)mmap(0, size, PROT_READ | PROT_WRITE,\
    MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (0);
  init_block(*block, size);
  return (1);
}