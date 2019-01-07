NAME = rtv1

SRCS =	main.c					\
		objects.c				\
		events.c				\
		reading.c				\
		reading_utilitaries.c	\
		read_light.c			\
		read_cam.c				\
		read_obj.c				\
		raytracer.c				\
		vector.c				\
		put_pixel.c				\
		new.c					\
		rays.c					\
		quadratic.c				\
		matrix.c				\
		math.c					\
		shading.c				\
		light_impact.c			\
		diffuse.c				\
		read_lim.c				\
		check_lim.c				\
		light_side.c			\
		misc_utils.c			\

SRCO = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

FRMW = -framework OpenGL -framework Appkit

LIB =	./libft/libft.a			\
		./mlx/libmlx.a	\

SRC_PATH = srcs

OBJ_PATH = .obj

SRC = $(addprefix $(SRCS_PATH)/,$(SRCS))

OBJ = $(addprefix $(OBJ_PATH)/,$(SRCO))

INCLUDES = includes

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIB) $(FRMW)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc -c $(FLAGS) -I$(INCLUDES) -o $@ -c $<

$(LIB):
	make -C libft
	make -C mlx

clean:
	rm -rf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	make -C libft clean
	make -C mlx clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all
