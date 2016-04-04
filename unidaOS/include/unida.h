#ifndef __UNIDA_H__
#define __UNIDA_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>

#include "console.h"
#include "ds2_cpu.h"
#include "ds2_cpuclock.h"
#include "ds2_dma.h"
#include "ds2_excpt.h"
#include "ds2_fcntl.h"
#include "ds2_unistd.h"
#include "ds2_malloc.h"
#include "ds2_mmc_api.h"
#include "ds2_timer.h"
#include "ds2_types.h"
#include "ds2io.h"
#include "fs_api.h"
#include "partition.h"

/*
 *    Color Specs
 */
#define CS              ((r / 8), (g / 8), (b / 8))
#define BACK_COLOR		RGB15(4, 2, 6)
#define BLACK_COLOR		RGB15(0, 0, 0)
#define WHITE_COLOR		RGB15(31, 31, 31)
#define LIGHT_BLUE		RGB15(1, 18, 26)
#define YELLOW			RGB15(30, 31, 0)

/*
 *    Text Specs
 */
#define MAX_STRLEN      32
#define MAX_LINES       24+1

#endif //__UNIDA_H__
