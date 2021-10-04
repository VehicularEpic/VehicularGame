if (OS_WINDOWS)
    ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

    set(WINDOWS_RESOURCES platform/windows/Resource.rc platform/windows/Resource.h)
    source_group(${CMAKE_PROJECT_NAME} FILES ${WINDOWS_RESOURCES})

    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${PROJECT_SOURCES} ${WINDOWS_RESOURCES})
    SET_EXECUTABLE_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME})

    target_link_libraries(${CMAKE_PROJECT_NAME} ${LINKED_LIBS} ${CEF_STANDARD_LIBS})

    if (USE_SANDBOX)
        ADD_LOGICAL_TARGET("cef_sandbox_lib" "${CEF_SANDBOX_LIB_DEBUG}" "${CEF_SANDBOX_LIB_RELEASE}")

        target_link_libraries(${CMAKE_PROJECT_NAME} cef_sandbox_lib ${CEF_SANDBOX_STANDARD_LIBS})
    endif ()

    ADD_WINDOWS_MANIFEST("${CMAKE_SOURCE_DIR}/platform/windows/manifest" "${CMAKE_PROJECT_NAME}" "exe")
endif ()
