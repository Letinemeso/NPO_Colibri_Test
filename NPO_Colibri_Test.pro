TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	File_Mask.cpp \
	main.cpp

LIBS += \
	-lstdc++fs

HEADERS += \
	File_Mask.h
