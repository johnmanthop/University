#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Bit op function to perform the left shift operation in a bitstring
 * This function preserves the extra leftmost bits by resizing the bitstr buffer
 * That means it can only be used with a malloc'd block of memory
 * @param bitstr the message to shift
 * @param amount the amount of shifts to perform
 */
void shift_left(char **bitstr, size_t amount)
{
	unsigned i;
	size_t size = strlen(*bitstr) + 1;
	
	*bitstr = realloc(*bitstr, (size + amount)*sizeof(char)); //prepae extra space 
	for (i = 0; i < amount; ++i) {
		(*bitstr)[size + i - 1] = '0';
	}
	(*bitstr)[size + i - 1] = 0; //set end character
}

/*
 * Bit op function to perform the overflow left shift operation
 * This function does not preserve any extra leftmost bits
 * @param bitstr the message to shift
 * @param amount the amount of shifts to perform
 */
void shift_lefto(char *bitstr, size_t amount)
{
	unsigned i;
	size_t size = strlen(bitstr) + 1;
	
	memcpy(bitstr, bitstr + amount, size - amount);
	for (i = size - amount - 1; i < size - 1; ++i) {
		bitstr[i] = '0';
	}
	bitstr[size - 1] = 0; //set end character
}

/*
 * Bit op function to perform right shift operation
 * The right shift can never preserve the rightmost bits, so they are lost
 * @param bitstr the message to shift
 * @param amount the amount of shifts to perform
 */
void shift_right(char *bitstr, size_t amount)
{
	unsigned i;
	size_t size = strlen(bitstr) + 1;

	memcpy(bitstr + amount, bitstr, size - amount);
	for (i = 0; i < amount; ++i) {
		bitstr[i] = '0';
	}
}

/*
 * Bit op function to perform the xor operation
 * @param a the first bit
 * @param b the second bit
 * @result the operation a xor b
 */
char c_xor(char a, char b)
{
	//branchless programming
	return '0'*(a == b) + '1'*(a != b);
}

/*
 * Bit op function to count any extra zero leftmost bits
 * In other words this function counts all the leading zeroes in a bitstring
 * @param bitstr the bitstring to scan
 * @result the number of leftmost zero characters in the string
 */
size_t oversize(char *bitstr)
{
	unsigned i;
	
	for (i = 0; i < strlen(bitstr) && bitstr[i] == '0'; ++i);
	return i;
}

/*
 * Bit op function to perform the xor modulo operation on two bitstrings
 * @param divident the operation's divident
 * @param divisor the operation's divisor
 * @result the xor modulo operation on the two bitstrings
 */
char *mod(char *divident, char *divisor)
{
	unsigned i, j;
	size_t step_size = strlen(divisor); //count the step size of every iteration
	char *buffer = malloc((step_size + 1) * sizeof(char)); //malloc a helper buffer memory (in the end it will store the result)
	
	if (step_size > strlen(divident)) {
		free(buffer);
		return NULL; //if the divisor is bigger than the divident return NULL (invalid op)
	}
	
	memcpy(buffer, divident, step_size * sizeof(char)); //copy the divident to the helper buffer
	buffer[step_size] = 0; //add the \0 char at the end
	
	for (i = 0; i < strlen(divident) - step_size + 1; ++i) { //while there are divident bits to perform operations on
		if (buffer[0] == '0') { //if the buffer right now starts with 0 perform a zero xor on all the buffer bits
			for (j = 0; j < step_size; ++j) {
				buffer[j] = c_xor('0', buffer[j]);
			}
		} else {
			for (j = 0; j < step_size; ++j) { //otherwise perform a xor operation on the divisor and buffer bits
				buffer[j] = c_xor(divisor[j], buffer[j]);
			}
		}
		
		shift_lefto(buffer, 1); //shift the buffer one left (skipping the leftmost bit)
		buffer[step_size - 1] = divident[i + step_size]; //add the next rightmost bit
	}
	
	//in other words this function performs the xor modulo as would be performed by hand (more or less)
	
	return buffer;
}
/* 
 * Bit op function to check if a binary input is zero or not
 * @param buffer the bitstring to check
 * @return false if the bitstring is not zero, true otherwise
 */
char zero(char *buffer)
{
	unsigned i;
	
	for (i = 0; i < strlen(buffer); ++i) {
		if (buffer[i] != '0') return 0;
	}
	
	return 1;
}