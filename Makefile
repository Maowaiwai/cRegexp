CC = gcc
RM = rm
MKDIR = mkdir

DIR_OBJS = objs
DIR_EXES = out

DIRS := $(DIR_OBJS) $(DIR_EXES)

EXE = cRegexp
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(DIR_OBJS)/,$(OBJS))
EXE := $(addprefix $(DIR_EXES)/,$(EXE))

all : $(DIRS) $(EXE)
$(DIRS) :
	$(MKDIR) $@
$(EXE) : $(OBJS)
	$(CC) -o $@ $^
$(DIR_OBJS)/%.o : %.c
	$(CC) -o $@ -c $^


.PHONY:clean
clean :
	$(RM) $(DIRS) $(EXE) -rf




