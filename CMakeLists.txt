# ###############################################
# Check for a valid version of CMake.
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

ADD_DEFINITIONS("-std=c++11")

# ###############################################
# Start the project.
PROJECT( TheCyclops )

# ###############################################
# Allow unit tests to be disabled via command
# line or the CMake GUI.
OPTION( BUILD_UNIT_TESTS "Build unit tests." OFF )

# ###############################################
# Enable the CMake built in CTest system if unit
# tests are enabled.
IF( BUILD_UNIT_TESTS )
	ENABLE_TESTING()
ENDIF( BUILD_UNIT_TESTS )

# ###############################################
# Find packages for this machine.
#FIND_PACKAGE( Threads )

# ###############################################
# Add the external libraries, internal libraries,
# applications and tools to the project.
#INCLUDE( External/CMakeLists.txt )
#INCLUDE( Libraries/CMakeLists.txt )
ADD_SUBDIRECTORY( External )
ADD_SUBDIRECTORY( Libraries )
ADD_SUBDIRECTORY( Applications )
ADD_SUBDIRECTORY( Tools )

#SET(CMAKE_EXECUTABLE_SUFFIX ".html")
#ADD_EXECUTABLE(main ${sources})

#file(GLOB sources *.cpp)
#set(CMAKE_EXECUTABLE_SUFFIX ".html")
#add_executable(hello_triangle ${sources})
