find_package(OpenGL REQUIRED)
add_executable(program program.cpp)
target_link_libraries(program PRIVATE ${OPENGL_LIBRARIES} glfw glad game glm algs)

# Specify the source directory and the destination directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}")

# # Use file(GLOB ...) to find all image files in the source directory
# file(GLOB IMAGE_FILES "${SOURCE_DIR}/*.jpg" "${SOURCE_DIR}/*.png")

# # Copy each image file found to the destination directory
# foreach(IMAGE_FILE ${IMAGE_FILES})
#     file(COPY ${IMAGE_FILE} DESTINATION ${DEST_DIR})
# endforeach()

# Copy the shader folder to the destination directory
file(COPY "${SOURCE_DIR}/shaders" DESTINATION "${DEST_DIR}")

file(COPY "${SOURCE_DIR}/textures" DESTINATION "${DEST_DIR}")

file(COPY "${SOURCE_DIR}/levels" DESTINATION "${DEST_DIR}")


