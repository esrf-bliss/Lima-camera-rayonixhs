/*
The keys for the Blum program 'compare' (in lib/sort)
are groups of four integers stored in the global array sort_key.
The array sort_key contain the keys for a particular
sort in order of priority. Each key group has the following format:

   		(type, direction, position, length)

- type is 2 or 10 for long or float		(VAX-VMS numbers)
- direction is 0 or 1 for ascending or descending
- The position parameter  counts from the begining of a record starting at 0. 
(remember bytes 0 and 1 of each fortran record in Unix are the record length) 
- length is the size (4  or 2 for type = 2, 4 for type = 10)

The key groups are preceded in the array sort_key by an integer giving
the number of key groups following.

*/

#define MAXKEYS 5			/* max. number of sort keys per file */

#define TYPE(key)  (4 * key + 1)
#define DIRECTION(key) (4 * key + 2)
#define POSITION(key) (4 * key + 3)
#define LENGTH(key) (4 * key + 4)

int  sort_key[MAXKEYS * 4 + 1];		/* key describing current file sort */
int  compare_key[MAXKEYS * 4 + 1]; /* key used by compare in sorts, searches */
int compare(), pm_compare();
