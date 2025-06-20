# add mem leak checker
add_subdirectory("${PROJECT_SOURCE_DIR}/src/third_party/Oakum")

# Add cJSON source files

file(GLOB cJSON_SOURCES "${PROJECT_SOURCE_DIR}/src/third_party/cjson/*.c")
file(GLOB cJSON_HEADERS "${PROJECT_SOURCE_DIR}/src/third_party/cjson/*.h")

# Create library
add_library(cjson STATIC ${cJSON_SOURCES})

# Link against cjson
add_executable       (${PROJECT_NAME} WIN32 MACOSX_BUNDLE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${FLTK_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE cjson)
target_link_libraries(${PROJECT_NAME} PRIVATE Oakum)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cjson
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}^/third_party/Oakum/source/include
)

# set DEBUG 0/1 in C-Source
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG=1)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG=0)
endif()

# Modify your copy command to use the runtime output directory
set(CONFIG_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/config.json"
    # "${CMAKE_CURRENT_SOURCE_DIR}/settings.json"
)

foreach(FILE_TO_COPY IN LISTS CONFIG_FILES)
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FILE_TO_COPY}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_FILE_NAME}"
        COMMENT "Copying config files..."
        VERBATIM
    )
endforeach()

