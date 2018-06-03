import QtQuick 2.7
import QtQuick.Controls.Styles 1.2;
import QtQuick.Controls 1.4
import com.gen.Net 1.0
import com.gen.MyRpc 1.0

Rectangle {
    id:rect;
    visible: true
    color: "#ECECEC";
    anchors.fill: parent ;

    Net{
        id:net;
    }
    MyRpc{
        id:rpc;
    }


    Text {
        color : "#000000";
        anchors.top:rect.top;
        anchors.topMargin: 20;
        anchors.horizontalCenter:  rect.horizontalCenter;
        text:"Start Game"
        font.pointSize: 30
    }


    Rectangle{
        id:rect_bet_num
        width:297;
        height: 38;
        anchors.verticalCenter: rect.verticalCenter;
        anchors.horizontalCenter:  rect.horizontalCenter;

        Text {
            id:bet_name
            text:"Random_Number:"
            anchors.left: parent.left;
            anchors.verticalCenter: rect_bet_num.verticalCenter;
            anchors.margins:25;
        }
        TextInput{
            id:bet_text;
            anchors.left: bet_name.right;
            anchors.leftMargin: 20;
            width:249;
            height: 38;
            font.pixelSize: 14;
            focus: true;
            color:"#6b6b6b";
            verticalAlignment: Text.AlignVCenter;
            maximumLength:20;
            activeFocusOnPress: true
            anchors.verticalCenter: rect_bet_num.verticalCenter;
        }
    }




    Button{
        id:start_btn
        text:"Start"
        anchors.horizontalCenter:  rect.horizontalCenter;
        width:200;
        height: 35;
        anchors.bottom: rect.bottom;
        anchors.bottomMargin: 50;

        onClicked:{
            var num=bet_text.text;
            //            if(num.getL>0){
            root.bet_num=num;
            //                 start_btn.enabled=false;
            rpc.getNewAddress();
        }
    }

    Connections{
        target:rpc;
        onGetNewAddressComplete:{
            console.log("onGetNewAddressComplete:" + result);
            var newaddress=JSON.parse(result);
            root.address= newaddress.result;
            rpc.signMessage(root.address,root.bet_num);
        }
    }

    Connections{
        target:rpc;
        onSignMessageComplete:{
            console.log("onSignMessageComplete:" + result);
            var signmsg=JSON.parse(result);
            root.ciphertext= signmsg.result;
            net.getEncodeNumber(root.address,root.ciphertext);
        }
    }


    Connections{
        target:net;
        onEncodeNumberComplete:{
            console.log("onEncodeNumberComplete: " + result);
            var msg=JSON.parse(result);
            root.roomid=msg.roomid;
            root.uid=msg.uid;
            root.viewShow = 1;
            bet_text.text=""
        }
    }
}
