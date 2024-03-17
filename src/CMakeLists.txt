add_executable(${PROJECT_NAME} "")

set(SOURCES glutil.cpp main.cpp)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})