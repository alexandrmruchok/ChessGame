QT += quick scxml

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AppStateMachine.cpp \
        Application.cpp \
        Field.cpp \
        ChessBoard.cpp \
        FieldsRow.cpp \
        figures/AbstractFigure.cpp \
        figures/BishopFigure.cpp \
        figures/KingFigure.cpp \
        figures/KnightFigure.cpp \
        figures/PawnFigure.cpp \
        figures/QueenFigure.cpp \
        figures/RookFigure.cpp \
        main.cpp \
        styles/AbstractStyle.cpp

RESOURCES += \
    images.qrc \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AppStateMachine.h \
    Application.h \
    Field.h \
    BoardPos.h \
    ChessBoard.h \
    FieldsRow.h \
    figures/AbstractFigure.h \
    figures/BishopFigure.h \
    figures/KingFigure.h \
    figures/KnightFigure.h \
    figures/PawnFigure.h \
    figures/QueenFigure.h \
    figures/RookFigure.h \
    figures/figures.h \
    styles/AbstractStyle.h \
    styles/ClassicStyle.h

DISTFILES += \
    classchart.qmodel

STATECHARTS += \
    stateChart.scxml

INCLUDEPATH += \
    figures/ \
    styles/
