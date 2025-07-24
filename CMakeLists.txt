cmake_minimum_required(VERSION 3.5)
project(communication)

add_library(custom_server SHARED src/custom_server.cpp)
target_link_libraries(custom_server PUBLIC )
target_include_directories(custom_server PUBLIC include )

add_library(custom_client SHARED src/custom_client.cpp)
target_link_libraries(custom_client PUBLIC)
target_include_directories(custom_client PUBLIC include )

add_library(dummy_sock SHARED src/dummy_sock.cpp)
target_link_libraries(dummy_sock PUBLIC ${OpenCV_LIBS})
target_include_directories(dummy_sock PUBLIC include)

add_library(custom_socket SHARED src/custom_socket.cpp)
target_link_libraries(custom_socket PUBLIC custom_client custom_server dummy_sock)
