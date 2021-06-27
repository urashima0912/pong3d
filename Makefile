APP= pong

main: main.c palette.o ball.o
	gcc $^ -o $(APP) -lraylib -pedantic-errors -Wall -g

palette.o: src/palette.c
	gcc $^ -c

ball.o: src/ball.c
	gcc $^ -c

.PHONY: clean
clean:
	rm *.o $(APP)