#include <stdio.h>
#include "ft_dbg.h"

int main(int argc, char **argv) {
	t_dbg	dbg;
	pid_t	pid;

    (void)argc;

	dbg.prog = argv[1];
	pid = fork();
	if (pid == 0) {
		ptrace(pid, 0, NULL, NULL);
		execl(dbg.prog, argv[2], NULL);
	}
	if (pid >= 1){
		dbg.pid = pid;
		printf("pid: %i", pid);
		dbg.line = NULL;
		while((dbg.line = linenoise("hello> ")) != NULL) {
			printf("You wrote: %s\n", dbg.line);
			linenoiseHistoryAdd(dbg.line);
			linenoiseFree(dbg.line);
        }
	}
	perror("ftdbg: failed to fork a process");
	return -1;
}
