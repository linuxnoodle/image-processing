PROJECT:=bad-apple

CC:=g++
LFLAGS=-ansi -O2 -std=c++17
UNAME:=$(shell uname)
ifeq ($(UNAME), Linux)
	LFLAGS+= -lcurses
endif

OBJDIR:=objects
OBJ:=$(addprefix $(OBJDIR)/,main.o lodepng.o imageconverting.o)

$(PROJECT): $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $@

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CC) $(LFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: all
all: clean $(PROJECT)

.PHONY: clean
clean:
	rm -r objects bad-apple
