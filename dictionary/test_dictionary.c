#include <stdio.h>
#include "hashix.h"

int	main()
{
	t_hasharr *d;
	t_hashlst *tmp;

	printf("Hashvalue %u\n", hashix("Apple"));
	printf("Hashvalue %u\n", hashix("Apple"));
	printf("12356\n");


	printf("12356\n");
	d = hash_newtab();
	hash_install("Apple", "14", d);
	hash_install("Orangee", "42", d);
	tmp = hash_lookup("Apple", d);

	printf("Hashvalue %u\n", hashix("Apple"));
	printf("tmp: %x\n", (unsigned int)tmp);

	printf("lookup\n");
	printf("%s\n", (char *)tmp->key);

	printf("lookup another\n");
	tmp = hash_lookup("Orangee", d);
	printf("%s\n", (char *)tmp->data);

	return (0); 
}