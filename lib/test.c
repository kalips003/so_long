// cc test.c -L. -l:libft.a && ./a.out
// cls && cc test.c -L. -l:./push_swap/lib/libft.a && ./a.out
#include "../include/libft.h"
#include "../include/so_long.h"

//, void (*del)(void *),
// int my_function(int num, ...);
// #define funct(ap, type)    (*(type *)((ap += sizeof(type)) - sizeof(type)))

int	main(int ac, char **av, char **env)
{
	int randomNumber;
	int i = -1;

	while (++i < atoi_v(av[1]))
	{
		randomNumber = (rand() % (MAX_CHANCE + 1));
		put("random number = %d\n", randomNumber);
	}
	return (0);
}

// while (((condition1) & bit) || ((condition2) & ~bit))

// Structures: You can define a structure that contains function pointers as members. This is useful when you want to associate functions with other data or metadata.

// typedef struct {
//     void (*functionPtr)(void *);
//     char *description;
// } FunctionInfo;

// FunctionInfo myFunctions[] = {
//     {function1, "Function 1"},
//     {function2, "Function 2"},
//     {function3, "Function 3"}
// };

//  HEXA MEMORY
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	0x11111111 > 286331153
	0x22222222 > 572662306
	0x33333333 > 858993459
	0x44444444 > 1145324612
	0x55555555 > 1431655765
	0x66666666 > 1717986918
	0x77777777 > 2004318071
	0x88888888 > 2290649224
	0x99999999 > 2576980377
*/

//  BIWISE
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	//  #   Setting a Bit at a Specific Position:
// Set the 4th bit (counting from 0) of a variable x
x |= (1 << 4);

	//  #   Clearing a Bit at a Specific Position:
// Clear the 3rd bit of a variable x
x &= ~(1 << 3);

	//  #   Toggling a Bit at a Specific Position:
// Toggle the 5th bit of a variable x
x ^= (1 << 5);

	//  #   Checking if a Bit is Set:
// Check if the 2nd bit of a variable x is set
if (x & (1 << 2)) {
	// Bit is set
}

	//  #   Checking if a Bit is Clear:
// Check if the 1st bit of a variable x is clear
if (!(x & (1 << 1))) {
	// Bit is clear
}

	//  #   Setting Multiple Bits at Once:
// Set the 1st, 3rd, and 5th bits of a variable x
x |= (1 << 1) | (1 << 3) | (1 << 5);

	//  #   Extracting Specific Bits:
// Extract the 3 least significant bits from a variable x
int	extractedBits = x & 0b111;

	//  #   Swapping Two Variables without Using a Temporary Variable:
// Swap the values of variables a and b without using a temporary variable
a ^= b;
b ^= a;
a ^= b;

	//  #   Checking if an Integer is Even or Odd:
// Check if a number is even or odd
if (num & 1) {
	// Number is odd
} else {
	// Number is even
}




Yes,
	there are bitwise operations that can perform toggling on specific bits of a number,
	including toggling a range of bits. One common operation is using XOR with a bitmask.

Let's say you want to toggle a specific range of bits,
	starting from bit position start and ending at bit position end (inclusive),
	in a number x. You can use the following bitwise XOR operation with a bitmask:

plaintext

x ^= ((1 << (end - start + 1)) - 1) << start;

Here's how it works:

	(1 << (end - start + 1)) - 1: This expression generates a bitmask with end
		- start + 1 consecutive set bits. For example,
		if start is 2 and end is 4,
		this expression will generate 111 in binary (7 in decimal).
	<< start: This shifts the bitmask to the left by start positions to align it with the range you want to toggle.
	x ^= ...: This performs a bitwise XOR operation between the original number x and the bitmask,
		effectively toggling the bits within the specified range.

For example, let's say you have a number x and you want to toggle bits 2 to 4:

plaintext

x ^= ((1 << (4 - 2 + 1)) - 1) << 2;

If x is initially 10101010 in binary, after performing the above operation,
	the bits 2 to 4 will be toggled, resulting in 10000010.


*/
