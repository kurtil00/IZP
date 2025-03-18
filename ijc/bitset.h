#include <assert.h>

typedef unsigned long* bitset_t;
typedef unsigned long bitset_index_t;

#define bitset_create(jmeno_pole,velikost) \
_Static_assert(velikost > 0, u8"Velikost pole musí být přirozené číslo."); \
unsigned long jmeno_pole[(velikost+1) / sizeof(unsigned long) - velikost % sizeof(unsigned long)] = {0}; \
jmeno_pole[0] = velikost;


#define bitset_alloc(jmeno_pole,velikost) \
_Static_assert(velikost < sizeof(unsigned long), u8"Velikost pole musí být menší než unsigned long.") \
bitset_t jmeno_pole = calloc(velikost, sizeof(unsigned long))
