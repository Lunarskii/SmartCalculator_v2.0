cmake_minimum_required(VERSION 3.5)

project(untitled VERSION 0.1 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "/usr/local/qt;/opt/qt;$ENV{QT_INSTALL_DIR};$ENV{QTDIR};~/Qt/")
set(CMAKE_PREFIX_PATH "/home/lunarskii/Qt/6.4.2/gcc_64/lib/cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR}PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(PROJECT_DIRS
        model/
        controller/
        view/
        .
)
set(TEST_DIRS
        model/
        tests/
)

set(PROJECT_SOURCES "")
set(TEST_SOURCES "")

foreach(dir ${PROJECT_DIRS})
    file(GLOB CPP_SOURCES "${dir}/*.cpp")
    file(GLOB HEADER_SOURCES "${dir}/*.h")
    file(GLOB UI_SOURCES "${dir}/*.ui")
    list(APPEND PROJECT_SOURCES ${CPP_SOURCES} ${HEADER_SOURCES} ${UI_SOURCES})
endforeach()

foreach(dir ${TEST_DIRS})
    file(GLOB CPP_SOURCES "${dir}/*.cpp")
    file(GLOB HEADER_SOURCES "${dir}/*.h")
    list(APPEND TEST_SOURCES ${CPP_SOURCES} ${HEADER_SOURCES})
endforeach()

add_executable(tests 
        ${TEST_SOURCES}
)

add_custom_target(coverage
  COMMAND lcov --directory . --capture --output-file coverage.info
  COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info
  COMMAND lcov --list coverage.info
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(untitled
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET untitled APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(untitled SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(untitled
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(untitled PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(untitled PUBLIC Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(untitled PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(tests PRIVATE ${GTEST_LIBRARIES} pthread)

include(GoogleTest)
gtest_discover_tests(tests)

set_target_properties(untitled PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS untitled
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled)
endif()
