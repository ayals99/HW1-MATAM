CC := gcc
CFLAGS := -std=c99 HackEnrollment -I/home/mtm/public/2223b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG *.c tool/*.c
TARGET := HackEnrollment
LDFLAGS := -lm
OBJS := main.o HackEnrollment.o Person.o Hacker.o Course.o Node.o IsraeliQueue.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: tool/main.c  tool/HackEnrollment.h
	$(CC) $(CFLAGS) -c $<

HackEnrollment.o: tool/HackEnrollment.c tool/HackEnrollment.h IsraeliQueue.h tool/Person.h tool/Node.h tool/Hacker.h\
 tool/Course.h
	$(CC) $(CFLAGS) -c $<

Person.o: tool/Person.c tool/Person.h tool/Node.h tool/Hacker.h tool/Node.h
	$(CC) $(CFLAGS) -c $<

Hacker.o: tool/Hacker.c tool/Hacker.h
	$(CC) $(CFLAGS) -c $<

Course.o: tool/Course.c tool/Course.h IsraeliQueue.h IsraeliQueue.c
	$(CC) $(CFLAGS) -c $<

Node.o: tool/Node.c tool/Node.h
	$(CC) $(CFLAGS) -c $<

IsraeliQueue.o: IsraeliQueue.c IsraeliQueue.h tool/Node.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS)
