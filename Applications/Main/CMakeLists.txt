PROJECT (MAIN)

#ADD_DEFINITIONS("-s USE_SDL=2")

FILE ( GLOB_RECURSE
       INCLUDE_FILES
       Source/*.h
       Source/*.hpp
      )

SET ( SOURCE_FILES
    Source/Cyclops.cpp)
#    Source/main.cpp)

####SET(CMAKE_EXECUTABLE_SUFFIX ".html")

ADD_EXECUTABLE (Main ${SOURCE_FILES}
                        ${INCLUDE_FILES})


cyc_set_default_properties(Main)

####SET_TARGET_PROPERTIES(Main PROPERTIES LINK_FLAGS "-s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"bmp\", \"png\"]' --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/Assets@/")

#Add project libraries
#TARGET_LINK_LIBRARIES (Main Math_static)
TARGET_LINK_LIBRARIES (Main Application_static)
TARGET_LINK_LIBRARIES (Main ScriptManager_static)

INSTALL (TARGETS Main
        RUNTIME DESTINATION bin COMPONENT Runtime
        LIBRARY DESTINATION lib COMPONENT Runtime)