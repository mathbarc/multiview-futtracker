set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

set(Boost_USE_STATIC_LIBS    OFF) # only find static libs
set(Boost_USE_MULTITHREADED  ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED date_time filesystem system)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(Qt5Widgets REQUIRED)

find_package(OpenCV 3 COMPONENTS core highgui videoio imgcodecs)

if(${OpenCV_FOUND})
else()
        find_package(OpenCV 2 REQUIRED core highgui)
endif()

set(VIEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "View include dir")

set(VIEW_INCLUDE_DIRS
        ${VIEW_INCLUDE_DIR}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS})

file(GLOB VIEW_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB VIEW_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB VIEW_FORMS ${CMAKE_CURRENT_SOURCE_DIR}/forms/*.ui)

include_directories(${VIEW_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

qt5_wrap_ui(VIEW_WRAPPED_IUS ${VIEW_FORMS})
qt5_add_resources(VIEW_RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc)
add_library(View STATIC ${VIEW_SOURCES} ${VIEW_HEADERS} ${VIEW_WRAPPED_IUS} ${VIEW_RESOURCE})
target_link_libraries(View Qt5::Widgets ${OpenCV_LIBS} ${Boost_LIBRARIES})
