#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "receiver.h"
#include "sender.h" 

/*
 * Function to create a random bitstring of size k
 * @param buffer the buffer to fill the the message
 * @param k the size of the message
 * @return the randomized message, note the result is returned by reference in the buffer
 */
void randomize(char *msg, size_t k)
{
	unsigned i;
	
	for (i = 0; i < k; ++i) {
		msg[i] = (rand() % 2) + 48; //get a random number between 0 and 1 and convert it to char (by adding the value 48)
	}
	
	msg[k] = 0; //add the \0 char at the end
}

/*
 * Helper function to perform a benchmark
 * @param k the message size
 * @param p the P parameter
 * @param ber the bit error rate
 * @param samples the amount of tests to perform
 */
void benchmark(unsigned k, char *p, float ber, unsigned samples)
{
	unsigned i;
	unsigned w_msgs = 0, d_msgs = 0, ud_msgs = 0;
	//all wrong messages, detected wrong messages, undetected wrong messages
	//should be wrong = detected + undetected
	char *msg = malloc((k+1) * sizeof(char));
	
	for (i = 0; i < samples; ++i) {
		char recv_code;
		
		randomize(msg, k); //create random message
		create_crc_msg(&msg, p); //add crc bits
		
		if (apply_noise(msg, ber)) { //apply noise and if an error occures
			++w_msgs; //add to the wrong messages
			recv_code = receive(msg, p); //perform a receive operation
			if (recv_code == -2) {
				printf("Fatal error\n");
				return; //Should never happen (happens only when divisor > divident)
			} else if (recv_code == 0) { //if error is found
				++d_msgs; //addm to the detected counter
			} else if (recv_code == 1) {
				++ud_msgs; //else add to the undetected counter;
			}
		}
	}
	
	free(msg);
	//convert everything to percentages
	float w_perc  = ((float)w_msgs  / (float)samples) * 100.0;
	float d_perc  = ((float)d_msgs  / (float)w_msgs)  * 100.0;
	float ud_perc = ((float)ud_msgs / (float)w_msgs)  * 100.0;
	
	printf("Wrong messages: %d out of %d (%.5f%)\n", w_msgs, samples, w_perc);
	printf("Detected wrong messages: %d (%.5f%)\n", d_msgs, d_perc);
	printf("Unetected wrong messages: %d (%.5f%)\n", ud_msgs,  ud_perc);
}