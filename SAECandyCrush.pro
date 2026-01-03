TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        modes_de_jeu/duo.cpp \
        modes_de_jeu/pvp.cpp \
        modes_de_jeu/solo.cpp \
        modes_de_jeu/modehistoire.cpp
HEADERS += \
        modes_de_jeu/duo.h \
        modes_de_jeu/pvp.h \
        modes_de_jeu/solo.h \
        modes_de_jeu/modehistoire.h
