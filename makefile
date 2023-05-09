CC := gcc
CFLAGS := -std=c99 -o HackEnrollment -I/new_home/mtm/public/2223b/ex1 -I/new_home/mtm/public/2223b/ex1/tool -Wall -pedantic-errors -Werror -DNDEBUG
TARGET := HackEnrollment
LDFLAGS := -lm
OBJS := tool/main.o tool/HackEnrollment.o tool/Person.o tool/Hacker.o tool/Course.o Node.o IsraeliQueue.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

tool/main.o: tool/main.c tool/HackEnrollment.h
	$(CC) $(CFLAGS) -c $< -o $@

tool/HackEnrollment.o: tool/HackEnrollment.c tool/HackEnrollment.h tool/Person.h tool/Course.h IsraeliQueue.h
	$(CC) $(CFLAGS) -c $< -o $@

tool/Person.o: tool/Person.c tool/Person.h tool/Hacker.h
	$(CC) $(CFLAGS) -c $< -o $@

tool/Hacker.o: tool/Hacker.c tool/Hacker.h
	$(CC) $(CFLAGS) -c $< -o $@

tool/Course.o: tool/Course.c tool/Course.h IsraeliQueue.h
	$(CC) $(CFLAGS) -c $< -o $@

Node.o: Node.c Node.h
	$(CC) $(CFLAGS) -c $< -o $@

IsraeliQueue.o: IsraeliQueue.c IsraeliQueue.h Node.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
