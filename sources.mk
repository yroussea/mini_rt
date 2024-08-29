MATHS_FILE = inter math
MLX_FILE = manage_mlx on_clic
OBJECT_FILE = add_obj get_scene
RAY_FILE = genering_image init_ray raytracing thread
SHADING_FILE = shading phong



MATHS_DIR = maths
MATHS_PATH = $(addprefix $(MATHS_DIR)/, $(MATHS_FILE))
MLX_DIR = mlx_interaction
MLX_PATH = $(addprefix $(MLX_DIR)/, $(MLX_FILE))
OBJECT_DIR = object
OBJECT_PATH = $(addprefix $(OBJECT_DIR)/, $(OBJECT_FILE))
RAY_DIR = ray
RAY_PATH = $(addprefix $(RAY_DIR)/, $(RAY_FILE))
SHADING_DIR = shading
SHADING_PATH = $(addprefix $(SHADING_DIR)/, $(SHADING_FILE))

ALL_SCRS_FILES = main $(MATHS_PATH) $(MLX_PATH) $(OBJECT_PATH) $(RAY_PATH) $(SHADING_PATH)
SRCS_FILES = $(addsuffix .c, $(ALL_SCRS_FILES))

