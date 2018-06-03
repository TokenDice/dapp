#include "net.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QStringList>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

const QString baseIp="http://120.27.232.146:9009/";

const QString encodeNumberApi = baseIp+"encodeNumber";
const QString getSecretApi = baseIp+"getSecret";
const QString createFundTxApi = baseIp+"createFundTx";
const QString getFundTxApi = baseIp+"getFundTx";

const QString signFundTxApi = baseIp+"signFundTx";
const QString anounceSecretApi = baseIp+"anounceSecret";
const QString getNumApi = baseIp+"getNum";


Net::Net(QObject *parent) : QObject(parent){
    encodeNumber=nullptr;
    secret=nullptr;
    createFundTx=nullptr;
    getFundTx=nullptr;
    signfundtx=nullptr;
    anouncesecret=nullptr;
    getnum=nullptr;

}

Net::~Net(){
    if(encodeNumber){
        encodeNumber->deleteLater();
    }
    if(secret){
        secret->deleteLater();
    }
    if(createFundTx){
        createFundTx->deleteLater();
    }
    if(getFundTx){
        getFundTx->deleteLater();
    }
    if(signfundtx){
        signfundtx->deleteLater();
    }
    if(anouncesecret){
        anouncesecret->deleteLater();
    }
    if(getnum){
        getnum->deleteLater();
    }
}



void Net::getEncodeNumber(QString address,QString secret){
    if(encodeNumber){
        encodeNumber->deleteLater();
    }


    QJsonObject obj;
    obj.insert("address",address);
    obj.insert("secret",secret);
    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();

    QByteArray contentsize = QByteArray::number(dt.size());

    QUrl url(encodeNumberApi);

    QNetworkRequest request;
    request.setUrl( url );
    //set head
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );

    encodeNumber = manager.post(request , dt );

    connect(encodeNumber,SIGNAL(finished()),this,SLOT(getEncodeNumberFinished()));

}



void Net::getEncodeNumberFinished(){
    if(encodeNumber->error()){
        return;
    }
    QString result = encodeNumber->readAll();
    emit encodeNumberComplete(result);
}



void Net::getSecret(int roomid){
    if(secret){
        secret->deleteLater();
    }

    QJsonObject obj;
    obj.insert("roomid",roomid);
    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());
    QUrl url(getSecretApi);

    QNetworkRequest request;
    request.setUrl( url );
    //set head
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );

    secret = manager.post(request , dt );

    connect(secret,SIGNAL(finished()),this,SLOT(getSecretFinished()));

}

void Net::getSecretFinished(){
    if(secret->error()){
        return;
    }
    QString result = secret->readAll();
    emit getSecretComplete(result);
}



void Net::createFundtx( int uid, int roomid, QString txid, QString amount, int vout){
    if(createFundTx){
        createFundTx->deleteLater();
    }

    QJsonObject obj;
    obj.insert("uid",uid);
    obj.insert("roomid",roomid);
    obj.insert("txid",txid);
    obj.insert("amount",amount);
    obj.insert("vout",vout);

    QJsonDocument doc;
    doc.setObject( obj );

    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());
    QUrl url(createFundTxApi);

    QNetworkRequest request;
    request.setUrl( url );
    //set head
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    createFundTx = manager.post(request , dt );

    connect(createFundTx,SIGNAL(finished()),this,SLOT(getCreateFundTxFinished()));

}



void Net::getCreateFundTxFinished(){
    if(createFundTx->error()){
        return;
    }
    QString result = createFundTx->readAll();
    emit getCreateFundTxComplete(result);
}



void Net::getFundtx(int roomid){
    if(getFundTx){
        getFundTx->deleteLater();
    }
    QJsonObject obj;
    obj.insert("roomid",roomid);
    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());
    QUrl url(getFundTxApi);

    QNetworkRequest request;
    request.setUrl( url );
    //set head
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );

    getFundTx = manager.post(request , dt );

    connect(getFundTx,SIGNAL(finished()),this,SLOT(getFundTxFinished()));
}

void Net::getFundTxFinished(){
    if(getFundTx->error()){
        return;
    }
    QString result = getFundTx->readAll();
    emit getFundTxComplete(result);
}



void Net::signFundTx(int roomid,QString hex){
    if(signfundtx){
        signfundtx->deleteLater();
    }
    QJsonObject obj;
    obj.insert("roomid",roomid);
    obj.insert("hex",hex);
    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());
    QUrl url(signFundTxApi);
    QNetworkRequest request;
    request.setUrl( url );
    //set head
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    signfundtx = manager.post(request , dt );
    connect(signfundtx,SIGNAL(finished()),this,SLOT(signFundTxFinished()));
}

void Net::signFundTxFinished(){
    if(signfundtx->error()){
        return;
    }
    QString result = signfundtx->readAll();
    emit signFundTxComplete(result);
}


void Net::anounceSecret(int roomid,int num,int uid){
    if(anouncesecret){
        anouncesecret->deleteLater();
    }
    QJsonObject obj;
    obj.insert("roomid",roomid);
    obj.insert("num",num);
    obj.insert("uid",uid);
    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());
    QUrl url(anounceSecretApi);
    QNetworkRequest request;
    request.setUrl( url );
    //set head
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    anouncesecret = manager.post(request , dt );
    connect(anouncesecret,SIGNAL(finished()),this,SLOT(anounceSecretFinished()));
}

void Net::anounceSecretFinished(){
    if(anouncesecret->error()){
        return;
    }
    QString result = anouncesecret->readAll();
    emit anounceSecretComplete(result);
}

void Net::getNum(int roomid){
    if(getnum){
        getnum->deleteLater();
    }
    QJsonObject obj;
    obj.insert("roomid",roomid);
    QJsonDocument doc;
    doc.setObject( obj );
    QByteArray dt = doc.toJson();
    QByteArray contentsize = QByteArray::number(dt.size());
    QUrl url(getNumApi);
    QNetworkRequest request;
    request.setUrl( url );
    //set head
    request.setRawHeader("content-type","application/json");
    request.setRawHeader("content-length",contentsize );
    getnum = manager.post(request , dt );
    connect(getnum,SIGNAL(finished()),this,SLOT(getNumFinished()));
}

void Net::getNumFinished(){
    if(getnum->error()){
        return;
    }

    QString result = getnum->readAll();
    emit getNumComplete(result);
}

