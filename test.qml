import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    id: root
    visible: true
    visibility:Window.FullScreen

    Rectangle
    {
        width: parent.width;
        height: parent.height / 2;
        color: "red"
        anchors.top: parent

        Accessible.role: Accessible.List
        Text
        {
          text: "List"
          anchors.centerIn: parent
        }

        Rectangle
        {
            width: parent.width;
            height: parent.height / 2 ;
            color: "blue"
            anchors.top: parent
            Accessible.role: Accessible.ListItem
            opacity: 1 / 3;

            Text
            {
              text: "ListItem"
              anchors.centerIn: parent
            }
        }

    }
}   
