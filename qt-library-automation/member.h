/*ÜMİT BAYRAM 20010011507*/
#ifndef MEMBER_H
#define MEMBER_H

#include <QMainWindow>
#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class member;
}

class member : public QMainWindow
{
    Q_OBJECT

public:
    explicit member(QSqlDatabase db,QWidget *parent = nullptr);
    ~member();
    void listmember();

private slots:
    void on_btn_yenimember_clicked();

    void on_btn_update_clicked();

    void on_btn_del_clicked();

    void on_tView_members_clicked(const QModelIndex &index);

private:
    Ui::member *ui;
    QSqlQuery *query;
    QSqlQueryModel *model;

};

#endif // MEMBER_H

