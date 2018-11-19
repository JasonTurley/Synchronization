# Specify all source files here
SRCS = main.c mutex.c sem.c error.c

# Specify target here (name of executable)
TARG = synch

# Specify compiler, compile flags, and needed libraries
CC   = gcc
OPTS = -std=c11 -Wall -Wextra -Werror -g -O
LIBS = -lrt

# This truncates all .c files in the src list to .o files
OBJS = $(SRCS:.c=.o)

# All is not really needed, but is used to generate the target
all: $(TARG)

# This generates the target executable
$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)

# This is a generic rule for .o files
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARG)
