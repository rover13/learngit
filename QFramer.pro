#-------------------------------------------------
#
# Project created by QtCreator 2014-07-23T11:28:16
#
#-------------------------------------------------

QT       += core gui printsupport webkitwidgets axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# application name
TARGET = QFramer

# type
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .    \
            .\YYTRemote \
            "$(LIVESDK)/include/" \
            "$(SINGLEAPPSDK)/include/"


LIBS += -L"$(LIVESDK)/libs/Debug" \
        "$(SINGLEAPPSDK)/libs/debug/QtSolutions_SingleApplication-headd.lib" \

include(./QFramer/QFramer.pri)

# build dir
BuildDir =build_$$QT_VERSION

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/$$BuildDir/debug
    OBJECTS_DIR = $$PWD/$$BuildDir/debug/.obj
    MOC_DIR = $$PWD/$$BuildDir/debug/.moc
    RCC_DIR = $$PWD/$$BuildDir/debug/.rcc
    UI_DIR = $$PWD/$$BuildDir/debug/.ui
} else {
    DESTDIR = $$PWD/$$BuildDir/release
    OBJECTS_DIR = $$PWD/$$BuildDir/release/.obj
    MOC_DIR = $$PWD/$$BuildDir/release/.moc
    RCC_DIR = $$PWD/$$BuildDir/release/.rcc
    UI_DIR = $$PWD/$$BuildDir/release/.ui
}

# source
SOURCES += \
    dialogs/settingdialog.cpp \
    functionpages/uielement.cpp \
    mainwindow/centerwindow.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/settingmenu.cpp \
    mainwindow/settingmenucontroller.cpp \
    mainwindow/thememenu.cpp \
    main.cpp \
    functionpages/animationgradientlabel.cpp \
    YYTRemote/YYTVideoShow.cpp \
    YYTRemote/YYTStateManage.cpp \
    YYTRemote/YYTServerHelper.cpp \
    YYTRemote/YYTRoomMemerDlg.cpp \
    YYTRemote/YYTPluginManage.cpp \
    YYTRemote/VideoRender.cpp \
    YYTRemote/sha1.cpp \
    YYTRemote/ScreenShareDlg.cpp \
    YYTRemote/RoomManage.cpp \
    YYTRemote/RemoteImageDlg.cpp \
    YYTRemote/PatientCase.cpp \
    YYTRemote/NetworkHelper.cpp \
    YYTRemote/MessageCallBack.cpp \
    YYTRemote/LiveServerHelper.cpp \
    YYTRemote/InteractionServerHelper.cpp \
    YYTRemote/iLiveSDKWrap.cpp \
    YYTRemote/Event.cpp \
    YYTRemote/ConsultationReportDlg.cpp \
    YYTRemote/ConsultationApplyDlg.cpp \
    common/YYTCommon/Util.cpp \
    functionpages/rightfloatwindow.cpp

# header
HEADERS  += \
    dialogs/settingdialog.h \
    functionpages/uielement.h \
    mainwindow/centerwindow.h \
    mainwindow/mainwindow.h \
    mainwindow/settingmenu.h \
    mainwindow/settingmenucontroller.h \
    mainwindow/thememenu.h \
    functionpages/animationgradientlabel.h \
    YYTRemote/YYTVideoShow.h \
    YYTRemote/YYTStateManage.h \
    YYTRemote/YYTServerHelper.h \
    YYTRemote/YYTRoomMemerDlg.h \
    YYTRemote/YYTPluginManage.h \
    YYTRemote/VideoRender.h \
    YYTRemote/sha1_Psword.h \
    YYTRemote/sha1.h \
    YYTRemote/ScreenShareDlg.h \
    YYTRemote/RoomManage.h \
    YYTRemote/RemoteImageDlg.h \
    YYTRemote/PatientCase.h \
    YYTRemote/NetworkHelper.h \
    YYTRemote/MessageCallBack.h \
    YYTRemote/LiveServerHelper.h \
    YYTRemote/InteractionServerHelper.h \
    YYTRemote/iLiveSDKWrap.h \
    YYTRemote/Event.h \
    YYTRemote/ConsultationReportDlg.h \
    YYTRemote/ConsultationApplyDlg.h \
    common/YYTCommon/Util.h \
    common/YYTCommon/common.h \
    functionpages/rightfloatwindow.h

# resources
RESOURCES += \
    QFramer.qrc

# QT4.8 applciation icon
contains(QT_MAJOR_VERSION, 4){
    win32{
        RC_FILE = QFramer.rc
    }
}

# QT5 applciation icon
contains(QT_MAJOR_VERSION, 5){
    RC_ICONS = "skin/images/QFramer.ico"
}

FORMS +=
