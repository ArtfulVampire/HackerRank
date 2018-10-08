QT += core
TARGET = hacker
CONFIG += c++1y
TEMPLATE = app
SOURCES += \
    queries.cpp \
    triplets.cpp \
    lib.cpp \
    main.cpp
OTHER_FILES += \
    input.txt
HEADERS += \
    header.h
DISTFILES += \
    input.txt
