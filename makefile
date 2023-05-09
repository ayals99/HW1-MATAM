CC := gcc
CFLAGS := -std=c99 -I/home/mtm/public/2223b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG *.c tool/*.c
TARGET := HackEnrollment
LDFLAGS := -lm
OBJS := main.o HackEnrollment.o Person.o Hacker.o Course.o Node.o IsraeliQueue.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c HackEnrollment.h
	$(CC) $(CFLAGS) -c $< -o $@

HackEnrollment.o: HackEnrollment.c HackEnrollment.h Person.h Course.h IsraeliQueue.h
	$(CC) $(CFLAGS) -c $< -o $@

Person.o: Person.c Person.h Hacker.h
	$(CC) $(CFLAGS) -c $< -o $@

Hacker.o: Hacker.c Hacker.h
	$(CC) $(CFLAGS) -c $< -o $@

Course.o: Course.c Course.h IsraeliQueue.h
	$(CC) $(CFLAGS) -c $< -o $@

Node.o: Node.c Node.h
	$(CC) $(CFLAGS) -c $< -o $@

IsraeliQueue.o: IsraeliQueue.c IsraeliQueue.h Node.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
