set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package(Qt5Core REQUIRED)

set(Boost_USE_STATIC_LIBS    OFF) # only find static libs
set(Boost_USE_MULTITHREADED  ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED date_time filesystem system)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

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

set(BUSINESS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "Business include dir")

set(BUSINESS_INCLUDE_DIRS 
        ${BUSINESS_INCLUDE_DIR}
        ${Qt5Core_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS})


file(GLOB BUSINESS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB BUSINESS_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
add_definitions(-DWITH_CUDA=${WITH_CUDA} -DOPENCV_VERSION=${OPENCV_VERSION})
include_directories(${BUSINESS_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
#qt5_wrap_ui(CAMERAMARKER_WRAPPED_IUS ${CAMERAMARKER_FORMS})
#qt5_wrap_cpp(BUSINESS_WRAPPED_HEADERS ${BUSINESS_HEADERS})
#qt5_add_resources(CAMERAMARKER_RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc)
add_library(Business STATIC ${BUSINESS_SOURCES} ${BUSINESS_HEADERS})
target_link_libraries(Business Qt5::Core ${OpenCV_LIBS} ${Boost_LIBRARIES})
