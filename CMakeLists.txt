
project(wxBinApi)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O3") # Компиляция больших файлов

# SET(CMAKE_BUILD_TYPE Release) 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OPENSSL_USE_STATIC_LIBS TRUE)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../bin)

if(MINGW)
    link_libraries(ws2_32 wsock32)
endif()

set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)


find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

file(GLOB project
    *
    data/*
    data/dopformat/*
)

add_library(${PROJECT_NAME} STATIC ${project})


add_library(lib::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

if(wxWidgets_FOUND)
    target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
    # message(STATUS "Found wxWidgets ${wxWidgets_VERSION_STRING}")
else()
    message(STATUS "WEBSOCKET wxWidgets Not Found")
endif()

if(OPENSSL_FOUND)
    # Add the include directories for compiling
    target_include_directories(${PROJECT_NAME} PRIVATE ${OPENSSL_INCLUDE_DIR})

    # Add the static lib for linking
    target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)
    # message(STATUS "Found OpenSSL ${OPENSSL_VERSION}")
else()
    message(STATUS "WEBSOCKET OpenSSL Not Found")
endif()

if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    # message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
else()
    message(STATUS "WEBSOCKET BOOST Not Found")
endif()