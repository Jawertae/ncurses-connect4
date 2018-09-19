comp = g++
objs = main.cpp
flags = -w
lflags = -lncurses
name = connect4

ALL:$(objs)
	$(comp) $(objs) $(flags) $(lflags) -o $(name)
