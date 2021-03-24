import QtQuick 2.12
import QtQuick.Window 2.12
import marker 1.0

Window {
    width: grid.width
    height: grid.height
    visible: true
    title: qsTr("Battle-ship")

    Component {
        id: delegate

        Item {
            id: cell
            width: grid.cellWidth
            height: grid.cellHeight
            property alias source: image.source

            Image {
                mipmap: true
                smooth: true
                fillMode: Image.Stretch
                anchors.fill: parent
                source: "qrc:/Water.jpg"
            }

            Text {
                color: Qt.rgba(1, 1, 1, 1)
                font.pointSize: 24
                text: modelData.symbol
                anchors.centerIn: parent
            }

            Image {
                id: image
                mipmap: true
                smooth: true
                fillMode: Image.Stretch
                anchors.fill: parent
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                radius: 8
                border.width: 4
                border.color: "black"
            }

            states: [
                State {
                    name: "Missed"
                    when: modelData.state === Marker.Missed
                    PropertyChanges {
                        target: cell
                        source: "qrc:/missed.png"
                    }
                },
                State {
                    name: "Got"
                    when: modelData.state === Marker.Got
                    PropertyChanges {
                        target: cell
                        source: "qrc:/got.png"
                    }
                }

            ]

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(modelData.clickable)
                    {
                       if(modelData.shipOwnership)
                       {
                          console.log("Got by index ", index)
                          modelData.shipOwnership = false
                          Wrapper.setCell(index, Marker.Got)
                       }
                       else
                       {
                           console.log("Missed by index ", index)
                           Wrapper.setCell(index, Marker.Missed)
                       }
                    }
                    else
                        console.log("cell is no longer clickable ")
                }
            }

        }
    }

    GridView  {
        id: grid
        flow: GridView.FlowLeftToRight
        cellWidth: 80
        cellHeight: 80
        width: cellWidth * Wrapper.cellsInRow
        height: cellHeight * Wrapper.cellsInRow
        model: Wrapper.cells
        delegate: delegate
        focus: true
    }
}
