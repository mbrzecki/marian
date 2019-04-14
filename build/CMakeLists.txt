cmake_minimum_required(VERSION 3.6.2)
project (MARIAN)

# setting cmake scripts dir
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/included_scripts/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "./static_lib")

# compilation flags, linker flags

set( COMPILE_FLAGS "-std=c++11 -pedantic -Wall -Wextra -O3")
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set( CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

link_directories(/usr/local/lib)

# searching for libraries needed
include( FIND_GSL)

# adding directories with header files
include_directories(../src)

# adding directories with source files

file(GLOB DIFFUSION "../src/diffusion/*.cpp")
file(GLOB UTILS "../src/utils/*.cpp")
file(GLOB FDM "../src/FDM/*.cpp")
file(GLOB BC "../src/FDM/boundaryConditions/*.cpp")
file(GLOB GRID "../src/FDM/gridBuilders/*.cpp")
file(GLOB SCHEME "../src/FDM/schemes/*.cpp")
file(GLOB FIN "../src/financial/*.cpp")
file(GLOB OPT "../src/financial/options/*.cpp")
file(GLOB GRIDRANGE "../src/financial/gridRange/*.cpp")

# creating macro variablesmake    
set(SOURCES ${DIFFUSION} ${UTILS} ${FDM}  ${BC} ${GRID} ${SCHEME} ${FIN} ${OPT} ${GRIDRANGE})	
	    
set(LINK_FLAG ${GSL_LIBRARIES})

# object library

add_library(maniek OBJECT ${SOURCES})

# creating executables on the basis of cpp files in mains directory

file( GLOB APP_SOURCES "../example/*.cpp" )
foreach( sourcefiles ${APP_SOURCES} )

	 string( REGEX REPLACE "^.*/example/" "" rawpath ${sourcefiles})
	 string( REPLACE ".cpp" "" filename ${rawpath} )
	 string( CONCAT path [ ${rawpath} "/" ${filename} ".cpp" ])
	 string( REPLACE "[" "" path ${path} )
	 string( REPLACE "]" "" path ${path} )

	 add_executable( ${filename} ${sourcefiles} $<TARGET_OBJECTS:maniek>)
	 target_link_libraries(${filename} ${LINK_FLAG})
	 
endforeach( sourcefiles ${APP_SOURCES} )
