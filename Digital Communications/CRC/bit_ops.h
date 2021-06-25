#ifndef BIT_OPS_H
#define BIT_OPS_H

void shift_left (char **bitstr, size_t amount);
void shift_lefto(char  *bitstr, size_t amount);
void shift_right(char  *bitstr, size_t amount);

char *mod (char *divident, char *divisor);
char  zero(char *buffer);

#endif