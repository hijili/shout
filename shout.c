#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_CONFIG "/etc/shout/shout.conf"
#define BUFMAX 256

typedef struct shouter {
	int num_exclamation;
	int num_cycles;
	char word[BUFMAX];
} shouter;

void parse_config (shouter *sh, const char *conffile) {
	assert(conffile != NULL);
	FILE *fp;

	if ((fp = fopen(conffile, "r")) == NULL) {
		perror("file open failed");
		exit(EXIT_FAILURE);
	}

	char line[BUFMAX] = {};
	while (fgets(line, BUFMAX, fp) != NULL) {
		if (line[0] == '#') { continue; }
		char key[BUFMAX] = {};
		char value[BUFMAX] = {};
		int ret = sscanf(line, "%255[^=]=%255s", key, value); // umm... :(
		if (ret != 2) {
			printf("[WARN] unexpected line: %s\n", line);
			continue;
		}
		if (strcmp(key, "WORD") == 0)
			strcpy(sh->word, value);
		else if (strcmp(key, "EXCLAMATION") == 0)
			sh->num_exclamation = atoi(value); // XXX: should use strtol
		else if (strcmp(key, "CYCLES") == 0)
			sh->num_cycles = atoi(value);
		else
			printf("[WARN] unexpected config: %s=%s\n", key, value);
	}
	fclose(fp);
}

void dump(shouter sh) {
	printf("---------\n");
	printf("word: %s\n", sh.word);
	printf("num_exclamation: %d\n", sh.num_exclamation);
	printf("num_cycles: %d\n", sh.num_cycles);
	printf("---------\n");
}

void shout(shouter sh) {
	char cycle_char;

	// TBD: multibyte char...
	char vowel[5] = {'a', 'i', 'u', 'e', 'o'};
	char *last_vowel = NULL;
	for (int i = 0; i < 5; i++) {
		char c = vowel[i];
		char *p = strrchr(sh.word, c);
		if (p != NULL && (last_vowel == NULL || last_vowel < p))
			last_vowel = p;
	}
	if (last_vowel == NULL)
		// If sh.word doesn't include vowel, last char is set to last_vowel.
		last_vowel = &(sh.word[strlen(sh.word)-1]);

	char *p = sh.word;
	while (*p != '\0') {
		if (p == last_vowel)
			for (int i = 0; i < sh.num_cycles; i++)
				printf("%c", *p);
		else
			printf("%c", *p);
		p++;
	}
	for (int i = 0; i < sh.num_exclamation; i++)
		printf("%c", '!');
	printf("\n");
}

int main(int argc, char **argv) {
	char *config = DEFAULT_CONFIG;

	const struct option longopts[] = {
		{  "config", required_argument,     0, 'c' },
		{         0,                 0,     0,  0  },
	};
	const char* optstring = "c:" ;
	int longindex = 0;
	int c;
	while ((c = getopt_long(argc, argv, optstring, longopts, &longindex)) != -1) {
		switch (c) {
		case 'c':
			config = optarg;
			break;
		default:
			return 1;
		}
	}

	shouter sh = { 5, 5, "shout" };
	parse_config(&sh, config);

	// prior stdin
	if (optind < argc) {
		strncpy(sh.word, argv[optind], BUFMAX-1);
	}
	shout(sh);
}
