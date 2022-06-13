//
// Created by unixity on 6/12/22.
//

#ifndef UNTITLED_FT_DBG_H
#define UNTITLED_FT_DBG_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include "../linenoise/linenoise.h"

typedef struct	s_dbg {
	char	*prog;
	char	*line;
	pid_t	pid;
}	t_dbg;

#endif //UNTITLED_FT_DBG_H
