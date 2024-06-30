default: all

all: t1 t2 t3

t1: ep2-1.c
	gcc -S ep2-1.c -masm=intel -fno-asynchronous-unwind-tables -O0 -g0

t2: ep2-2.c
	gcc -S ep2-2.c -masm=intel -fno-asynchronous-unwind-tables -O0 -g0
