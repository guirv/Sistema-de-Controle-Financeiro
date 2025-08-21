cmake_minimum_required(VERSION 3.16)

project(ControleFinanceiro VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES ControleFinanceiro_pt_BR.ts)


set(PROJECT_SOURCES
    main.cpp

    user.h
    user.cpp
    estrategia.h
    estrategia.cpp
    lancamento.h
    despesa.h

    janelalogin.h
    janelalogin.cpp
    janelalogin.ui

    janelacadastro.h
    janelacadastro.cpp
    janelacadastro.ui

    janelasenha.h
    janelasenha.cpp
    janelasenha.ui

    janelasobremim.h
    janelasobremim.cpp
    janelasobremim.ui

    janelaestrategia.h
    janelaestrategia.cpp
    janelaestrategia.ui

    janelacriarestrategia.h
    janelacriarestrategia.cpp
    janelacriarestrategia.ui

    janelanovadespesa.h
    janelanovadespesa.cpp
    janelanovadespesa.ui

    janelaprincipal.h
    janelaprincipal.cpp
    janelaprincipal.ui

    recursos.qrc
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ControleFinanceiro
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        perfis.h perfis.cpp


    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(ControleFinanceiro SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ControleFinanceiro
            ${PROJECT_SOURCES}
        )
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(ControleFinanceiro PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ControleFinanceiro)
endif()
set_target_properties(ControleFinanceiro PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ControleFinanceiro
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ControleFinanceiro)
endif()
