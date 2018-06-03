import QtQuick 2.7
import QtQuick.Controls.Styles 1.2;
import QtQuick.Controls 1.4
import com.gen.Net 1.0
import com.gen.MyRpc 1.0

Rectangle {
    id:rect;
    visible: true
    color: "#ECECEC";
    anchors.fill: parent

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
        id:game_name
        text:"RESULT"
        font.pointSize: 30
    }



    Text {
        id:text_result
        color : "#666666";
        width: 600;
        height: 350;
        wrapMode: Text.Wrap
        anchors.horizontalCenter:  rect.horizontalCenter;
        anchors.top:rect.top;
        anchors.topMargin: 100;
    }


    Button{
        text:"Reset"
        anchors.horizontalCenter:  rect.horizontalCenter;
        width:200;
        height: 35;
        anchors.bottom: rect.bottom;
        anchors.bottomMargin: 20;

        onClicked:{
            root.viewShow = 0
        }
    }

    Button{
        text:"Pub Result"
        anchors.horizontalCenter:  rect.horizontalCenter;
        width:200;
        height: 35;
        anchors.bottom: rect.bottom;
        anchors.bottomMargin: 70;

        onClicked:{
            net.getNum(root.roomid);
        }
    }


    function show_result(){
        var text="Bet Number:  "+root.bet_num+"\nAddress:  "
                +root.address+"\nmRoomid:  "
                +root.roomid+"\nUid:  "
                +root.uid+"\nScript_Address:  "
                +root.script_address;
        text_result.text=text;
    }

    Connections{
        target:net;
        onGetNumComplete:{
            console.log("onGetNumComplete: " + result);
            var json = JSON.parse(result);
            if (json.code === 0) {
                var data = JSON.parse(json.data);
                root.num0 = data.num0;
                root.num1 = data.num1;
                console.log("num0: " + data.num0);
                console.log("num1: " + data.num1);
                var mybet=root.uid==0?data.num0:data.num1;
                var advbet=root.uid==1?data.num0:data.num1;

                var text="Address:  "
                        +root.address+"\nmRoomid:  "
                        +root.roomid+"\nUid:  "
                        +root.uid+"\nScript_Address:  "
                        +root.script_address+"\nMyBetNum:  "
                        +mybet+"\nAdvBetNum:  "
                        +advbet
                text_result.text=text;
                rpc.createTx(root.fund_txid, 0, root.address, root.amount);
            } else {
                console.log("only one announce secret!!")
            }
        }
    }

    Connections{
        target:rpc;
        onCreateTxComplete:{
            console.log("onCreateTxComplete: " + result);
            var json = JSON.parse(result);
            var data = json.result;
            console.log("json.result: " + json.result);
            console.log("root.num0: " + root.num0);
            console.log("root.secret0: " + root.secret0);
            console.log("root.num1: " + root.num1);
            console.log("root.secret1: " + root.secret1);

            rpc.signTx(json.result, root.address, root.num0, root.secret0, root.num1, root.secret1);
        }
    }

    Connections{
        target:rpc;
        onSignTxComplete:{
            console.log("onSignTxComplete: " + result);
            var json = JSON.parse(result);
            var data = json.result;
            console.log("complete: ", data.complete);
            var resulet;
            if (data.complete) {
                resulet="winnerrrrrrrrrrrrrrrrrrrrrrrrrrrrrr."
                console.log("winnerrrrrrrrrrrrrrrrrrrrrrrrrrrrrr.");
                rpc.sendRawtransaction(data.hex)
            } else {
                resulet="loserrrrrrrrrrrrrrrrrrrrrrrrrrrrrr."
                console.log("loserrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr.");
            }
            var text=text_result.text+"\n"+resulet
            text_result.text=text;
        }
    }


    Connections{
        target:rpc;
        onSendRawtransactionComplete:{
            console.log("onSendRawtransactionComplete: " + result);
            var json = JSON.parse(result);
        }
    }

}
