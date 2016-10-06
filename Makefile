CC= g++ 

OBJS = main.o    trees/interval_tree.o 	

SRCS = ${OBJS:%.o=%.cpp}
BFILE = rect

.PHONY: all
all: $(BFILE)

$(BFILE): $(OBJS)
	$(CC) -o $(BFILE) $(OBJS)

%.o : %.cpp
	$(CC) -o $*.o -c $*.cpp