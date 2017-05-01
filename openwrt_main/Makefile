.PHONY: clean

CC = mipsel-openwrt-linux-gcc
RM = rm
OBJ = car_main
OBJS = main.o serialport.o

$(OBJ):$(OBJS)
	$(CC) -o $@ $^
%.o: %.c
	$(CC) -c $^ -o $@
clean:
	@$(RM) $(OBJS)
