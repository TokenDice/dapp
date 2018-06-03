#ifndef RPC_H
#define RPC_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QAuthenticator>
#include <vector>
class MyRpc : public QObject
{
    Q_OBJECT
public:
     MyRpc(QObject *parent = 0);
    ~MyRpc();
     Q_INVOKABLE void getNewAddress();
     Q_INVOKABLE void signMessage(QString address,QString num);
     Q_INVOKABLE void buildScript(QString address1,QString msg1,QString address2,QString msg2);
     Q_INVOKABLE void listUnspent();
     Q_INVOKABLE void createRawTransaction(const QString txid0,const QString txid1, const int vout0, const int vout1,
                                           const QString script_address, const QString amount,
                                           const QString change_address, const QString change );
     Q_INVOKABLE void signRawtransaction(const QString txHex);
     Q_INVOKABLE void sendRawtransaction(const QString txHex);
     Q_INVOKABLE void signTx(QString hexTx,QString address, QString num0,QString sign0, QString num1,QString sign1);
     Q_INVOKABLE void decodeRawtransaction(QString hexTx);
     Q_INVOKABLE void createTx(QString txidVout,int vout,QString address,QString amount);







private:
    QNetworkAccessManager manager;
    QNetworkReply* getnewaddress;
    QNetworkReply* signmessage;
    QNetworkReply* buildscript;
    QNetworkReply* listunspent;
    QNetworkReply* createrawtransaction;
    QNetworkReply* signrawtransaction;
    QNetworkReply* sendrawtransaction;
    QNetworkReply* signtx;
    QNetworkReply* decoderawtransacion;
    QNetworkReply* createtx;






private slots:
   void getNewAddressFinished();
   void signMessageFinished();
   void buildScriptFinished();
   void listUnspentFinished();
   void createRawTransactionFinished();
   void signRawtransactionFinished();
   void sendRawtransactionFinished();
   void signTxFinished();
   void decodeRawtransactionFinished();
   void createTxFinished();


signals:
    void getNewAddressComplete(QString result);
    void signMessageComplete(QString result);
    void buildScriptComplete(QString result);
    void listUnspentComplete(QString result);
    void createRawTransactionComplete(QString result);
    void signRawtransactionComplete(QString result);
    void sendRawtransactionComplete(QString result);
    void signTxComplete(QString result);
    void decodeRawtransactionComplete(QString result);
    void createTxComplete(QString result);
};


#endif // RPC_H
