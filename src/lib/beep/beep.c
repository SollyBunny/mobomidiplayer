#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <linux/kd.h>

#include "beep.h"

#define CONSOLE_PATH "/dev/console"

static int consoleFd = -1;

static void sighandle(int sig) {
	(void)sig;
	exit(beepDestroy() ? 0 : 1);
}

bool beepSetup() {
	signal(SIGINT, sighandle);
	signal(SIGTERM, sighandle);
	signal(SIGQUIT, sighandle);
	consoleFd = open(CONSOLE_PATH, O_WRONLY);
	if (consoleFd == -1) {
		perror("open");
		return false;
	}
	return true;
}

bool beepDestroy() {
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (consoleFd != -1) {
		bool failed = false;
		if (ioctl(consoleFd, KIOCSOUND, 0) < 0) {
			perror("ioctl KIOCSOUND stop");
			failed = true;
		}
		if (close(consoleFd) < 0) {
			consoleFd = -1;
			perror("close");
			failed = true;
		}
		consoleFd = -1;
		if (failed)
			return false;
	}
	return true;
}

bool beepStart(float freq) {
	int tone = 1193180.0f / freq;
	if (ioctl(consoleFd, KIOCSOUND, tone) < 0) {
		perror("ioctl KIOCSOUND stop");
		return false;
	}
	return true;
}

bool beepStop() {
	if (ioctl(consoleFd, KIOCSOUND, 0) < 0) {
		perror("ioctl");
		return false;
	}
	return true;
}
