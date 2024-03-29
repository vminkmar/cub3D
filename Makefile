NAME			:=	cub3D

CC				:=	cc

RM				:=	rm -f

CFLAGS			:=	-g -Wall -Wextra -Werror #-fsanitize=address

VPATH           :=  src/ src/parser src/draw src/movement src/raycaster

SRC_FILES		:=	main.c check_input.c parser.c utils.c linked_list_utils.c init.c free.c print_errors.c\
					linked_list.c check_map.c get_textures_and_map.c get_textures_and_map_utils.c edit_textures.c color.c syntax_check.c\
					color_utils.c linked_list_to_array.c raycast.c raycast2.c draw_utils.c movement.c directions.c textures.c doors.c\
					minimap.c colors_check.c free_utils.c syntax_check_utils.c linekd_list_to_array_utils.c load_pngs.c\
					compare_textures.c trim_textures.c

HEADER			:=	-I./include/

LIBMLX			:=	include/MLX42

LMLX			:=	include/MLX42/build/libmlx42.a

ODIR			:=	obj

LINK_FLAGS		:=	

OBJS			:=	$(SRC_FILES:%.c=$(ODIR)/%.o)

LIBFT			:=	include/Libft

LFT				:=	include/Libft/libft.a

LIB				:= $(LIBDIR)/cub3D.a

LFLAGS			:= $(LFT) $(LMLX) -I include

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    LFLAGS += -ldl -lglfw -pthread -lm
endif

ifeq ($(UNAME_S),Darwin)
    LFLAGS += -lglfw -L "$(HOME)/.brew/opt/glfw/lib/"
endif


all: libft $(LMLX) $(NAME)

libft: $(LFT)

$(LFT):
	@git submodule init
	@git submodule update
	@make -C ./include/Libft

$(LMLX): $(LIBMLX)
	@git submodule init include/MLX42
	@git submodule update include/MLX42
	@cd include/MLX42 && pwd && cmake -B build && cmake --build build -j4

$(NAME): $(LMLX) $(OBJS) $(LFT)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LINK_FLAGS) -o $@

$(ODIR)/%.o: %.c | $(ODIR)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(ODIR):
	mkdir $(ODIR)

norm:
	norminette src/ include/cub3D.h

clean:
	$(MAKE) -C $(LIBFT) clean
	$(RM) $(OBJS) $(BONUS_OBJS) $(LIB)


fclean: clean
	$(RM) $(NAME) $(NAME_BONUS) $(LFT)

re: fclean all

.PHONY: all clean fclean re bonus libft


LSAN			=	LeakSanitizer
LSANLIB			=	/LeakSanitizer/liblsan.a


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
