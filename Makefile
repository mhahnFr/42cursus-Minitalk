# The source files for the client.
C_SRCS =

# The source files for the server.
S_SRCS = 

# The object files of the server.
S_OBJS = $(patsubst %.c,%.o,$(S_SRCS))

# The object files of the client.
C_OBJS = $(patsubst %.c,%.o,$(C_SRCS))

# The flags to use during the compilation.
CFLAGS = -Wall -Werror -Wextra -g

# The flags to use during linking.
LDFLAGS = 

# The name of the server.
SERV = server

# The name of the client.
CLIE = client

# Does everything that is needed for this project.
all: $(SERV) $(CLIE)

# Runs the norm checker on every registered file.
nor:
	norminette $(C_SRCS) $(S_SRCS) $(patsubst %.c,%.h,$(S_SRCS)) $(patsubst %.c,%.h,$(S_SRCS)) | grep :

# Compiles each file individually.
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Does whatever is needed to create the server executable.
$(SERV): $(S_OBJS)
	$(CC) $(LDFLAGS) -o $(SERV) $(S_OBJS)

# Does whatever is needed to create the client executable.
$(CLIE): $(C_OBJS)
	$(CC) $(LDFLAGS) -o $(CLIE) $(C_OBJS)

# Removes all temporary files.
clean:
	- $(RM) $(OBJS) *~
	- find . -name *~ -print -delete

# Removes all files created by this makefile.
fclean: clean

# Cleans and recompiles the project.
re: fclean all

# A list of the rules that are always dirty.
.PHONY: all clean fclean re nor
