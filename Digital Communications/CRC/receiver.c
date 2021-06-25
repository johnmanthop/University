#include <stdlib.h>
#include "bit_ops.h"

/*
 * Function to simulate the receivment of a message
 * if the crc check equals true then the message is (probably) not corrupted
 * @param msg the received message in binary
 * @param P the p parameter in binary
 * @return true if the message is not detected as corrupted, false otherwise
 */
char receive(char *msg, char *P)
{
	char *temp = mod(msg, P); //find the modulo result
	char code;
	
	if (temp == NULL) { //should probably never happen
		return -2;
	}
	
	code = zero(temp); //get the crc check code
	//if the modulo result is zero then the message is ok (return true), if the result is not zero, there probably is an error (return false)
	
	free(temp); //return memory
	
	return code;
}