MATHS_FILE = math pixelisation_size
MLX_FILE = destroy draw event loop setup
OBJECT_FILE = add_obj get_scene plane sphere
RAY_FILE = gen_image init_ray raytracing
PARSING_FILE = parsing



MATHS_DIR = maths
MATHS_PATH = $(addprefix $(MATHS_DIR)/, $(MATHS_FILE))
MLX_DIR = mlx_inter
MLX_PATH = $(addprefix $(MLX_DIR)/, $(MLX_FILE))
OBJECT_DIR = object
OBJECT_PATH = $(addprefix $(OBJECT_DIR)/, $(OBJECT_FILE))
RAY_DIR = ray
RAY_PATH = $(addprefix $(RAY_DIR)/, $(RAY_FILE))
PARSING_DIR = parsing
PARSING_PATH = $(addprefix $(PARSING_DIR)/, $(PARSING_FILE))

ALL_SCRS_FILES = main $(MATHS_PATH) $(MLX_PATH) $(OBJECT_PATH) $(RAY_PATH) $(PARSING_PATH)
SRCS_FILES = $(addsuffix .c, $(ALL_SCRS_FILES))

