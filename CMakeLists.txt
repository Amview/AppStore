cmake_minimum_required(VERSION 3.16)

project(AppStore VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".LIB" ".dll" ".DLL" ".dylib")
include_directories("/Users/hua/file/project/源码/cpp-httplib-0.16.0")
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIRS})
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        utils/config_utils.cpp
        utils/config_utils.h
        domain/app_info.cpp
        domain/app_info.h
        utils/qjson_utils.cpp
        utils/qjson_utils.h
        component/download_card.cpp
        component/download_card.h
        component/app.cpp
        component/app.h
        rs.qrc
        utils/layout_utils.cpp
        utils/layout_utils.h
        utils/font_builder.h
        utils/http_utils.cpp
        utils/http_utils.h
        utils/string_utils.cpp
        utils/string_utils.h
        domain/config.cpp
        domain/config.h
        component/settingdialog.h
        component/settingdialog.cpp
        component/customlineedit.cpp
        ui.cpp
        component/pathselectedit.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AppStore
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AppStore APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(AppStore SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AppStore
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(AppStore PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(AppStore PRIVATE OpenSSL::SSL OpenSSL::Crypto)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AppStore)
endif()
set_target_properties(AppStore PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AppStore
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AppStore)
endif()
