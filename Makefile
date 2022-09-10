program_NAME	:=	bin/main
program_SRCS	:=	$(wildcard src/*.c)
program_OBJS	:=	${program_SRCS:.c=.o}
program_INCLUDES	:=	include/ /usr/include

FLAGS	:=	$(foreach dir, $(program_INCLUDES), -I$(dir))

.PHONY: all clean distclean

all:	$(program_NAME)

$(program_NAME): $(program_SRCS)
	gcc ${program_SRCS} -o $(program_NAME) $(FLAGS) -g -Wall -Wextra

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)
	