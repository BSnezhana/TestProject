QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../Grocery
SOURCES +=  tst_testcsvstreamer.cpp \
    ../Grocery/CSVStreamer.cpp
