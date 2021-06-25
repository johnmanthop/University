#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 1025

#include "benchmark.h"
#include "bit_ops.h"
#include "sender.h"

void benchmark_menu()
{//helper function to perform benchmark procedure
	unsigned k, samples;
	float ber;
	char *p = malloc(MAX * sizeof(char)); //let's hope P is smaller than 1024
	
	printf("K bit message length:");
	scanf("%u", &k);
	
	printf("P parameter (<= 1024 long & starting and ending with 1):");
	scanf("%s", p);
	
	printf("Bit error rate:");
	scanf("%f", &ber);
	
	printf("Amount of samples:");
	scanf("%d", &samples);
	
	benchmark(k, p, ber, samples);
	free(p);
}

void single_msg_menu()
{//helper function to perform single message transmition
	for (;;) {
		char *buffer = malloc((MAX+1) * sizeof(char)); //alocate 1024 + 1 (for \0) characters
		char *p      = malloc(MAX * sizeof(char));
		float ber;
		
		printf("Binary message up to 1024 bits (q for exit):");
		scanf("%s", buffer);
		
		if (!strcmp(buffer, "q")) {
			free(buffer);
			free(p);
			return; //if the input is q then exit
		}
		
		printf("P parameter:");
		scanf("%s", p);
		
		printf("Bit error rate:");
		scanf("%f", &ber);
		
		create_crc_msg(&buffer, p);
		printf("CRC message: %s\n", buffer);
		
		apply_noise(buffer, ber);
		printf("Transmited message: %s\n", buffer);
		
		char *result = mod(buffer, p);
		if (!result) {
			printf("Problematic data entered...\n\n");
		} else {
			printf("Result modulo: %s\n\n", result);
			free(result);
		}
		free(buffer);
		free(p);
		//be kind and return the memory
	}
}

int main()
{
	char mode;
	
	srand(time(NULL));
	for (;;) {
		printf("---------------------------------------------------\nChoose mode\n1>Benchmark \n2>Single transmition \n3>Exit\n");
		scanf("%c", &mode);
		//simple menu function
		if (mode == '1') {
			benchmark_menu();
		} else if (mode == '2') {
			single_msg_menu();
		} else if (mode == '3') {
			return 0;
		}
		while (getchar() != '\n');
	}
	
	return 0;
}
