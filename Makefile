clean:
	rm -f main.exe
main: main.c
	gcc main.c lib/point.c lib/stack.c -o main