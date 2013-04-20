.PHONY: clean build
build:
	gcc -c -o snd2.o snd2.c
	gcc -o use_snd use_snd.c snd2.o -lasound -lpthread
clean:
	rm -f *.o *~ use_snd

