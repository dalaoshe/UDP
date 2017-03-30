SERVER = server

HEAD = unp.h recvfrom_flags.h unprtt.h do_server.h do_client.h token_bucket.h
#CFLAGS=-I/usr/include -I/path/include
BINDIR = ./bin
OBJDIR = ./objs

SRCS = main.c dg_send_recv.c rtt.c recvfrom_flags.c do_client.c \
	do_server.c error_check.c UDPThread.c

OBJS = main.o do_client.o do_server.o \
	client_send_recv.o recvfrom_flags.o rtt.o error_check.o\
	token_bucket.o token_bucket_map.o server_util.o UDPThread.o

main: $(OBJS) $(HEAD)
	echo $(OBJS) $(BINDIR)/$@
	g++ -o $(BINDIR)/$@ $(OBJS) -lpthread


%.o: %.cpp 
	@echo $@ $< "gcc"
	g++ -c $< -o $@  

clean: 
	rm $(OBJDIR)/*.o $(BINDIR)/main *.o
