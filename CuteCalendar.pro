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
    Model/Hierarchy/factory.cpp \
    View/modifydialog.cpp \
    View/modview.cpp \
    View/viewbirthday.cpp \
    View/viewmeeting.cpp \
    View/mainwindow.cpp \
    View/mycalendar.cpp \
    View/eventwidget.cpp \
    View/viewreminder.cpp \
    View/viewworkout.cpp \
    main.cpp \
    Model/DataType/time.cpp \
    Model/DataType/date.cpp \
    Model/DataType/formaterror.cpp \
    Model/model.cpp \
    Model/Hierarchy/todolist.cpp \
    Model/Hierarchy/event.cpp \
    Model/Hierarchy/workout.cpp \
    Model/Hierarchy/alert.cpp \
    Model/Hierarchy/alldayevent.cpp \
    Model/Hierarchy/eventwithduration.cpp \
    Model/Hierarchy/reminder.cpp \
    Model/Hierarchy/meeting.cpp \
    Model/Hierarchy/birthday.cpp \
    View/tagpicker.cpp \
    View/neweventdialog.cpp \
    View/checklist.cpp \
    View/viewtodolist.cpp \
    View/enterlineedit.cpp \
    View/msgscheduler.cpp

HEADERS += \
    Model/Hierarchy/factory.h \
    View/mainwindow.h \
    View/modifydialog.h \
    View/modview.h \
    View/mycalendar.h \
    View/viewbirthday.h \
    View/viewmeeting.h \
    View/eventwidget.h \
    Model/DataType/date.h \
    Model/DataType/time.h \
    Model/Hierarchy/event.h \
    Model/Hierarchy/alldayevent.h \
    Model/Hierarchy/eventwithduration.h \
    Model/Hierarchy/alert.h \
    Model/Hierarchy/birthday.h \
    Model/Hierarchy/todolist.h \
    Model/Hierarchy/meeting.h \
    Model/Hierarchy/reminder.h \
    Model/Hierarchy/workout.h \
    Model/DataType/formaterror.h \
    Model/DataType/deepptr.h \
    Model/model.h \
    Model/Container/vector.h \
    Model/Container/unorderedmultimap.h \
    View/tagpicker.h \
    View/neweventdialog.h \
    View/checklist.h \
    View/viewtodolist.h \
    View/enterlineedit.h \
    View/viewreminder.h \
    View/viewworkout.h \
    View/msgscheduler.h

FORMS +=

RESOURCES += \
    res.qrc
