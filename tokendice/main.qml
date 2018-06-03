import QtQuick 2.7
import QtQuick.Window 2.2;

Window {
    id: root;
    visible: true;

    width: 650;
    height: 400;
    title: qsTr("Token Dice");

    property int viewShow:0;
    property var bet_num;
    property var address;
    property var ciphertext;
    property var roomid;
    property var uid;

    property var script_address;
    property var script;
    property var amount;

    property var fund_txid;

    property var num0;
    property var num1;
    property var secret0;
    property var secret1;

    PageBetNum {
        id:view_num
        visible: viewShow == 0
    }

    PageBetCoin {
        id:view_coin
        visible: viewShow == 1
    }

    PageResult {
        id:view_result
        visible: viewShow == 2
    }

    function setResult(){
    view_result.show_result();
    }


}
