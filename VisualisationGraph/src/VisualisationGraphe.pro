# #####################################################################
# Automatically generated by qmake (2.01a) mer. fvr. 17 13:29:22 2010
# #####################################################################
TEMPLATE = app
TARGET = 
DEPENDPATH += . \
    controller \
    model \
    observer \
    serialize \
    view \
    model/Graph \
    serialize/xml
INCLUDEPATH += . \
    model \
    observer \
    controller \
    view \
    serialize \
    model/Graph \
    serialize/xml

# Input
HEADERS += controller/ControllerModel.h \
    model/AbstractModel.h \
    model/Algo.h \
    model/AlgoUtils.h \
    model/Graph.h \
    model/Graph/GraphMatrix.h \
    model/Model.h \
    model/Summit.h \
    observer/Observable.h \
    observer/Observer.h \
    serialize/AlgoIO.h \
    serialize/AlgoLoader.h \
    serialize/GraphIO.h \
    serialize/GraphXml.h \
    serialize/Serialize.h \
    view/ConfigGraph.h \
    view/Console.h \
    view/Edge.h \
    view/GraphWidget.h \
    view/MainFrame.h \
    view/MenuBar.h \
    view/Node.h \
    view/StatusBar.h \
    view/ToolsBar.h \
    serialize/xml/tinystr.h \
    serialize/xml/tinyxml.h
SOURCES += main.cpp \
    controller/ControllerModel.cpp \
    model/AbstractModel.cpp \
    model/AlgoUtils.cpp \
    model/Graph.cpp \
    model/Graph/GraphMatrix.cpp \
    model/Model.cpp \
    model/Summit.cpp \
    serialize/AlgoLoader.cpp \
    serialize/GraphXml.cpp \
    serialize/Serialize.cpp \
    view/ConfigGraph.cpp \
    view/Console.cpp \
    view/Edge.cpp \
    view/GraphWidget.cpp \
    view/MainFrame.cpp \
    view/MenuBar.cpp \
    view/Node.cpp \
    view/StatusBar.cpp \
    view/ToolsBar.cpp \
    serialize/xml/tinystr.cpp \
    serialize/xml/tinyxml.cpp \
    serialize/xml/tinyxmlerror.cpp \
    serialize/xml/tinyxmlparser.cpp
