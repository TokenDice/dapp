import QtQuick 2.7
import QtQuick.Controls.Styles 1.2;
import QtQuick.Controls 1.4
import com.gen.Net 1.0
import com.gen.MyRpc 1.0

Rectangle {
    id:rect;
    visible: true
    color: "#ECECEC";
    anchors.fill: parent;

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
        text:"Playing"
        font.pointSize: 30
    }



    Rectangle{
        id:rect_bet_coin
        width:200;
        height: 38;
        anchors.horizontalCenter:  rect.horizontalCenter;
        anchors.top:rect.top;
        anchors.topMargin:100;
        Text {
            id:coin_name
            text:"Bet Coin："
            anchors.left: parent.left;
            anchors.verticalCenter: rect_bet_coin.verticalCenter;
            anchors.margins:25;
        }
        TextInput{
            id:game_coin;
            anchors.left: coin_name.right;
            anchors.leftMargin: 15;
            width:249;
            height: 38;
            font.pixelSize: 14;
            focus: true;
            color:"#6b6b6b";
            verticalAlignment: Text.AlignVCenter;
            maximumLength:20;
            activeFocusOnPress: true
        }
    }

    Button{
        text:"Create Game"
        anchors.horizontalCenter: rect.horizontalCenter;
        width:200;
        height:35;
        anchors.top:rect.top;
        anchors.topMargin:150;

        onClicked:{
            net.getSecret(root.roomid);
        }
    }

    Button{
        text:"Create Tx"
        anchors.horizontalCenter: rect.horizontalCenter;
        width:200;
        height:35;
        anchors.top:rect.top;
        anchors.topMargin:200;

        onClicked:{
            rpc.listUnspent();
        }
    }

    Button{
        text:"Sign Tx"
        anchors.horizontalCenter: rect.horizontalCenter;
        width:200;
        height:35;
        anchors.top:rect.top;
        anchors.topMargin:250;

        onClicked:{
            net.getFundtx(root.roomid);
        }
    }


    Button{
        text:"Announce Secret"
        anchors.horizontalCenter:  rect.horizontalCenter;
        width:150;
        height: 35;
        anchors.bottom: rect.bottom;
        anchors.bottomMargin: 30;

        onClicked:{
            if (root.uid === 0) {
                net.getFundtx(root.roomid);
            } else {
                net.anounceSecret(root.roomid, root.bet_num, root.uid);
            }
        }
    }
    Connections{
        target:net;
        onGetSecretComplete:{
            console.log("onGetSecretComplete: " + result);
            var json = JSON.parse(result);
            if (json.code !== 0) {
                console.log("Wait for rival sending message. ");
                return;
            }

            var data = JSON.parse(json.data);
            root.secret0 = data.secret0;
            root.secret1 = data.secret1;
            rpc.buildScript(data.address0, data.secret0, data.address1, data.secret1);
        }
    }


    Connections{
        target:rpc;
        onBuildScriptComplete:{
            console.log("onBuildScriptComplete: " + result);
            var json = JSON.parse(result);
            var data = json.result;
            root.script_address = data.address;
            root.script = json.script;
        }
    }

    Connections{
        target:rpc;
        onListUnspentComplete:{
            console.log("onListUnspentComplete: " + result);
            var json = JSON.parse(result);
            var tx = json.result;
            net.createFundtx(root.uid, root.roomid, tx[0].txid, tx[0].amount, tx[0].vout);
        }
    }

    Connections{
        target:net;
        onGetCreateFundTxComplete:{
            console.log("onGetCreateFundTxComplete: " + result);
            var json = JSON.parse(result);
            if (json.code !== 0) {
                console.log("onGetCreateFundTxComplete error. ");
            }
        }
    }

    Connections{
        target:net;
        onGetFundTxComplete:{
            console.log("onGetFundTxComplete: " + result);
            var json = JSON.parse(result);
            if (json.code !== 0) {
                console.log("onGetFundTxComplete error. ");
                return;
            }

            var data = JSON.parse(json.data);
            var hex = data.hexTx;

            console.log("root.uid: " + root.uid);
            console.log("txid0: " + data.txid0);
            console.log("hex: " + data.hexTx);
            console.log("root.script_address: " + root.script_address);
            console.log("data.scriptAmount: " + data.scriptAmount);

            root.amount = data.scriptAmount;

            if (root.uid === 0 && hex === "" && data.txid0 !== "" && data.txid1 !== "") {
                rpc.createRawTransaction(data.txid0, data.txid1, data.vout0, data.vout1,
                                         root.script_address, data.scriptAmount, data.changeAddress, data.change);
            }
            else if (root.uid === 1 && hex !== "") {
                rpc.signRawtransaction(hex);
            }
            else if (root.uid === 0 && hex !== "" && data.txid0 !== "" && data.txid1 !== "") {
                rpc.decodeRawtransaction(hex);
            }
        }
    }

    Connections{
        target:rpc;
        onCreateRawTransactionComplete:{
            console.log("onCreateRawTransactionComplete: " + result);
            var json = JSON.parse(result);
            rpc.signRawtransaction(json.result);
        }
    }

    Connections{
        target:rpc;
        onSignRawtransactionComplete:{
            console.log("onSignRawtransactionComplete: " + result);
            var json = JSON.parse(result);
            var data = json.result;
            if (root.uid === 0) {
                net.signFundTx(root.roomid, data.hex);
            } else {
                net.signFundTx(root.roomid, data.hex);
                rpc.sendRawtransaction(data.hex);
            }
        }
    }

    Connections{
        target:net;
        onSignFundTxComplete:{
            console.log("onSignFundTxComplete: " + result);
            var json = JSON.parse(result);
            if (json.code !== 0) {
                console.log("onSignFundTxComplete error. ");
            }
        }
    }

    Connections{
        target:rpc;
        onSendRawtransactionComplete:{
            console.log("onSendRawtransactionComplete: " + result);
            var json = JSON.parse(result);
            root.fund_txid = json.result;
        }
    }


    Connections{
        target:rpc;
        onDecodeRawtransactionComplete:{
            console.log("onDecodeRawtransactionComplete: " + result);
            var json = JSON.parse(result);
            var data = json.result;
            root.fund_txid = data.txid;
            net.anounceSecret(root.roomid, root.bet_num, root.uid);
        }
    }

    Connections{
        target:net;
        onAnounceSecretComplete:{
            console.log("onAnounceSecretComplete: " + result);
            var json = JSON.parse(result);
            console.log("fund_txid: ", root.fund_txid);
            root.setResult();
            root.viewShow = 2;
        }
    }

}
