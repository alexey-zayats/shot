TEMPALTE=app
TARGET=shot

CONFIG      += shared
CONFIG      += qt
CONFIG 	    -= app_bundle

QT += webenginewidgets
QT += core
QT += gui
QT += widgets
QT += webview
QT += network

SOURCES += main.cpp \
	shotwindow.cpp

HEADERS += shotwindow.h

