cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wdelete-non-virtual-dtor")

project( objectannotationtool )

find_package(Boost COMPONENTS filesystem regex)
find_package(OpenCV REQUIRED)
find_package(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(EXECUTABLE_OUTPUT_PATH ../bin)
file(GLOB_RECURSE objectannotationtool_src "src/*.cpp")

QT4_WRAP_UI(UI_INTERFACE 
			gui/mainwindow.ui 
			gui/associatedialog.ui
)

include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_BINARY_DIR} src)
add_executable( annotationtool ${objectannotationtool_src} ${UI_INTERFACE})
target_link_libraries( annotationtool ${Boost_LIBRARIES} ${OpenCV_LIBS} ${QT_LIBRARIES})
