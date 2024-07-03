/*ÜMİT BAYRAM 20010011507*/
#ifndef ODUNCALMA_H
#define ODUNCALMA_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class oduncalma;
}

class oduncalma : public QMainWindow
{
    Q_OBJECT

public:
    explicit oduncalma(QSqlDatabase db,QWidget *parent = nullptr);
    ~oduncalma();
    void listbook();
    void listmember();
    void oduncalinanktplistele();

private slots:
    void on_btn_odncAl_clicked();

    void on_tView_books_clicked(const QModelIndex &index);

    void on_tView_members_clicked(const QModelIndex &index);

private:
    Ui::oduncalma *ui;
    QSqlQueryModel *model;
    QSqlQueryModel *modelmember;
    QSqlQueryModel *modelbook;
    QSqlQueryModel *modeloduncalinan;
    QSqlQuery *query;
    QSqlQuery *querymember;
    QSqlQuery *querybook;
    QSqlQuery *queryoduncalinan;
    QSqlQuery *queryAynikitapalinmismi;

};

#endif // ODUNCALMA_H
