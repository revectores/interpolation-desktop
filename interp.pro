QT += widgets
QT += charts
QT += core

LIBS += -lpoly -L/usr/local/lib/revector
INCLUDEPATH += /usr/local/include
INCLUDEPATH += "dashboard"

SOURCES += "dashboard/dashboard.h"
SOURCES += "dashboard/dashboard.cpp"
SOURCES += "main.cpp"

