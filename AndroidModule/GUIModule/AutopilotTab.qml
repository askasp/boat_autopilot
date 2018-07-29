
import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1

Item {
    property int psi_D:0
    id:headings
    width:parent.width
    height:parent.height
    Text{
        id:desiredHeading
        font.pixelSize:parent.height*0.3
        anchors.horizontalCenter:parent.horizontalCenter
        anchors.verticalCenter:parent.verticalCenter
        text:"ψ_desired: " + psi_D + "°" + "\nψ_error" 
        color:darkFontColor
    }

    Button{
        id:minus1
        width:parent.width/6
        height:parent.height
        Text{
            text:"-10°" 
            font.pixelSize:parent.height*0.4
            anchors.verticalCenter:parent.verticalCenter
            anchors.horizontalCenter:parent.horizontalCenter
            color:darkFontColor
        }
        onClicked:{
            if(psi_D <= 9){
                psi_D = 360+psi_D
            }
            psi_D -=10
            myOutMessage.updatePsi_D(psi_D)
        }
    }
    Button{
        anchors.left:minus1.right
        width:parent.width/6
        height:parent.height
        Text{
            text:"-1°" 
            font.pixelSize:parent.height*0.4
            anchors.verticalCenter:parent.verticalCenter
            anchors.horizontalCenter:parent.horizontalCenter
            color:darkFontColor
        }
        onClicked:{
            if(psi_D <= 1){
                psi_D = 360 +psi_D
            }
            psi_D -=1
            myOutMessage.updatePsi_D(psi_D)
        }

    }
    Button{
        anchors.right:parent.right
        id:pluss10
        width:parent.width/6
        height:parent.height
        Text{
            text:"+10°" 
            font.pixelSize:parent.height*0.4
            anchors.verticalCenter:parent.verticalCenter
            anchors.horizontalCenter:parent.horizontalCenter
            color:darkFontColor
        }
        onClicked:{
            if(psi_D >= 350){
                psi_D = (psi_D-360)
            }
            psi_D +=10
            myOutMessage.updatePsi_D(psi_D)
        }
    }
    Button{
        anchors.right:pluss10.left
        width:parent.width/6
        height:parent.height
        Text{
            text:"+1°" 
            font.pixelSize:parent.height*0.4
            anchors.verticalCenter:parent.verticalCenter
            anchors.horizontalCenter:parent.horizontalCenter
            color:darkFontColor
        }
        onClicked:{
            if(psi_D >= 359){
                psi_D = (psi_D-360)
            }
            psi_D +=1
            myOutMessage.updatePsi_D(psi_D)
        }

    }
}
