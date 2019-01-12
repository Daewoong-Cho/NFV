include $(HOME)/env.make.linux

MY_INCLUDE = 

MY_NAME_1  = libdavid

CFLAGS  = -I$(INC_DIR) -g
LFLAGS  = -L$(LIB_DIR)

LIBSTL1 = $(MY_NAME_1).a

SECSRC  = lib_ipc.c lib_socket.c lib_errlog.c lib_udp.c lib_fep.c lib_codetbl.c

all:        $(LIBSTL1)

$(LIBSTL1): $(LIBSTL1)(lib_ipc.o lib_socket.o lib_errlog.o lib_udp.o lib_fep.o lib_codetbl.o)
	if [ -s /usr/bin/ranlib ]; then ranlib $(LIBSTL1); fi
        
clear:
clean:
	rm -f *.o *.a *.so
