QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        studentdatainfo.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Dodali smo StudentSerialization projekat kao zavisnost odabirom:
# Desni klik na StudentDataReadWrite -> Add Library... -> Internal Library -> Odabir projekta StudentSerialization
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../StudentSerialization/release/ -lStudentSerialization
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../StudentSerialization/debug/ -lStudentSerialization
else:unix: LIBS += -L$$OUT_PWD/../StudentSerialization/ -lStudentSerialization

INCLUDEPATH += $$PWD/../StudentSerialization
DEPENDPATH += $$PWD/../StudentSerialization

HEADERS += \
    studentdatainfo.h
