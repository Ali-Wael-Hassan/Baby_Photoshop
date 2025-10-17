cmake_minimum_required(VERSION 3.16)

project(Baby_Photoshop_fix VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appBaby_Photoshop_fix
    main.cpp
    app_icon.rc
)

qt_add_qml_module(appBaby_Photoshop_fix
    URI Baby_Photoshop_fix
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES stb_image.h
        SOURCES stb_image_write.h
        SOURCES transformoperations.h transformoperations.cpp
        SOURCES image_class.h image_class.cpp
        SOURCES toneandcoloradjustments.h toneandcoloradjustments.cpp
        SOURCES overlay.h overlay.cpp
        SOURCES menu.h menu.cpp
        SOURCES manager.h manager.cpp
        SOURCES artisticeffects.h artisticeffects.cpp
        QML_FILES FirstMenu.qml
        QML_FILES SecondMenu.qml
        RESOURCES
                icon/simple.png
                icon/resize.png
                icon/oldPhoto.png
                icon/fancy.png
                icon/crop.png
                icon/blackAndwhite.png
                icon/gray.png
                icon/blur.png
                icon/bright.png
                icon/contrast.png
                icon/flip.png
                icon/frame.png
                icon/home.png
                icon/infrared.png
                icon/invert.png
                icon/Merge.png
                icon/oil.png
                icon/purple.png
                icon/redo.png
                icon/rotate.png
                icon/skew.png
                icon/sun.png
                icon/tv.png
                icon/undo.png
                icon/plus.png
                icon/Baby_Photoshop.png
                icon/edge.png
                icon/sun2.png
                icon/dark.png
                icon/DUCK.jpg
                RESOURCES app_icon.rc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appBaby_Photoshop_fix PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appBaby_Photoshop_fix
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME "DUCK"
)

target_link_libraries(appBaby_Photoshop_fix
    PRIVATE Qt6::Quick
            Qt6::Core
            Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appBaby_Photoshop_fix
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
