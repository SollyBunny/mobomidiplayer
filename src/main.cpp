#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <tml/tml.h>
#include <beep/beep.h>

const int NOTE_LEN = 100;

static float key2freq(char key) {
	return 440.0f * pow(2, (((float)key - 69.0f) / 12.0f));
}

static void sleep(float ms) {
	timespec time;
	time.tv_sec = static_cast<time_t>(ms / 1000.0f);
	time.tv_nsec = static_cast<long>((ms - time.tv_sec * 1000.0f) * 1e6);
	nanosleep(&time, nullptr);
}

static bool doNote(const char note, unsigned time) {
	static unsigned lastTime = 0.0f;
	static char lastNote = 0;
	int delta = (int)time - (int)lastTime;
	if (delta < 5) {
		time = lastTime + 5;
		delta = 5;
	}
	if (!beepStart(key2freq(lastNote)))
		return false;
	if (delta < NOTE_LEN) {
		sleep(delta);
		if (!beepStop())
			return false;
	} else {
		beepStart(key2freq(lastNote));
		sleep(NOTE_LEN);
		if (!beepStop())
			return false;
		sleep(delta - NOTE_LEN);
	}
	lastNote = note;
	lastTime = time;
	return true;
}

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		printf("usage: %s [filename.mid]\n", argv[0]);
		exit(1);
	}
	tml_message* midi = tml_load_filename(argv[1]);
	if (!midi) {
		perror("open");
		exit(1);
	}
	if (!beepSetup())
		exit(1);
	printf("Playing %s\n", argv[1]);
	while (midi) {
		if (midi->type == TML_NOTE_ON && midi->velocity > 0)
			if (!doNote(midi->key, midi->time))
				break;
		midi = midi->next;
	}
	doNote(0, 0);
	if (!beepDestroy())
		exit(1);
	return 0;
}