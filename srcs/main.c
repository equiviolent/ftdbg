#include <stdio.h>
#include "ft_dbg.h"

void	continue_execution(t_dbg *dbg) {
	int wait_status;

#if defined __APPLE__
	ptrace(PT_CONTINUE, dbg->pid, NULL, 0);
#elif __linux__
	ptrace(PTRACE_CONT, dbg->pid, NULL, NULL);
#endif
	
	waitpid(dbg->pid, &wait_status, 0);
}

void	handleLine(t_dbg *dbg) {
	char	**nline;

	nline = ft_split(dbg->line, ' ');
	if (!(strncmp(nline[0], "continue", 9)) || !(strncmp(nline[0], "c", 2)))
		continue_execution(dbg);
	else
		printf("ftdbg: unknown command\n");
}

void	loopRun(t_dbg *dbg) {
	while ((dbg->line = linenoise("ftdbg> ")) != NULL) {
		handleLine(dbg);
		linenoiseHistoryAdd(dbg->line);
		linenoiseFree(dbg->line);
	}
}

int main(int argc, char **argv) {
	t_dbg	dbg;

    (void)argc;

	dbg.prog = argv[1];
	dbg.pid = fork();
	if (dbg.pid < 0) {
		perror("ftdbg: failed to fork a process");
	}
	if (dbg.pid == 0) {
		#if defined __APPLE__
			ptrace(PT_TRACE_ME, 0, NULL, 0);
		#elif __linux__
			ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		#endif
			execl(dbg.prog, dbg.prog, NULL);
	}
	
	dbg.line = NULL;
	loopRun(&dbg);
	return -1;
}
