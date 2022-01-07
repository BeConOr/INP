#include "database.h"

DataBase::DataBase(QString name, QObject *parent)
    : QObject{parent}
{
    dbname = name;
}

void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile(DATABASE_NAME).exists()){
            this->restoreDataBase();
        } else {
            this->openDataBase();
        }
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(DATABASE_NAME);
//    if(!db.open()){
//        qDebug() << db.lastError().text();
//    }
//    QSqlQuery query("SHOW TABLES", db);
//    qDebug() << query.
//    db = QSqlDatabase::database(DATABASE_NAME);
}

bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if((!this->createTableC() || !this->createTableK())){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DataBase::closeDataBase()
{
    db.close();
}

bool DataBase::createTableC()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query(db);
    if(!query.exec("CREATE TABLE " COLOR_TABLE " ("
                        "'Color_id'	INTEGER NOT NULL, "
                        "'Color_name'	TEXT NOT NULL, "
                        "'Image_name'	TEXT NOT NULL, "
                        "'Image'	BLOB NOT NULL, "
                        "'Number'	INTEGER NOT NULL, "
                        "PRIMARY KEY('Color_id' AUTOINCREMENT)"
                   " )")){
        qDebug() << "DataBase: error of create " << COLOR_TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::createTableK()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query(db);
    if(!query.exec("CREATE TABLE " KNIFE_TABLE " ("
                       "'Knife_id'	INTEGER NOT NULL, "
                       "'Knife_name_RUS'	TEXT NOT NULL, "
                       "'Knife_name_ENG'	TEXT NOT NULL, "
                       "'Exp_color_name'	TEXT, "
                       "'Exp_color_cost'	TEXT, "
                       "'Knife_image_name'	TEXT NOT NULL, "
                       "'Knife_image'	BLOB NOT NULL, "
                       "'Cost'	REAL NOT NULL DEFAULT 0.0, "
                       "'isKnife'	INTEGER NOT NULL DEFAULT 1, "
                       "PRIMARY KEY('Knife_id' AUTOINCREMENT)"
                   " )")){
        qDebug() << "DataBase: error of create " << KNIFE_TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::insertIntoColor(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query(db);
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " COLOR_TABLE " ('Color_name', 'Image_name', 'Image', 'Number') VALUES (?, ?, ?, ?)");
    query.addBindValue(data[0].toString());
    query.addBindValue(data[1].toString());
    query.addBindValue(data[2].toByteArray());
    query.addBindValue(data[3].toInt());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << COLOR_TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::insertIntoKnife(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query(db);
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " KNIFE_TABLE " ('Knife_name_RUS', 'Knife_name_ENG', 'Exp_color_name', 'Exp_color_cost', 'Knife_image_name', 'Knife_image', 'Cost', 'isKnife') "
                  "VALUES (:RUS, :ENG, :Col_name, :Col_cost, :Name, :Image, :Cost, :isKnife)");
    query.bindValue(":RUS",        data[0].toString());
    query.bindValue(":ENG",        data[1].toString());
    query.bindValue(":Col_name",      data[2].toString());
    query.bindValue(":Col_cost",      data[3].toString());
    query.bindValue(":Name",      data[4].toString());
    query.bindValue(":Image",      data[5].toByteArray());
    query.bindValue(":Cost",      data[6].toDouble());
    query.bindValue(":isKnife",      data[7].toInt());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << KNIFE_TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

QList<Co> DataBase::selectColor(){
    QSqlQuery query(db);
    QList<Co> record;
    if(!query.exec("SELECT Color_id, Color_name, Image_name, Image, Number FROM " COLOR_TABLE)){
        qDebug() << "DataBase: error of select from " << COLOR_TABLE;
        qDebug() << query.lastError().text();
    }
    while(query.next()){
        if(query.value(0) != 0){
            Co data;
            data.id = query.value(0).toInt();
            data.rus = query.value(1).toString();
            data.imgName = query.value(2).toString();
            data.img = query.value(3).toByteArray();
            data.number = query.value(4).toInt();
            record.append(data);
        }else{
            Co data;
            data.id = query.value(0).toInt();
            record.append(data);
        }
    }
    return record;
}

QList<Kn> DataBase::selectKnife(){
    QSqlQuery query(db);
    QList<Kn> record;
    if(!query.exec("SELECT Knife_id, Knife_name_RUS, Knife_name_ENG, Exp_color_name, Exp_color_cost, Knife_image_name, Knife_image, Cost, isKnife FROM " KNIFE_TABLE)){
        qDebug() << "DataBase: error of select from " << KNIFE_TABLE;
        qDebug() << query.lastError().text();
    }
    while(query.next()){
        if(query.value(0) != 0){
            Kn data;
            data.id = query.value(0).toInt();
            data.rus = query.value(1).toString();
            data.eng = query.value(2).toString();
            data.colHigh = query.value(3).toString();
            data.cosHigh = query.value(4).toString();
            data.imgName = query.value(5).toString();
            data.img = query.value(6).toByteArray();
            data.cost = query.value(7).toDouble();
            data.isKnife = query.value(8).toInt();
            record.append(data);
        }else{
            Kn data;
            data.id = query.value(0).toInt();
            record.append(data);
        }
    }
    return record;
}

void DataBase::deleteKn(int id){
    QSqlQuery query(db);

    query.prepare("DELETE FROM " KNIFE_TABLE " WHERE Knife_id = :id");
    query.bindValue(":id" ,id);

    if(!query.exec()){
        qDebug() << "DataBase: error of delete from " << KNIFE_TABLE;
        qDebug() << query.lastError().text();
    }
}

void DataBase::deleteCo(int id){
    QSqlQuery query(db);

    query.prepare("DELETE FROM " COLOR_TABLE " WHERE Color_id = :id");
    query.bindValue(":id", id);

    if(!query.exec()){
        qDebug() << "DataBase: error of delete from " << COLOR_TABLE;
        qDebug() << query.lastError().text();
    }
}

Kn DataBase::selectK(int id){
    QSqlQuery query(db);
    query.prepare("SELECT Knife_id, Knife_name_RUS, Knife_name_ENG, Exp_color_name, Exp_color_cost, Knife_image_name, Knife_image, Cost, isKnife FROM " KNIFE_TABLE " WHERE Knife_id = :id");
    query.bindValue(":id" ,id);
    if(!query.exec()){
        qDebug() << "DataBase: error of select from " << KNIFE_TABLE;
        qDebug() << query.lastError().text();
    }
    query.next();
    Kn data;
    data.id = query.value(0).toInt();
    data.rus = query.value(1).toString();
    data.eng = query.value(2).toString();
    data.colHigh = query.value(3).toString();
    data.cosHigh = query.value(4).toString();
    data.imgName = query.value(5).toString();
    data.img = query.value(6).toByteArray();
    data.cost = query.value(7).toDouble();
    data.isKnife = query.value(8).toInt();
    return data;
}

bool DataBase::updateKnife(const QVariantList &data, int id)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query(db);
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("UPDATE " KNIFE_TABLE " SET Knife_name_RUS = ?, Knife_name_ENG = ?, Exp_color_name = ?, Exp_color_cost = ?, Knife_image_name = ?, Knife_image = ?, Cost = ?, isKnife = ? "
                  "WHERE Knife_id = ?");
    query.addBindValue(data[0].toString());
    query.addBindValue(data[1].toString());
    query.addBindValue(data[2].toString());
    query.addBindValue(data[3].toString());
    query.addBindValue(data[4].toString());
    query.addBindValue(data[5].toByteArray());
    query.addBindValue(data[6].toDouble());
    query.addBindValue(data[7].toInt());
    query.addBindValue(id);
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error update into " << KNIFE_TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
