TARGET = journalc

MOC_DIR = .moc
OBJECTS_DIR = .obj

QT += quick

CONFIG += link_pkgconfig
CONFIG += c++11
PKGCONFIG += libsystemd-journal

SOURCES = \
    src/main.cpp \
    src/journalmodel.cpp

HEADERS = \
    src/journalmodel.h

OTHER_FILES += \
    qml/main.qml
