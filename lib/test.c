#include "../include/libft.h"
// #include "../include/so_long.h"

/*******************************************************************************
*******************************************************************************/
// <!> - - - - - - - - - - - </!>
///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * *
░█████╗░  ███████╗░█████╗░██╗██████╗░███████╗
██╔══██╗  ██╔════╝██╔══██╗██║██╔══██╗██╔════╝
███████║  █████╗░░███████║██║██████╔╝█████╗░░
██╔══██║  ██╔══╝░░██╔══██║██║██╔══██╗██╔══╝░░
██║░░██║  ██║░░░░░██║░░██║██║██║░░██║███████╗
╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝╚═╝╚═╝░░╚═╝╚══════╝

> resize all sprites, + up direction (64 px)


bulbizare create grass behind him, grass is 0 or '*'


make github > ask input for comment
git commit -m "$(date) + print memory "
blink work with %S?


lib > comment line of norm size\
random cat color makefile

<?> .PHONY: test - This declares that test is a phony target, meaning it's not associated with a file. </?>

* * * * * * * * * * * * * * * * * * * * * * * * * * * */
// MACRO
// #define funct(ap, type)    (*(type *)((ap += sizeof(type)) - sizeof(type)))
///////////////////////////////////////////////////////////////////////////////]
int	main(int ac, char **av, char **env)
{
    int fd = open("map/map3.ber", O_RDONLY);
	if (fd == -1)
		return (put("error fd\n"));
	char *line = NULL;
	char **file = NULL;
	while ((line = gnl(fd)) != NULL)
		file = expand_tab(file, line);
    put("\n%#.8S\n== still here ^^\n", "ajksdf lkjadsflkjhasdlkfsj alksdjflajd flkaj fdlkja sdf l jka fdl");
    free_tab(file);
	free_s(line);
	close(fd);
    return 0;
}/*
///////////////////////////////////////////////////////////////////////////////]
----- >
NULL----->
==754==
==754== FILE DESCRIPTORS: 3 open (3 std) at exit.
==754==
==754== HEAP SUMMARY:
==754==     in use at exit: 112 bytes in 8 blocks
==754==   total heap usage: 16 allocs, 8 frees, 432 bytes allocated
==754==
==754== 48 bytes in 4 blocks are indirectly lost in loss record 1 of 2
==754==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==754==    by 0x10976D: f_rtrn_1 (gnl.c:78)
==754==    by 0x109939: gnl (gnl.c:128)
==754==    by 0x10928A: main (test.c:42)
==754==
==754== 112 (64 direct, 48 indirect) bytes in 4 blocks are definitely lost in loss record 2 of 2
==754==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==754==    by 0x1093D1: expand_tab (expend_free.c:40)
==754==    by 0x109280: main (test.c:43)
==754==
==754== LEAK SUMMARY:
==754==    definitely lost: 64 bytes in 4 blocks
==754==    indirectly lost: 48 bytes in 4 blocks
///////////////////////////////////////////////////////////////////////////////]*/
void    f_()
{
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
does somethign

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
}
///////////////////////////////////////////////////////////////////////////////]












//  			BIWISE
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
while (((condition1) & bit) || ((condition2) & ~bit))

   Setting a Bit at N: (counting from 0)
x |= (1 << N);

   Clearing a Bit at N:
x &= ~(1 << N);

	Toggling a Bit at N:
x ^= (1 << N);

	Toggle a specific range of bits, end (inclusive)
x ^= ((1 << (end - start + 1)) - 1) << start;

	Checking if Bit N is Set:
if (x & (1 << N)) {
	// Bit is set }

	Checking if a Bit is Clear:
if (!(x & (1 << N))) {
	// Bit is clear}

	Setting Multiple Bits at Once:
x |= (1 << 1) | (1 << 3) | (1 << 5);

	Extracting Specific Bits: (3 least)
int	extractedBits = x & 0b111;

	Swapping Two Variables without Using a Temporary Variable:
a ^= b;
b ^= a;
a ^= b;

	Checking if an Integer is Even or Odd: (faster than % 2)
if (num & 1)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
