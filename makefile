
CC = gcc
CFLAGS = -std=c99 -I/home/mtm/public/2223b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG
LDFLAGS = -lm

TARGET = program
# Compiler options
CC = gcc
CFLAGS = -std=c99 -I. -I/home/mtm/public/2223b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG

#OBJECTS
OBJS = main.o HackEnrollment.o Person.o Hacker.o Course.o Node.o IsraeliQueue.o

# Linker options
LDFLAGS = -lm

# EXECUTE
EXEC = program

# Source files
SRCS = main.c HackEnrollment.c Person.c Courses.c Hacker.c Node.c IsraeliQueue.c

    $(TARGET): $(OBJS)
	    	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET)

    main.o: main.c HackEnrollment.h
	    	$(CC) $(CFLAGS) -c $< -o $@

    HackEnrollemnt.o: HackEnrollment.c Person.h Course.h
			    	$(CC) $(CFLAGS) $(LDLIBS) -c $@

    Person.o: Person.c Hacker.h Node.h
			    $(CC) $(CFLAGS) $(LDLIBS) -c $@

    Hacker.o: Hacker.c
			    $(CC) $(CFLAGS) $(LDLIBS) -c $@

	Course.o : Course.c
			    $(CC) $(CFLAGS) $(LDLIBS) -c $@

    IsraeliQueue.o : IsraeliQueue.c Node.h
			    $(CC) $(CFLAGS) $(LDLIBS) -c $@

	Node.o : Node.c
			    $(CC) $(CFLAGS) $(LDLIBS) -c $@

# include tree:
#			HackEnrollment.h includes Person.h and Courses.h
#				Person.h includes Hacker.h and Node.h
#					IsraeliQueue.h includes Node.h
#

## Compiler options:
 #CC = gcc
 #CFLAGS = -std=c99 -I. -I/home/mtm/public/2223b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG
 #
 ## Linker options
 #LDLIBS = -lm
 #
 ## Source files
 #SRCS = main.c HackEnrollment.c Person.c Courses.c Hacker.c Node.c IsraeliQueue.c
 #
 ## Object files
 #OBJS = $(SRCS:.c=.o)
 #
 ## Target executable
 #TARGET = program
 #
 #all: $(TARGET)
 #
 #$(TARGET): $(OBJS)
 #	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)
 #
 ## Compile source files to object files
 #%.o: %.c
 #	$(CC) $(CFLAGS) -c $< -o $@
 #
 ## Dependencies
 #main.o: main.c HackEnrollment.h
 #HackEnrollment.o: HackEnrollment.c Person.h Course.h
 #Person.o: Person.c Hacker.h Node.h
 #Courses.o: Courses.c
 #Hacker.o: Hacker.c
 #Node.o: Node.c
 #IsraeliQueue.o: IsraeliQueue.c Node.h
 #
 ## Clean
 #clean:
 #	rm -f $(OBJS) $(TARGET)

 #Certainly! Here is a step-by-step explanation of the makefile:
 #
 #1. `CC = gcc` specifies that the `gcc` compiler should be used to compile the source code.
 #2. `CFLAGS = -std=c99 -I. -I/home/mtm/public/2223b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG` sets the compiler flags to include C99 standard, include directories, and enable various warning and error flags.
 #3. `LDLIBS = -lm` sets the linker flag to include the math library (`-lm`).
 #4. `SRCS = main.c HackEnrollment.c Person.c Courses.c Hacker.c Node.c IsraeliQueue.c` sets the names of the source files to be compiled.
 #5. `OBJS = $(SRCS:.c=.o)` creates a variable `OBJS` which is the list of object files that will be generated by compiling each source file in `SRCS`.
 #6. `TARGET = program` sets the name of the executable to be generated.
 #7. `all: $(TARGET)` defines a target called `all`, which depends on the `$(TARGET)` target. Running `make all` will build the `$(TARGET)` executable.
 #8. `$(TARGET): $(OBJS)` defines a rule for building the `$(TARGET)` executable, which depends on all the object files in `$(OBJS)`.
 #9. `$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)` is the command to link all the object files into the executable `$(TARGET)`.
 #10. `%.o: %.c` is a pattern rule that says that any object file with a `.o` extension depends on a source file with the same name and a `.c` extension.
 #11. `$(CC) $(CFLAGS) -c $< -o $@` is the command to compile a source file to an object file. `$<` is an automatic variable that holds the name of the source file, and `$@` is an automatic variable that holds the name of the object file.
 #12. `main.o: main.c HackEnrollment.h` and similar lines define dependencies for each object file. These dependencies ensure that if any of the source files change, only the necessary object files will be recompiled.
 #13. `clean: rm -f $(OBJS) $(TARGET)` defines a `clean` target that removes all object files and the executable.