
bin: main.c
	gcc main.c -o $@

.PHONY: run clean

run:
	./bin

clean:
	rm bin
