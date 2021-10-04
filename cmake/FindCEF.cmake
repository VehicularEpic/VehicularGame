function(get_platform PLATFORM)
    if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
        if ("${PROJECT_ARCH}" STREQUAL "arm64")
            set(CEF_PLATFORM "macosarm64")
        else ()
            set(CEF_PLATFORM "macosx64")
        endif ()
    elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        if (CMAKE_SIZEOF_VOID_P MATCHES 8)
            set(CEF_PLATFORM "linux64")
        else ()
            set(CEF_PLATFORM "linux32")
        endif ()
    elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
        if (CMAKE_SIZEOF_VOID_P MATCHES 8)
            set(CEF_PLATFORM "windows64")
        else ()
            set(CEF_PLATFORM "windows32")
        endif ()
    endif ()

    set("${PLATFORM}" "${CEF_PLATFORM}" PARENT_SCOPE)
endfunction()

get_platform(CEF_PLATFORM)

# Specify the binary distribution type and download directory.
set(CEF_DISTRIBUTION "cef_binary_${CEF_VERSION}_${CEF_PLATFORM}")
set(CEF_DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/external")

# The location where we expect the extracted binary distribution.
set(CEF_ROOT_DIR "${CEF_DOWNLOAD_DIR}/${CEF_DISTRIBUTION}")

# Download and/or extract the binary distribution if necessary.
if (NOT IS_DIRECTORY "${CEF_ROOT_DIR}")
    set(CEF_DOWNLOAD_FILENAME "${CEF_DISTRIBUTION}.tar.bz2")
    set(CEF_DOWNLOAD_PATH "${CEF_DOWNLOAD_DIR}/${CEF_DOWNLOAD_FILENAME}")

    if (NOT EXISTS "${CEF_DOWNLOAD_PATH}")
        set(CEF_DOWNLOAD_URL "https://cef-builds.spotifycdn.com/${CEF_DOWNLOAD_FILENAME}")
        string(REPLACE "+" "%2B" CEF_DOWNLOAD_URL_ESCAPED ${CEF_DOWNLOAD_URL})

        # Download the SHA1 hash for the binary distribution.
        message(STATUS "Downloading ${CEF_DOWNLOAD_PATH}.sha1 from ${CEF_DOWNLOAD_URL_ESCAPED}...")

        file(DOWNLOAD "${CEF_DOWNLOAD_URL_ESCAPED}.sha1" "${CEF_DOWNLOAD_PATH}.sha1")
        file(READ "${CEF_DOWNLOAD_PATH}.sha1" CEF_SHA1)

        # Download the binary distribution and verify the hash.
        message(STATUS "Downloading ${CEF_DOWNLOAD_PATH}...")

        file(
                DOWNLOAD "${CEF_DOWNLOAD_URL_ESCAPED}" "${CEF_DOWNLOAD_PATH}"
                EXPECTED_HASH SHA1=${CEF_SHA1}
                SHOW_PROGRESS
        )
    endif ()

    # Extract the binary distribution.
    message(STATUS "Extracting ${CEF_DOWNLOAD_PATH}...")
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf "${CEF_DOWNLOAD_DIR}/${CEF_DOWNLOAD_FILENAME}"
            WORKING_DIRECTORY ${CEF_DOWNLOAD_DIR}
    )
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT_DIR}/cmake")

set(_CEF_ROOT "${CEF_ROOT_DIR}")
set(_CEF_ROOT_EXPLICIT 1)

include(cef_variables)
include(cef_macros)

add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

# Display configuration settings.
PRINT_CEF_CONFIG()
