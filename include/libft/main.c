#include "libft.h"
int     main(void)
{
       int     index;
       char  **tab;
       tab = ft_split("AxBxCCCxDDDDxEExxxF", 'x');
       index = 0;
       while (tab[index])
               free(tab[index++]);
       free(tab);
       while (1) ;
}
