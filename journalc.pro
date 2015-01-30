TARGET = journalc

MOC_DIR = .moc
OBJECTS_DIR = .obj

QT += quick

CONFIG += link_pkgconfig
PKGCONFIG += libsystemd-journal

SOURCES = \
    src/main.cpp \
    src/journalmodel.cpp

HEADERS = \
    src/journalmodel.h

OTHER_FILES += \
    qml/main.qml
