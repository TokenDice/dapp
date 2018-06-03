#include "myrpc.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QStringList>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <iostream>

const QString baseIp="http://127.0.0.1:18332/";
QByteArray authenticator;


MyRpc::MyRpc(QObject *parent) : QObject(parent){
    getnewaddress=nullptr;
    signmessage=nullptr;
    buildscript=nullptr;
    listunspent = nullptr;
    createrawtransaction=nullptr;
    signrawtransaction = nullptr;
    sendrawtransaction = nullptr;
    signtx = nullptr;
   decoderawtransacion= nullptr;
     createtx= nullptr;

    QByteArray array("cf:mymm");
    QString temp="Basic "+array.toBase64();
    authenticator=temp.toUtf8();
}

MyRpc::~MyRpc(){
}



void MyRpc::getNewAddress(){
    if(getnewaddress){
        getnewaddress->deleteLater();
    }

    QJsonObject obj;
    QJsonArray params;
    obj.insert("jsonrpc","1.0");
    obj.insert("id","curltest");
    obj.insert("method","getnewaddress");
    obj.insert("params",params);
    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(baseIp);
    QNetworkRequest request;
    request.setUrl( url );
    //set head

    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    request.setRawHeader("authorization",authenticator );
    getnewaddress= manager.post(request,dt);
    connect(getnewaddress,SIGNAL(finished()),this,SLOT(getNewAddressFinished()));
}



void MyRpc::getNewAddressFinished(){
    if(getnewaddress->error()){
        return;
    }
    QString result = getnewaddress->readAll();
    emit getNewAddressComplete(result);
}


void MyRpc::signMessage(QString address,QString num){
    if(signmessage){
        signmessage->deleteLater();
    }

    QJsonObject obj;
    QJsonArray params;
    params.append(address);
    params.append(num);

    obj.insert("jsonrpc","1.0");
    obj.insert("id","curltest");
    obj.insert("method","signmessage");
    obj.insert("params",params);
    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(baseIp);
    QNetworkRequest request;
    request.setUrl( url );
    //set head

    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    request.setRawHeader("authorization",authenticator );
    signmessage= manager.post(request,dt);
    connect(signmessage,SIGNAL(finished()),this,SLOT(signMessageFinished()));
}



void MyRpc::signMessageFinished(){
    if(signmessage->error()){
        return;
    }
    QString result = signmessage->readAll();
    emit signMessageComplete(result);
}



void MyRpc::buildScript(QString address1,QString msg1,QString address2,QString msg2){
    if(buildscript){
        buildscript->deleteLater();
    }

    QJsonObject obj;
    QJsonArray params;
    params.append(address1);
    params.append(msg1);
    params.append(address2);
    params.append(msg2);

    obj.insert("jsonrpc","1.0");
    obj.insert("id","curltest");
    obj.insert("method","buildscript");
    obj.insert("params",params);
    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(baseIp);
    QNetworkRequest request;
    request.setUrl( url );
    //set head

    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    request.setRawHeader("authorization",authenticator );
    buildscript = manager.post(request,dt);
    connect(buildscript, SIGNAL(finished()),this,SLOT(buildScriptFinished()));
}



void MyRpc::buildScriptFinished(){
    if(buildscript->error()){
        std::cout << "error: " << buildscript->error() << std::endl;
        return;
    }
    QString result = buildscript->readAll();
    emit buildScriptComplete(result);
}


void MyRpc::listUnspent(){
    if(listunspent){
        listunspent->deleteLater();
    }

    QJsonObject obj;
    QJsonArray params;
    obj.insert("jsonrpc","1.0");
    obj.insert("id","curltest");
    obj.insert("method","listunspent");
    obj.insert("params",params);
    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(baseIp);
    QNetworkRequest request;
    request.setUrl( url );
    //set head

    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    request.setRawHeader("authorization",authenticator );
    listunspent= manager.post(request,dt);
    connect(listunspent,SIGNAL(finished()),this,SLOT(listUnspentFinished()));
}

void MyRpc::createRawTransaction(const QString txid0, const QString txid1, const int vout0, const int vout1,
                                 const QString script_address, const QString amount,
                                 const QString change_address, const QString change)
{
    if(createrawtransaction){
        createrawtransaction->deleteLater();
    }
    QJsonArray vinTx;

    QJsonObject txTemp;
    txTemp.insert("txid",txid0);
    txTemp.insert("vout",vout0);
    vinTx.append(txTemp);
    QJsonObject txTemp1;
    txTemp1.insert("txid",txid1);
    txTemp1.insert("vout",vout1);
    vinTx.append(txTemp1);

    QJsonObject voutTx;
    voutTx.insert(script_address, amount);

    if (!change_address.toStdString().empty())
        voutTx.insert(change_address, change);

    QJsonObject obj;
    QJsonArray params;
    params.append(vinTx);
    params.append(voutTx);
    obj.insert("jsonrpc","1.0");
    obj.insert("id","curltest");
    obj.insert("method","createrawtransaction");
    obj.insert("params",params);

    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(baseIp);
    QNetworkRequest request;
    request.setUrl( url );
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    request.setRawHeader("authorization",authenticator );
    createrawtransaction= manager.post(request,dt);
    connect(createrawtransaction,SIGNAL(finished()),this,SLOT(createRawTransactionFinished()));
}

