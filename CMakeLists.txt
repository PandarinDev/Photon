cmake_minimum_required(VERSION 3.12)
project(Photon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

file(GLOB_RECURSE PHOTON_SOURCES "Source/*.cpp")
file(GLOB_RECURSE PHOTON_HEADERS "Include/*.h")

add_executable(Photon ${PHOTON_SOURCES} ${PHOTON_HEADERS})
target_include_directories(Photon PUBLIC "Include")
target_link_libraries(Photon Threads::Threads)