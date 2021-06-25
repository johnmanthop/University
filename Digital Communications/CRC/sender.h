#ifndef SENDER_H
#define SENDER_H

void create_crc_msg(char **msg, char *p);
char apply_noise   (char  *msg, float ber);

#endif