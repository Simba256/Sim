add_library(algs path_finder.cpp)
target_include_directories(algs PUBLIC ../include)
target_link_libraries(algs PRIVATE ${OPENGL_LIBRARIES} glm game)