add_subdirectory(Business)
add_subdirectory(Control)
add_subdirectory(Persistence)
add_subdirectory(View)

find_package(Qt5Widgets REQUIRED)

set(MULTIVIEW_FUTTRACKER_INCLUDE_DIRS 
        ${Qt5Widgets_INCLUDE_DIRS}
        ${CONTROL_INCLUDE_DIR}
        ${VIEW_INCLUDE_DIR}
)

file(GLOB MULTIVIEW_FUTTRACKER_SOURCES main.cpp)

include_directories(${MULTIVIEW_FUTTRACKER_INCLUDE_DIRS})
message("${MULTIVIEW_FUTTRACKER_INCLUDE_DIRS}")

add_executable(FutTracker ${MULTIVIEW_FUTTRACKER_SOURCES})
target_link_libraries(FutTracker Qt5::Core Control View)
