/*ÜMİT BAYRAM 20010011507*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "books_action.h"
#include "member.h"
#include "oduncalma.h"
#include "teslim.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("20010011507.db");
    if(!db.open())
    {
        ui->statusBar->showMessage("Veri tabanına bağlanılamadı.");
    }

    else
    {
        ui->statusBar->showMessage("Veri tabanına bağlanıldı");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnMember_clicked()
{
    member *uye = new member(db);
    uye->show();
}


void MainWindow::on_btnBook_clicked()
{
    book *ktp = new book(db);
    ktp->show();
}


void MainWindow::on_btnOdncal_clicked()
{
    oduncalma *odnc = new oduncalma(db);
    odnc->show();
}


void MainWindow::on_btnOdnctslm_clicked()
{
    teslim *tslm = new teslim(db);
    tslm->show();
}

