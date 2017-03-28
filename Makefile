SERVER = server

HEAD = unp.h recvfrom_flags.h unprtt.h do_server.h do_client.h token_bucket.h
#CFLAGS=-I/usr/include -I/path/include
BINDIR = ./bin
OBJDIR = ./objs

SRCS = main.c dg_send_recv.c rtt.c recvfrom_flags.c do_client.c \
	do_server.c error_check.c

OBJS = main.o do_client.o do_server.o \
	dg_send_recv.o recvfrom_flags.o rtt.o error_check.o\
	token_bucket.o token_bucket_map.o

main: $(OBJS) $(HEAD)
	echo $(OBJS) $(BINDIR)/$@
	g++ -o $(BINDIR)/$@ $(OBJS) 


#main.o: main.c $(HEAD)
#	gcc -c main.c 

#do_server.o: do_server.c recvfrom_flags.o do_server.h
#	gcc -c do_server.c recvfrom_flags.o

token_bucket_map.o: token_bucket_map.cpp token_bucket.h
	g++ -o $@ -c $<
%.o: %.c 
	@echo $@ $< "gcc"
	g++ -c $< -o $@  

clean: 
	rm $(OBJDIR)/*.o $(BINDIR)/main *.o
