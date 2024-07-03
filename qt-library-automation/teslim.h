/*ÜMİT BAYRAM 20010011507*/
#ifndef TESLIM_H
#define TESLIM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QModelIndex>
#include <QModelIndexList>
#include <QDate>


namespace Ui {
class teslim;
}

class teslim : public QMainWindow
{
    Q_OBJECT

public:
    explicit teslim(QSqlDatabase db,QWidget *parent = nullptr);
    ~teslim();

    void oduncalinanktplistele();
    void teslimedilenkitapListele();

private slots:
    void on_btn_odncVer_clicked();

    void on_tView_odncalinanbooks_clicked(const QModelIndex &index);



private:
    Ui::teslim *ui;
    QSqlQueryModel *modeloduncalinan;
    QSqlQuery *queryoduncalinan;
    QSqlQueryModel *modelteslimalinan;
    QSqlQuery *queryteslimalinan;
    QSqlQuery *query;
};

#endif // TESLIM_H
