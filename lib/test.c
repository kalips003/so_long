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
	while ((line = gnl(fd)) != NULL)
	{
    	put("%S", line);
		free_s(line);
	}
	close(fd);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////]
void    f_()
{
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
does somethign

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
}
///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



//  			GITHUB
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
git pull
git log > navigate snapshots in time
git log --pretty=fuller
git log --pretty=oneline --abbrev-commit --date=short
git log --since="2022-01-01" --until="2022-12-31"
git checkout <commit-hash>
	Use the hash from the log output.
	save a good commit hash is Makefile Makerestore
To reset the repository to a specific commit:
	git reset --hard <commit-hash>
git push origin feature-branch:main


// Stash Changes: Use git stash to stash your changes.
	git stash
// Switch Branches: After stashing your changes, you can switch branches.
	git checkout <branch-name>
// Apply Stashed Changes: When you're ready, you can apply your stashed changes to the new branch.
	git stash apply
// Pop Stashed Changes: Alternatively, you can apply and remove the stashed changes in one step.
	git stash pop
// List Stashes: To see a list of stashed changes, you can use:
	git stash list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



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
