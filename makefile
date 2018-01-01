.PHONY: clean

shout: shout.c
	gcc -std=c99 shout.c -o shout

clean:
	rm -f shout *~
