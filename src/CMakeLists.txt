add_executable(${PROJECT_NAME} "")

set(SOURCES vertexutil.cpp shaderutil.cpp glutil.cpp main.cpp)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

file(GLOB SHADER_SOURCES
  shaders/*.glsl
)

add_custom_target(
  Shaders
  DEPENDS ${SHADER_SOURCES}
)

add_dependencies(${PROJECT_NAME} Shaders)

add_custom_command(TARGET Shaders POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "$<TARGET_PROPERTY:${PROJECT_NAME},SOURCE_DIR>/shaders"
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders" # copy shaders relative to executable (bin dir; see parent List file)
)