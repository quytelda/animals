#ifndef __GLOBAL_H
#define __GLOBAL_H

#define SGN(x) ((x >= 0) ? 1 : -1)
#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x > y) ? y : x)

#define RVAR(v) ((rand() % (2*v + 1)) - v)

#define KNRM "\x1B[0m"
#define KBLU "\x1B[34m"
#define KGRN "\x1B[32m"
#define KRED "\x1B[91m"
#define KYLW "\x1B[93m"
#define KWHT "\x1B[97m"
#define KGRY "\x1B[37m"

#define BG_NRM "\x1B[49m"
#define BG_RED "\x1B[41m"
#define BG_GRN "\x1B[42m"
#define BG_BLU "\x1B[44m"
#define BG_GRY "\x1B[100m"

#endif
