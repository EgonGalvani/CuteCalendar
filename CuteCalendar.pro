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
    	Model/Container/invalidinterval.cpp \
    Model/Hierarchy/uniqueevent.cpp \
    Model/Hierarchy/eventwithduration.cpp \
    Model/Hierarchy/recurrence.cpp \
    Model/Hierarchy/recurrencerule.cpp \
    Model/Hierarchy/event.cpp \
    Model/Hierarchy/birthday.cpp \
    Model/Hierarchy/training.cpp \
    Model/Hierarchy/reminder.cpp \
    Model/Hierarchy/meeting.cpp \
    Model/Hierarchy/alldayevent.cpp \
    Model/Hierarchy/datemanager.cpp \
    Model/Hierarchy/timemanager.cpp \
    Model/Hierarchy/todolist.cpp \
    Model/DataType/time.cpp

HEADERS += \
View/mainwindow.h \
        Model/Hierarchy/datemanager.h \
        Model/Container/intervaltree.h \
        Model/Container/invalidinterval.h \
        Model/DataType/date.h \
        Model/DataType/time.h \
    Model/Hierarchy/datemanager.h \
    Model/Hierarchy/event.h \
    Model/Hierarchy/timemanager.h \
    Model/Hierarchy/recurrence.h \
    Model/Hierarchy/recurrencerule.h \
    Model/Hierarchy/weeklyrule.h \
    Model/Hierarchy/yearlyrule.h \
    Model/Hierarchy/alldayevent.h \
    Model/Hierarchy/eventwithduration.h \
    Model/Hierarchy/uniqueevent.h \
    Model/Hierarchy/birthday.h \
    Model/Hierarchy/training.h \
    Model/Hierarchy/todolist.h \
    Model/Hierarchy/preciseevent.h \
    Model/Hierarchy/meeting.h \
    Model/Hierarchy/reminder.h \
    Model/Hierarchy/monthlyrule.h

FORMS +=
