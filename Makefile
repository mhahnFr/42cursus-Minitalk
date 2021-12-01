# The source files for the client.
C_SRCS = ./client_files/main.c

# The source files for the server.
S_SRCS = ./server_files/main.c

# The object files of the server.
S_OBJS = $(patsubst %.c,%.o,$(S_SRCS))

# The object files of the client.
C_OBJS = $(patsubst %.c,%.o,$(C_SRCS))

# The libft library file.
LIB = ./libft/src/libft.a

# The flags to use during the compilation.
CFLAGS = -Wall -Werror -Wextra -I./server_files -I./ft_printf -I./libft/src

# The flags used during linking.
LDFLAGS = -L./ft_printf -lftprintf -L./libft/src -lft

# The name of the server.
SERV = server

# The name of the client.
CLIE = client

# The ft_printf library file.
PRINT = ./ft_printf/libftprintf.a

# Does everything that is needed for this project.
all: $(SERV) $(CLIE)

# Runs the norm checker on every registered file.
nor:
	norminette $(C_SRCS) $(S_SRCS) $(patsubst %.c,%.h,$(S_SRCS)) $(patsubst %.c,%.h,$(S_SRCS)) | grep :

# Compiles each file individually.
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Does whatever is needed to create the server executable.
$(SERV): $(PRINT) $(LIB) $(S_OBJS)
	$(CC) $(S_OBJS) $(LDFLAGS) -o $(SERV)

# Calls the makefile of the ft_printf.
$(PRINT):
	make -C ./ft_printf all

# Calls the makefile of the libft.
$(LIB):
	make -C ./libft/src all

# Does whatever is needed to create the client executable.
$(CLIE): $(PRINT) $(C_OBJS)
	$(CC) $(LDFLAGS) -o $(CLIE) $(C_OBJS)

# Removes all temporary files.
clean:
	- make -C ./ft_printf clean
	- make -C ./libft/src clean
	- $(RM) $(S_OBJS) $(C_OBJS) *~
	- find . -name *~ -print -delete

# Removes all files created by this makefile.
fclean: clean
	make -C ./ft_printf fclean
	make -C ./libft/src fclean
	- $(RM) $(SERV) $(CLIE)

# Cleans and recompiles the project.
re: fclean all

# A list of the rules that are always dirty.
.PHONY: all clean fclean re nor
