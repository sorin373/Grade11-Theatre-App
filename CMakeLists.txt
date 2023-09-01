cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(Grade11-Theatre-App
    VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if(NOT CMAKE_CXX_COMPILE_FEATURES)
    message(FATAL_ERROR "The compiler does not support C++17.")
endif()

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_executable(${PROJECT_NAME}
    "src/main.cpp"
)

configure_file(${CMAKE_SOURCE_DIR}/src/db_files/actor.txt ${CMAKE_BINARY_DIR}/Release/db_files/actor.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/db_files/bilet.txt ${CMAKE_BINARY_DIR}/Release/db_files/bilet.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/db_files/personaj.txt ${CMAKE_BINARY_DIR}/Release/db_files/personaj.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/db_files/personal.txt ${CMAKE_BINARY_DIR}/Release/db_files/personal.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/db_files/piesa_veche.txt ${CMAKE_BINARY_DIR}/Release/db_files/piesa_veche.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/db_files/piesa.txt ${CMAKE_BINARY_DIR}/Release/db_files/piesa.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/db_files/sala.txt ${CMAKE_BINARY_DIR}/Release/db_files/sala.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/db_files/spectator_vechi.txt ${CMAKE_BINARY_DIR}/Release/db_files/spectator_vechi.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/db_files/spectator.txt ${CMAKE_BINARY_DIR}/Release/db_files/spectator.txt COPYONLY)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/db_files/ DESTINATION bin/db_files FILES_MATCHING PATTERN "*")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

if(UNIX)
    set(CPACK_GENERATOR "DEB;RPM;TGZ")
    set(CPACK_PACKAGE_CONTACT "sorin.andrei.tudose@gmail.com")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Sorin <sorin.andrei.tudose@gmail.com")
elseif(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_NSIS_DISPLAY_NAME ${PROJECT_NAME})
    set(CPACK_NSIS_PACKAGE_NAME ${PROJECT_NAME})
endif()

include(CPack)