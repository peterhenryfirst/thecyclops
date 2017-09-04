# ###############################################
# Check for a valid version of CMake.
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# ###############################################
# Include the main cmake file
get_filename_component(CYC_ROOT_DIR "." ABSOLUTE)
message("CYC_ROOT_DIR: ${CYC_ROOT_DIR}")
include("${CYC_ROOT_DIR}/CMake/cyclops.cmake")

# ###############################################
# Add definitions
ADD_DEFINITIONS("-std=c++11")

# ###############################################
# Start & Setup the project.
PROJECT( TheCyclops )

cyc_setup()

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
