add_library(game game.cpp shader.cpp texture.cpp stb_image.cpp resource_manager.cpp sprite_renderer.cpp game_object.cpp game_level.cpp ball_object.cpp)
target_include_directories(game PUBLIC ../include)
target_link_libraries(game PRIVATE ${OPENGL_LIBRARIES} glfw glad glm random algs)

# add_library(texture texture.cpp)
# target_include_directories(texture PUBLIC ../include)
# target_link_libraries(texture PRIVATE ${OPENGL_LIBRARIES} glfw glad glm)


# add_library(stb_image stb_image.cpp)
# target_include_directories(stb_image PUBLIC ../include)
# target_link_libraries(stb_image PRIVATE ${OPENGL_LIBRARIES} glfw glad glm)

# add_library(resource_manager resource_manager.cpp)
# target_include_directories(resource_manager PUBLIC ../include)
# target_link_libraries(resource_manager PRIVATE ${OPENGL_LIBRARIES} glfw glad glm shader texture stb_image)

# add_library(sprite_renderer sprite_renderer.cpp)
# target_include_directories(sprite_renderer PUBLIC ../include)
# target_link_libraries(sprite_renderer PRIVATE ${OPENGL_LIBRARIES} glfw glad glm)

# add_library(game_object game_object.cpp)
# target_include_directories(game_object PUBLIC ../include)
# target_link_libraries(game_object PRIVATE ${OPENGL_LIBRARIES} glfw glad glm texture sprite_renderer)

# add_library(game_level game_level.cpp)
# target_include_directories(game_level PUBLIC ../include)
# target_link_libraries(game_level PRIVATE ${OPENGL_LIBRARIES} glfw glad glm game_object sprite_renderer resource_manager)

# add_library(ball_object ball_object.cpp)
# target_include_directories(ball_object PUBLIC ../include)
# target_link_libraries(ball_object PRIVATE ${OPENGL_LIBRARIES} glfw glad glm game_object texture)

# add_library(particle_generator particle_generator.cpp)
# target_include_directories(particle_generator PUBLIC ../include)
# target_link_libraries(particle_generator PRIVATE ${OPENGL_LIBRARIES} glfw glad glm shader texture game_object)

# add_library(post_processor post_processor.cpp)
# target_include_directories(post_processor PUBLIC ../include)
# target_link_libraries(post_processor PRIVATE ${OPENGL_LIBRARIES} glfw glad glm shader texture sprite_renderer)

# add_library(game game.cpp)
# target_include_directories(game PUBLIC ../include)
# target_link_libraries(game PRIVATE ${OPENGL_LIBRARIES} glfw glad glm resource_manager sprite_renderer game_object game_level)

# add_library(ball_object_collisions ball_object_collisions.cpp)
# target_include_directories(ball_object_collisions PUBLIC ../include)
# target_link_libraries(ball_object_collisions PRIVATE ${OPENGL_LIBRARIES} glfw glad glm game sprite_renderer resource_manager game_object)