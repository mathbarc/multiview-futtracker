set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(OPENCV_VERSION 3)
if(${WITH_CUDA})
    find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs video cudabgsegm)
else()
    find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs video)
endif()

if(WIN32)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/arch:AVX")
else()
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-mavx")
endif()


if(${OpenCV_FOUND})
else()
        find_package(OpenCV 2 REQUIRED core highgui video)
        set(OPENCV_VERSION 2)
endif()

find_package(dlib REQUIRED)

set(BUSINESS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "Business include dir")

set(BUSINESS_INCLUDE_DIRS 
        ${BUSINESS_INCLUDE_DIR}
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${dlib_INCLUDE_DIRS})


file(GLOB BUSINESS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB BUSINESS_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
add_definitions(-DWITH_CUDA=${WITH_CUDA} -DOPENCV_VERSION=${OPENCV_VERSION})
include_directories(${BUSINESS_INCLUDE_DIRS})

add_library(Business STATIC ${BUSINESS_SOURCES} ${BUSINESS_HEADERS})
target_link_libraries(Business Qt5::Core Qt5::Widgets ${OpenCV_LIBS} ${dlib_LIBS})
