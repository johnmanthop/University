#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bit_ops.h"

/*
 * Function to create the crc bitstring
 * @param msg the original message the user wants to transmit
 * @param p the P parameter
 * @return the crc code appended message, note the result is returned by reference to the msg parameter
 */
void create_crc_msg(char **msg, char *p)
{
	unsigned k = strlen(*msg), n = strlen(p) + k - 1;
	char *remainder;
	
	shift_left(msg, n-k); //step 1 of 3 for the crc calculation
	//put n-k zeros to the right of the original message
	remainder = mod(*msg, p);//step 2 of 3
	//calculate the modulo of msg devided by p
	memcpy(*msg + strlen(*msg) - (n-k), remainder, strlen(remainder) + 1);
	//copy the modulo result to the appropriate bit position of the message
	free(remainder); //free up the allocated memory
}

/*
 * Function to simulate the bit error rate in a channel
 * @param msg the message to apply the error
 * @param ber the chance of a single bit flipping
 * @result true if the message is corrupted at least in one place, false otherwise
 */
char apply_noise(char *msg, float ber)
{
	unsigned i;
	char changed = 0;

	for (i = 0; i < strlen(msg); ++i) {
		float n = (float)rand() / (float)RAND_MAX; //get a random float in (0, 1]
		if (n <= ber) { //if the result is under the error limit then switch the bit
			msg[i] = ((msg[i] == '0')*'1' + (msg[i] == '1')*'0'); //branchless programing
			changed = 1;
		}
	}
	
	return changed;//return a boolean if the message has or has not changed
}