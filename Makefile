SERVER = server

HEAD = unp.h recvfrom_flags.h unprtt.h
#CFLAGS=-I/usr/include -I/path/include
BINDIR = ./bin
OBJDIR = ./objs

SRCS = main.c dg_send_recv.c recvfrom_flags.c rtt.c
OBJS = recvfrom_flags.o rtt.o main.o dg_send_recv.o 


OBJSS = $(OBJDIR)/dg_send_recv.o $(OBJDIR)/recvfrom_flags.o $(OBJDIR)/rtt.o $(OBJDIR)/main.o

main: $(OBJS) $(HEAD)
	echo $(OBJS) $(BINDIR)/$@
	gcc -o $(BINDIR)/$@ $(OBJS) 

#main.o: main.c $(HEAD)
#	gcc -c main.c 

%.o: %.c %.h
	echo $@ $<
	gcc -c $< -o $@  

clean: 
	rm $(OBJDIR)/*.o $(BINDIR)/main *.o
