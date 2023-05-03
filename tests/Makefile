CC				:=	cc
FILES			:=	valid_map_tests.c
RM				:=	rm -f
LDFLAGS			:=  -lcriterion -L.. -L "/Users/vminkmar/.brew/lib" ../lib/libtest.a
TESTS			:=	$(FILES:%.c=%.o)
%.o: %.c
	$(CC) $< -o $@ $(LDFLAGS) ../include/MLX42/build/libmlx42.a -lglfw -L "/Users/vminkmar/.brew/opt/glfw/lib/"
all: $(TESTS)
run: all
	for test in $(TESTS); do ./$$test; done
clean:
	$(RM) $(TESTS)
