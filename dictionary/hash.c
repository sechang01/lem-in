#include <stdio.h>

unsigned long	hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
		hash += c;
 //       hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return (hash % 31);
}

int	main()
{
	printf("%lu\n:", hash("zhuowei"));
	return (0);
}

