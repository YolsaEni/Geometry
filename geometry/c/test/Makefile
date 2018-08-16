_libs = -L. -lasst_geometry_c -lasst_geometry
#stdc++ must have.
LIBS = $(_libs) -lstdc++
INCLUDES    = -I ../include

CC = gcc
CFLAGS      += -Wall -g -O1

SRC := $(wildcard ./*.c)
OBJ := $(SRC:*%.c=*%.o)
MAIN        = demo

.PHONY: clean

all: $(MAIN)
	
$(MAIN): $(OBJ)
#	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $^
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $^ $(LIBS)
	demo

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.exe *~ $(MAIN)

