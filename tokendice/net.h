#ifndef NET_H
#define NET_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>

class Net : public QObject
{
    Q_OBJECT
public:
    explicit Net(QObject *parent = 0);
    ~Net();

    Q_INVOKABLE void getEncodeNumber( QString address, QString secret);
    Q_INVOKABLE void getSecret(int roomid);
    Q_INVOKABLE void createFundtx( int uid, int roomid, QString txid, QString amount, int vout);
    Q_INVOKABLE void getFundtx(const int roomid);

    Q_INVOKABLE void signFundTx(int roomid,QString hex);
    Q_INVOKABLE void anounceSecret(  int roomid, int num, int uid);
    Q_INVOKABLE void getNum( int roomid);

private:
    QNetworkAccessManager manager;
    QNetworkReply* encodeNumber;
    QNetworkReply* secret;
    QNetworkReply* createFundTx;
    QNetworkReply* getFundTx;

    QNetworkReply* signfundtx;
    QNetworkReply* anouncesecret;
    QNetworkReply* getnum;


private slots:
    void getEncodeNumberFinished();
    void getSecretFinished();
    void getCreateFundTxFinished();
    void getFundTxFinished();

    void signFundTxFinished();
    void anounceSecretFinished();
    void getNumFinished();


signals:
    void encodeNumberComplete(QString result);
    void getSecretComplete(QString result);
    void getCreateFundTxComplete(QString result);
    void getFundTxComplete(QString result);

    void signFundTxComplete(QString result);
    void anounceSecretComplete(QString result);
    void getNumComplete(QString result);
};


#endif // NET_H
