#ifndef _MYFATFS_H_
#define _MYFATFS_H_

#include "stdbool.h"

bool mountSDCard(void);

bool f_file_exists(const char* path);

#endif
