/*ÜMİT BAYRAM 20010011507*/

#ifndef BOOKS_ACTION_H
#define BOOKS_ACTION_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class book;
}

class book : public QMainWindow
{
    Q_OBJECT

public:
    explicit book(QSqlDatabase db,QWidget *parent = nullptr);
    ~book();
    void listbook();


private slots:
    void on_pushButton_yenisave_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_del_clicked();

    void on_tView_allbooks_clicked(const QModelIndex &index);

private:
    Ui::book *ui;
    QSqlQuery *query;
    QSqlQueryModel *model;
};

#endif // BOOKS_ACTION_H
