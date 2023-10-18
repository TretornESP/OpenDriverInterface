#ifndef _BASIC_H
#define _BASIC_H

#include "../../../odi/types.h"

void init_device(u32);
void exit_device(u32);

char * read_device(u32, u32, u32);
void write_device(u32, u32, u32, char *);

char * do_cool_things();
char * do_dumb_things();

#endif