
import "functions.js" as JS

import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1


Item {
    id:waypointItem
    width:parent.width
    height:parent.height
    property var waypointlocal:[]

    Text{
        id:desiredHeading
        font.pixelSize:parent.height*0.3
        anchors.horizontalCenter:parent.horizontalCenter
        anchors.verticalCenter:parent.verticalCenter
        text:"Active WPs: " + activeWaypoints + "\nNext WP: " + 300 +"m"
        color:darkFontColor
    }

    Button{
        id:createWp
        width:parent.width/3
        height:parent.height
        anchors.right:parent.right
        Text{
            text:"Create WP"
            font.pixelSize:parent.height*0.4
            anchors.verticalCenter:parent.verticalCenter
            anchors.horizontalCenter:parent.horizontalCenter
            color:darkFontColor
        }
        onClicked:{
            createWaypoints=true
            finishAndCreateVisible=true
    }
}
    Button{
        id:delWp
        width:parent.width/3
        height:parent.height
        anchors.left:parent.left
        Text{
            text:"Delete WP"
            font.pixelSize:parent.height*0.4
            anchors.verticalCenter:parent.verticalCenter
            anchors.horizontalCenter:parent.horizontalCenter
            color:darkFontColor
        }
        onClicked:{
        createWaypoints=false
        waypoints = []
        activeWaypoints = 0
        var i
        for (i = 0; i < guiWaypoints.length; i++) { 
            guiWaypoints[i].destroy();
        }
        guiWaypoints=[]
    }
}
    
}

