cmake_minimum_required (VERSION 2.6)

project (soil)

set (${PROJECT_NAME}_SRC
        "src/image_DXT.c"
        "src/image_helper.c"
        "src/SOIL.c"
        "src/stb_image_aug.c"
)

set (${PROJECT_NAME}_INC
        "src/image_DXT.h"
        "src/image_helper.h"
        "src/SOIL.h"
        "src/stb_image_aug.h"
        "src/stbi_DDS_aug.h"
        "src/stbi_DDS_aug_c.h"
)

source_group ("Source Files" FILES ${${PROJECT_NAME}_SRC})
source_group ("Header Files" FILES ${${PROJECT_NAME}_INC})

add_library (${PROJECT_NAME} ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_INC})