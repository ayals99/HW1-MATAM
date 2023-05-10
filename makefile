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

HackEnrollment.o: tool/HackEnrollment.c tool/HackEnrollment.h tool/Person.h tools/Course.h
	$(CC) $(CFLAGS) -c $<

Person.o: tools/Person.c tools/Person.h tools/Hacker.h tools/Hacker.c  tools/Node.h tools/Node.c
	$(CC) $(CFLAGS) -c $<

Hacker.o: tools/Hacker.c tools/Hacker.h
	$(CC) $(CFLAGS) -c $<

Course.o: tools/Course.c tools/Course.h IsraeliQueue.h IsraeliQueue.c
	$(CC) $(CFLAGS) -c $<

Node.o: tools/Node.c tools/Node.h
	$(CC) $(CFLAGS) -c $<

IsraeliQueue.o: tools/IsraeliQueue.c tools/IsraeliQueue.h tools/Node.h tools/Node.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS)
