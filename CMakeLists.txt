cmake_minimum_required(VERSION 2.8.12)

include(ExternalProject)

#############################################################################
#   P R O J E C T
#############################################################################

set(package "openrti-adapter-project")
project(${package})


#############################################################################
#   Application
#############################################################################

set(application "hla-control-cost")
set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_C_FLAGS " -Wall -Wno-deprecated -fPIC -m64 ${CMAKE_C_FLAGS}")
SET(CMAKE_CXX_FLAGS " -Wall -Wno-deprecated -fPIC -m64 ${CMAKE_CXX_FLAGS}")

#############################################################################
#   P A C K A G E S
#############################################################################
find_package(PkgConfig)

#############################################################################
#   L I B R A R I E S
#############################################################################

list(APPEND used_libs glfw GL dl)



#############################################################################
#   S O U R C E S
#############################################################################

file(GLOB  app_srcs     "src/*.cpp")
file(GLOB  main_srcs    "app/*.cpp")
file(GLOB  app_include  "include/*.hpp")

include_directories( include )


#############################################################################
#   E X E C U T A B L E S
#############################################################################

add_definitions( -DSHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/media/shaders" )
add_executable(${application} ${app_srcs} ${main_srcs})
target_link_libraries(${application} ${used_libs})

install (TARGETS ${application} DESTINATION bin OPTIONAL)