void MyRpc::signRawtransaction(const QString  txHex)
{
    if(signrawtransaction){
        signrawtransaction->deleteLater();
    }
    QJsonObject obj;
    QJsonArray params;
    params.append(txHex);
    obj.insert("jsonrpc","1.0");
    obj.insert("id","curltest");
    obj.insert("method","signrawtransaction");
    obj.insert("params",params);

    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(baseIp);
    QNetworkRequest request;
    request.setUrl( url );
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    request.setRawHeader("authorization",authenticator );
    signrawtransaction = manager.post(request,dt);
    connect(signrawtransaction,SIGNAL(finished()),this,SLOT(signRawtransactionFinished()));
}

void MyRpc::sendRawtransaction(const QString txHex)
{

    if(sendrawtransaction){
        sendrawtransaction->deleteLater();
    }
    QJsonObject obj;
    QJsonArray params;
    params.append(txHex);

    std::cout << "txxxxhex:" << txHex.toStdString() << std::endl;

    obj.insert("jsonrpc","1.0");
    obj.insert("id","curltest");
    obj.insert("method","sendrawtransaction");
    obj.insert("params",params);

    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(baseIp);
    QNetworkRequest request;
    request.setUrl( url );
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    request.setRawHeader("authorization",authenticator );
    sendrawtransaction = manager.post(request,dt);
    connect(sendrawtransaction,SIGNAL(finished()),this,SLOT(sendRawtransactionFinished()));
}

void MyRpc::signTx(QString hexTx, QString address, QString num0, QString sign0, QString num1, QString sign1)
{
    if(signtx){
        signtx->deleteLater();
    }
    QJsonObject obj;
    QJsonArray params;
    params.append(hexTx);
    params.append(address);
    params.append(num0);
    params.append(sign0);
    params.append(num1);
    params.append(sign1);
    obj.insert("jsonrpc","1.0");
    obj.insert("id","curltest");
    obj.insert("method","signtx");
    obj.insert("params",params);

    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(baseIp);
    QNetworkRequest request;
    request.setUrl( url );
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    request.setRawHeader("authorization",authenticator );
    signtx = manager.post(request,dt);
    connect(signtx,SIGNAL(finished()),this,SLOT(signTxFinished()));
}

void MyRpc::decodeRawtransaction(QString hexTx)
{
    if(decoderawtransacion){
        decoderawtransacion->deleteLater();
    }
    QJsonObject obj;
    QJsonArray params;
    params.append(hexTx);

    std::cout << "txxxxhex:" << hexTx.toStdString() << std::endl;

    obj.insert("jsonrpc","1.0");
    obj.insert("id","curltest");
    obj.insert("method","decoderawtransaction");
    obj.insert("params",params);

    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(baseIp);
    QNetworkRequest request;
    request.setUrl( url );
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    request.setRawHeader("authorization",authenticator );
    decoderawtransacion = manager.post(request,dt);
    connect(decoderawtransacion,SIGNAL(finished()),this,SLOT(decodeRawtransactionFinished()));

}

void MyRpc::createTx(QString txidVout, int vout, QString address, QString amount)
{
    if(createtx){
        createtx->deleteLater();
    }
    QJsonArray vinTx;

    QJsonObject txTemp;
    txTemp.insert("txid",txidVout);
    txTemp.insert("vout",vout);
    vinTx.append(txTemp);


    QJsonObject voutTx;
    voutTx.insert(address, amount);
    QJsonObject obj;
    QJsonArray params;
    params.append(vinTx);
    params.append(voutTx);
    obj.insert("jsonrpc","1.0");
    obj.insert("id","curltest");
    obj.insert("method","createrawtransaction");
    obj.insert("params",params);

    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(baseIp);
    QNetworkRequest request;
    request.setUrl( url );
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    request.setRawHeader("authorization",authenticator );
    createtx= manager.post(request,dt);
    connect(createtx,SIGNAL(finished()),this,SLOT(createTxFinished()));
}


void MyRpc::listUnspentFinished(){
    if(listunspent->error()){
        return;
    }
    QString result = listunspent->readAll();
    emit listUnspentComplete(result);
}

void MyRpc::createRawTransactionFinished()
{
    if(createrawtransaction->error()){
        std::cout << "createrawtransaction->error(): " << createrawtransaction->error() << std::endl;
        return;
    }
    QString result = createrawtransaction->readAll();
    emit createRawTransactionComplete(result);
}

void MyRpc::signRawtransactionFinished()
{
    if(signrawtransaction->error()){
        return;
    }
    QString result = signrawtransaction->readAll();
    emit signRawtransactionComplete(result);
}

void MyRpc::sendRawtransactionFinished()
{
    if(sendrawtransaction->error()){
        std::cout << sendrawtransaction->error() << std::endl;
        return;
    }
    QString result = sendrawtransaction->readAll();
    emit sendRawtransactionComplete(result);
}

void MyRpc::signTxFinished()
{
    if(signtx->error()){
        return;
    }
    QString result = signtx->readAll();
    emit signTxComplete(result);
}

void MyRpc::decodeRawtransactionFinished()
{
    if(decoderawtransacion->error()){
        return;
    }
    QString result = decoderawtransacion->readAll();
    emit decodeRawtransactionComplete(result);
}

void MyRpc::createTxFinished()
{
    if(createtx->error()){
        return;
    }

    QString result = createtx->readAll();

    emit createTxComplete(result);
}
