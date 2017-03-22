SERVER = server

HEAD = unp.h recvfrom_flags.h unprtt.h do_server.h
#CFLAGS=-I/usr/include -I/path/include
BINDIR = ./bin
OBJDIR = ./objs

SRCS = main.c dg_send_recv.c recvfrom_flags.c rtt.c recvfrom_flags.c
OBJS = do_server.o rtt.o main.o dg_send_recv.o recvfrom_flags.o


OBJSS = $(OBJDIR)/dg_send_recv.o $(OBJDIR)/recvfrom_flags.o $(OBJDIR)/rtt.o $(OBJDIR)/main.o

main: $(OBJS) $(HEAD)
	echo $(OBJS) $(BINDIR)/$@
	gcc -o $(BINDIR)/$@ $(OBJS) 

#main.o: main.c $(HEAD)
#	gcc -c main.c 

#do_server.o: do_server.c recvfrom_flags.o do_server.h
#	gcc -c do_server.c recvfrom_flags.o

%.o: %.c %.h
	echo $@ $<
	gcc -c $< -o $@  

clean: 
	rm $(OBJDIR)/*.o $(BINDIR)/main *.o
