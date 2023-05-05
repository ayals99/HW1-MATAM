
CC = gcc
CFLAGS = -std=c99 -I/home/mtm/public/2223b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG
LDFLAGS = -lm

TARGET = program
# Compiler options
CC = gcc
CFLAGS = -std=c99 -I. -I/home/mtm/public/2223b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG

# Linker options
LDLIBS = -lm

# Source files
SRCS = main.c HackEnrollment.c Person.c Courses.c Hacker.c Node.c IsraeliQueue.c

    main.o: main.c HackEnrollment.h
	    	

    HackEnrollemnt.o: HackEnrollment.c Person.h Course.h



#			HackEnrollment.h includes Person.h and Courses.h
#				Person.h includes Hacker.h and Node.h
#					IsraeliQueue.h includes Node.h
#