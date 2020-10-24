cmake_minimum_required(VERSION 2.8.3)
project(snake_server CXX)

SET(DUELS_ROOT "/opt/duels" CACHE STRING "Path to duels installation folder")
set(CMAKE_INSTALL_PREFIX ${DUELS_ROOT})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-pthread)
find_package (Threads)

# find ZeroMQ
find_path ( ZMQ_INCLUDE_DIR zmq.h )
find_library ( ZMQ_LIBRARY NAMES zmq )

include_directories(include ${DUELS_ROOT}/include ${ZMQ_INCLUDE_DIR})
add_definitions(-DDUELS_ROOT="${DUELS_ROOT}")

add_executable(snake_server server.cpp)
target_link_libraries(snake_server ${CMAKE_THREAD_LIBS_INIT} ${ZMQ_LIBRARY})

# add whatever is needed to build display executable


# install server
install(TARGETS snake_server DESTINATION bin)

# install gui and its deps
install(FILES snake_gui.py DESTINATION bin
        PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
        
# client headers and templates
install(FILES include/duels/snake/game.h include/duels/snake/msg.h DESTINATION include/duels/snake)
install(FILES client_template/CMakeLists.txt DESTINATION games/snake)
install(FILES client_template/snake.cpp DESTINATION games/snake )
