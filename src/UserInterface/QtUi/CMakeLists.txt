add_library(QtUi_lib STATIC QtUiController.cpp)

target_include_directories(QtUi_lib PUBLIC ./include)

target_link_libraries(QtUi_lib SOG::Utils Qt6::Core Qt6::Widgets)

add_library(SOG::UI::QT ALIAS QtUi_lib)
