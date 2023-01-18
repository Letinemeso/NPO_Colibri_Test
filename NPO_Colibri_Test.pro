TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	Data_Encryptor.cpp \
	File_Mask.cpp \
	File_Processor.cpp \
	main.cpp

LIBS += \
	-lstdc++fs

HEADERS += \
	Data_Encryptor.h \
	File_Mask.h \
	File_Processor.h

unix {
    LIBS += -lpthread
}
