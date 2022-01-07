#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>

#define DATABASE_NAME "ShopDB.db"
#define COLOR_TABLE "ColorPaper"
#define KNIFE_TABLE "KnifeTable"


struct Kn{
    int id;
    QString rus;
    QString eng;
    QString colHigh;
    QString cosHigh;
    QString imgName;
    QByteArray img;
    double cost;
    int isKnife;
    QString dbname;
};

struct Co{
    int id;
    QString rus;
    QString imgName;
    QByteArray img;
    int number;
};



class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QString name, QObject *parent = nullptr);
    void connectToDataBase();
    bool insertIntoColor(const QVariantList &data);
    bool insertIntoKnife(const QVariantList &data);
    QList<Co> selectColor();
    QList<Kn> selectKnife();
    Kn selectK(int id);
    void deleteKn(int id);
    void deleteCo(int id);
    bool updateKnife(const QVariantList &data, int id);
private:
    QSqlDatabase db;
    QString dbname;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTableC();
    bool createTableK();

};

#endif // DATABASE_H
