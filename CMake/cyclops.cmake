# ###############################################
#   cyc.cmake
#   Main cmake header for project, this must be included in the top-level
#   CMakeLists.txt file of a project




# ###############################################
#   cyc_setup()
#   Performs one-time initialization of the build system. Must be called
#   at the start of the root CMakeLists.txt file.
#
macro(cyc_setup)

  message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
  
  message("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME}")
  message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

  # set host system variables
  set (CYC_HOST_WINDOWS 0)
  set (CYC_HOST_OSX 0)
  set (CYC_HOST_LINUX 0)
  if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(CYC_HOST_WINDOWS 1)
    message("Host system: Windows")
  elseif (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
    set(CYC_HOST_OSX 1)
    message("Host system: OSX")
  elseif (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(CYC_HOST_LINUX 1)
    message("Host system: Linux")
  else()
    message(WARNING "Host system not recognized, setting to 'Linux'")
    set(CYC_HOST_LINUX 1)
  endif()

  # detect compiler
  message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
  if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    set(CYC_CLANG 1)
    message("Detected C++ Compiler: Clang (CYC_CLANG)")
  elseif (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    set(CYC_GCC 1)
    message("Detected C++ Compiler: GCC (CYC_GCC)")
  elseif (MSVC)
    set(CYC_MSVC 1)
    message("Detected C++ Compiler: VStudio (CYC_MSVC)")
  else()
    message("Detected C++ Compiler: Unknown")
  endif()

  
endmacro()

# ###############################################
#   cyc_set_default_properties()
#   Performs one-time initialization of the build system. Must be called
#   at the end of the executable CMakeLists.txt file.
#

macro(cyc_set_default_properties target)
  if (CYC_EMSCRIPTEN)
    SET(CMAKE_EXECUTABLE_SUFFIX ".html")
    SET_TARGET_PROPERTIES(${target} PROPERTIES LINK_FLAGS "-s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"bmp\", \"png\"]' --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/Assets@/")
  endif()
endmacro()