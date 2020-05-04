#-------------------------------------------------
#
# Project created by QtCreator 2020-04-14T21:36:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuteCalendar
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        View/mainwindow.cpp \
    Model/DataType/time.cpp \
    Model/Hierarchy/todolist.cpp \
    Model/Hierarchy/event.cpp \
    Model/Hierarchy/workout.cpp \
    Model/Hierarchy/eventwithduration.cpp \
    Model/Hierarchy/alert.cpp \
    Model/Hierarchy/reminder.cpp \
    Model/Hierarchy/alldayevent.cpp \
    Model/Hierarchy/birthday.cpp \
    Model/Hierarchy/meeting.cpp \
    View/viewpromemoria.cpp \
    View/viewmeeting.cpp \
    View/viewcompleanno.cpp \
    View/viewallenamento.cpp \
    View/newevent.cpp \
    View/mycalendar.cpp \
    View/mainwindow.cpp

HEADERS += \
    View/mainwindow.h \
    View/newevent.h \
    View/mycalendar.h \
    View/viewallenamento.h \
    View/viewcompleanno.h \
    View/viewmeeting.h \
    View/viewpromemoria.h \
    Model/DataType/date.h \
    Model/DataType/time.h \
    Model/Hierarchy/event.h \
    Model/Hierarchy/alldayevent.h \
    Model/Hierarchy/eventwithduration.h \
    Model/Hierarchy/birthday.h \
    Model/Hierarchy/todolist.h \
    Model/Hierarchy/meeting.h \
    Model/Hierarchy/reminder.h \
    Model/DataType/formaterror.h \
    Model/DataType/deepptr.h \
    Model/model.h \
    Model/xmlfileio.h \
    Model/fileio.h \
    Model/Container/vector.h \
    Model/Container/unorderedmultimap.h \
    Model/Hierarchy/workout.h \
    Model/Hierarchy/alert.h \
    View/viewpromemoria.h \
    View/viewmeeting.h \
    View/viewcompleanno.h \
    View/viewallenamento.h \
    View/newevent.h \
    View/mycalendar.h \
    View/mainwindow.h

FORMS +=
