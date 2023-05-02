NAME			:=	cub3D

# NAME_BONUS		:= 	cub3D_bonus

CC				:=	cc

RM				:=	rm -f

CFLAGS			:=	-g -Wall -Wextra -Werror

VPATH			:=	src/

SRC_FILES		:=	draw.c #main.c check_input.c parser.c utils.c parser_utils.c free_stuff.c 

HEADER			:=	-I./include/

LIBMLX			:=	include/MLX42

LMLX			:=	include/MLX42/build/libmlx42.a

ODIR			:=	obj

LINK_FLAGS		:=

OBJS			:=	$(SRC_FILES:%.c=$(ODIR)/%.o)

# BONUS_OBJS		:=	$(BONUS_FILES:%.c=$(ODIR)/%.o)

LIBFT			:=	include/Libft

LFT				:=	include/Libft/libft.a

LIBDIR			:= lib

LIB				:= $(LIBDIR)/cub3D.a

LFLAGS			:=	$(LFT) $(LMLX) -I include -lglfw -L "$(HOME)/.brew/opt/glfw/lib/"

all: $(LFT) $(LMLX) $(NAME) #$(NAME_BONUS)

$(LFT):	$(LIBFT)
	@git submodule init Libft
	@git submodule update Libft
	@cd include/Libft && make && make clean

$(LMLX): $(LIBMLX)
	@git submodule init MLX42
	@git submodule update MLX42
	@cd include/MLX42 && cmake -B build && cmake --build build -j4

$(NAME): $(LMLX) $(OBJS) $(LFT)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LINK_FLAGS) -o $@

# $(NAME_BONUS): $(BONUS_OBJS) $(LMLX) c $(LFT) 
# 	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LFLAGS) -o $@

$(ODIR)/%.o: %.c | $(ODIR)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(ODIR):
	mkdir $(ODIR)

test: $(TEST_FILES)
	@ar -rcs lib/libtest.a $(OBJS) include/libft/*.o
	@cd tests && $(MAKE) run

test2:
	@echo $(OBJS)

norm:
	norminette src/ include/

clean:
	$(MAKE) -C $(LIBFT) clean
	$(RM) $(OBJS) $(BONUS_OBJS) $(LIB) lib/libtest.a
	@cd tests && $(MAKE) clean


fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus


LSAN			=	LeakSanitizer
LSANLIB			=	/LeakSanitizer/liblsan.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
#	LINK_FLAGS += -ltinfo
	LSANLFLAGS := -rdynamic -LLeakSanitizer -llsan -ldl -lstdc++
endif
ifeq ($(UNAME_S),Darwin)
	LSANLFLAGS := -LLeakSanitizer -llsan -lc++
endif

lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK_FLAGS += $(LSANLFLAGS)
lsan: fclean $(LSANLIB)
lsan: all
$(LSAN):
	git clone https://github.com/mhahnFr/LeakSanitizer.git
$(LSANLIB): $(LSAN)
	@$(MAKE) -C LeakSanitizer

$(DOWNLOADFOLDER):
	mkdir -p $(DOWNLOADFOLDER)
	curl -s https://ftp.gnu.org/gnu/readline/readline-8.1.2.tar.gz --output $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz
	tar xfz $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz -C $(DOWNLOADFOLDER)
	cd $(DOWNLOADFOLDER)/readline-8.1.2; ./configure --prefix=$(PWD)/$(DOWNLOADFOLDER)/readline_out; cd ../../
	$(MAKE) -C $(DOWNLOADFOLDER)/readline-8.1.2
	$(MAKE) install -C $(DOWNLOADFOLDER)/readline-8.1.2
