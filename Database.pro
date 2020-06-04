TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    stokenizer.cpp \
    token.cpp \
    table.cpp \
    commandparser.cpp \
    parsetree.cpp \
    record.cpp \
    sql.cpp

HEADERS += \
    set.h \
    array_functions.h \
    stokenizer.h \
    token.h \
    constants.h \
    table.h \
    commandparser.h \
    array2d_helper_functions.h \
    parsetree.h \
    parse_tree_functions.h \
    pair.h \
    record.h \
    sql.h
