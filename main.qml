import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtScxml 5.8


Window {
    id: root

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TableView {
        id: chessboardView

        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        property int size: parent.width < parent.height ? parent.width : parent.height
        property int margins: 20
        property int fieldSize: (size - margins)/8
        property int borderWidth: Math.ceil(fieldSize / 20)

        model: chessboard.model
        width: size
        height: size

        EventConnection {
            stateMachine: app.stateMachine
            events: [app.stateMachine.fieldSelected]
            onOccurred: figureMovingAnimation.start();
        }

        PropertyAnimation {
            id: figureMovingAnimation

            ///TODO:
            loops: 1
            duration: 1
            onFinished:
            {
                console.log('onFinished')
                app.stateMachine.submitEvent(app.stateMachine.movingChanged)
            }
        }

        headerDelegate: Rectangle {
            color: app.style.chessBoardBackground
            height: chessboardView.margins
            Text {
                font.bold: true
                anchors.centerIn: parent
                text: styleData.value
                color: app.style.fontColor
            }
        }

        rowDelegate: Item {
            height: chessboardView.fieldSize;
        }

        itemDelegate: Rectangle {

            property bool isDark: styleData.value.row %2 ? (styleData.value.column % 2) : !(styleData.value.column % 2)
            property QtObject fieldObj: styleData.value
            property QtObject figureObj: fieldObj.figure ? fieldObj.figure : null

            color: isDark ? app.style.fieldsColor_dark : app.style.fieldsColor_light

            border.color: fieldObj.available ? 'green' : 'transparent'
            border.width: chessboardView.borderWidth

            Loader {
                id: figure

                anchors.fill: parent
                sourceComponent: styleData.value.figure ? figureComponent : undefined
            }

            MouseArea {
                id: mouseArea1
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: (figureObj && figureObj.canBeSelected) ? Qt.OpenHandCursor : (styleData.value.available ? Qt.OpenHandCursor : Qt.ArrowCursor)
                onClicked: {
                    if (app.stateMachine.figureSelecting && figureObj && figureObj.canBeSelected)
                        figureObj.select()

                    else if (app.stateMachine.fieldSelecting && chessboard.selectedFigure && fieldObj.available)
                    {
                        chessboard.selectedFigure.move(fieldObj)
                        app.stateMachine.submitEvent(app.stateMachine.fieldSelected)
                    }
                }
            }

            Component {
                id: figureComponent

                Rectangle {
                    id: figureItem

                    property QtObject fieldObj: styleData.value
                    property QtObject figureObj: fieldObj.figure

                    anchors.fill: parent
                    border.color: figureObj.canBeSelected ? 'green' : 'transparent'
                    border.width: chessboardView.borderWidth
                    color: 'transparent'

                    Image {
                        width: parent.width
                        height: parent.height
                        x: 0
                        y: figureObj.canBeSelected || figureObj.selected ? (figureObj.selected || mouseArea1.containsMouse ? -chessboardView.fieldSize / 10 : 0) : 0
                        source: app.style.figureImage(styleData.value.figure)
                    }
                }
            }
        }

        contentFooter: Rectangle {
            color: "#1ea60d"
            height:10// chessboardView.margins
        }

        TableViewColumn {
            width: chessboardView.margins
            title: ""
            delegate: Rectangle {
                color: app.style.chessBoardBackground

                Text {
                    color: app.style.fontColor
                    anchors.centerIn: parent
                    text: 8 - styleData.row
                    font.bold: true
                }
            }
        }

        TableViewColumn {
            width: chessboardView.fieldSize
            role: "A"
            title: "A"
        }

        TableViewColumn {
            width: chessboardView.fieldSize
            role: "B"
            title: "B"
        }

        TableViewColumn {
            width: chessboardView.fieldSize
            role: "C"
            title: "C"
        }

        TableViewColumn {
            width: chessboardView.fieldSize
            role: "D"
            title: "D"
        }

        TableViewColumn {
            width: chessboardView.fieldSize
            role: "E"
            title: "E"
        }

        TableViewColumn {
            width: chessboardView.fieldSize
            role: "F"
            title: "F"
        }

        TableViewColumn {
            width: chessboardView.fieldSize
            role: "G"
            title: "G"
        }

        TableViewColumn {
            width: chessboardView.fieldSize
            role: "H"
            title: "H"
        }

    }

    GameResult {
        anchors.fill: parent
    }
}
