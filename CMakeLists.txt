cmake_minimum_required(VERSION 3.0.0)
project(translation-service VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(translation-service main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CURL_ROOT_DIR /usr/local/Cellar/curl/7.75.0/include/)
find_package(curl REQUIRED)
message(STATUS ">>> CURL Dir Found: " ${CURL_INCLUDE_DIR})
