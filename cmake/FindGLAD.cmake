add_subdirectory(${PROJECT_EXTERNAL_MODULES}/glad/cmake)

glad_add_library(glad STATIC API ${GLAD_API})
