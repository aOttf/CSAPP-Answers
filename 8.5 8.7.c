#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

unsigned snooze(unsigned secs) {
	unsigned rm = sleep(secs);
	unsigned actu = secs - rm;

	printf("Slept for %u of %u seconds.\n", actu, secs);
	return rm;
}

void sigint_handler(int sig) {
	return;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <secs>\n", argv[0]);
		exit(0);
	}

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		unix_error("signal error\n");
	(void) snooze(atoi(argv[1]));

	exit(0);
}
