/*ÜMİT BAYRAM 20010011507*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnMember_clicked();

    void on_btnBook_clicked();

    void on_btnOdncal_clicked();

    void on_btnOdnctslm_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db ;
};
#endif // MAINWINDOW_H



