CC := gcc
CFLAGS := -std=c99 -I/home/mtm/public/2223b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG
TARGET := HackEnrollment
LDFLAGS := -lm
OBJS := tool/main.o tool/HackEnrollment.o tool/Person.o tool/Hacker.o tool/Course.o tool/Node.o IsraeliQueue.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

tool/main.o: tool/main.c tool/HackEnrollment.h
	$(CC) -c $(CFLAGS) $< -o $@

tool/HackEnrollment.o: tool/HackEnrollment.c tool/HackEnrollment.h IsraeliQueue.h tool/Person.h tool/Course.h
	$(CC) -c $(CFLAGS) $< -o $@

tool/Person.o: tool/Person.c tool/Person.h tool/Node.h tool/Hacker.h tool/Node.h
	$(CC) -c $(CFLAGS) $< -o $@

tool/Hacker.o: tool/Hacker.c tool/Hacker.h
	$(CC) -c $(CFLAGS) $< -o $@

tool/Course.o: tool/Course.c tool/Course.h IsraeliQueue.h
	$(CC) -c $(CFLAGS) $< -o $@

tool/Node.o: tool/Node.c tool/Node.h
	$(CC) -c $(CFLAGS) $< -o $@

IsraeliQueue.o: IsraeliQueue.c IsraeliQueue.h tool/Node.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
