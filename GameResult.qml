import QtQuick 2.12

Rectangle {

    anchors.fill: parent
    color: app.style.chessBoardBackground
    visible: app.stateMachine.gameResult

    Connections {
        target: chessboard
        onStalemate: text.text = "Stalemat. Press to continue"
    }

    Connections {
        target: chessboard
        onCheckmate: text.text = "Checkmate. Press to continue"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: app.stateMachine.submitEvent(app.stateMachine.restarted)
    }

    Text {
        id: text

        anchors.centerIn: parent
        font.pixelSize: 28
        color: app.style.fontColor
        text: qsTr("Game Finished")
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
