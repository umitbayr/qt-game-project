/*ÜMİT BAYRAM 20010011507*/

#include "teslim.h"
#include "ui_teslim.h"
#include "QDateEdit"

teslim::teslim(QSqlDatabase db,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::teslim)
{
    ui->setupUi(this);
    queryoduncalinan = new QSqlQuery(db);
    queryteslimalinan = new QSqlQuery(db);
    query = new QSqlQuery(db);
    oduncalinanktplistele();
    teslimedilenkitapListele();
}

teslim::~teslim()
{
    delete ui;
}
QDate almatarihi;

QString alma_tarihi;
void teslim::oduncalinanktplistele()
{
    queryoduncalinan->prepare("select * from Odunc_al");
    if(!queryoduncalinan->exec())
    {
        QMessageBox::critical(this,"Hata",queryoduncalinan->lastError().text(),"Ok");
        return;
    }

    modeloduncalinan = new QSqlQueryModel();
    modeloduncalinan->setQuery(*queryoduncalinan);
    ui->tView_odncalinanbooks->setModel(modeloduncalinan);

}

void teslim::teslimedilenkitapListele()
{
    queryteslimalinan->prepare("select * from Teslim");
    if(!queryteslimalinan->exec())
    {
        QMessageBox::critical(this,"Hata",queryteslimalinan->lastError().text(),"Ok");
        return;
    }

    modelteslimalinan = new QSqlQueryModel();
    modelteslimalinan->setQuery(*queryteslimalinan);
    ui->tView_teslmedilenbooks->setModel(modelteslimalinan);
}



void teslim::on_btn_odncVer_clicked()
{
    int memberNo = ui->lineEdit_memberNo->text().toInt();
    int bookNo = ui->lineEdit_bookNo->text().toInt();
    if (ui->lineEdit_bookNo->text().isEmpty() || ui->lineEdit_memberNo->text().isEmpty()) {
        QMessageBox::critical(this, "Hata", "Gerekli alanları doldurunuz!", "Tamam");
        return;
    }


    QString vermetarihi = ui->dateEdit->date().toString("dd.MM.yyyy");
    QString format = "dd.MM.yyyy";
    almatarihi = QDate::fromString(alma_tarihi, format);
    int borc = 0;
    int gunfark = almatarihi.daysTo(ui->dateEdit->date());
    if (gunfark > 15) {
        borc = (gunfark - 15) * 2;
    }

    // Prepare and print the query string
    QString teslimQuery = "INSERT INTO Teslim (uye_no, kitap_no, alma_tarihi, verme_tarihi, borc) VALUES (?, ?, ?, ?, ?)";

    query->prepare(teslimQuery);

    query->addBindValue(memberNo);
    query->addBindValue(bookNo);
    query->addBindValue(alma_tarihi);
    query->addBindValue(vermetarihi);
    query->addBindValue(borc);

    if (!query->exec()) {
        QMessageBox::critical(this, "Hata", "Teslim işlemi gerçekleştirilemedi:\n" + query->lastError().text(), "Tamam");
        return;
    }

    // Odunc_al tablosundan silme sorgusu
    query->prepare("DELETE FROM Odunc_al WHERE uye_no = ? AND kitap_no = ?");
    query->addBindValue(memberNo);
    query->addBindValue(bookNo);

    if(!query->exec())
    {
        QMessageBox::critical(this, "Hata", "Ödünç alınan kitaplar tablosundan silme işlemi gerçekleştirilemedi.", "Tamam");
        return;
    }

    // Listeleme işlemleri ve temizlik
    oduncalinanktplistele();
    teslimedilenkitapListele();
    ui->lineEdit_memberNo->clear();
    ui->lineEdit_bookNo->clear();
}


void teslim::on_tView_odncalinanbooks_clicked(const QModelIndex &index)
{
    QString a = modeloduncalinan->index(index.row(),1).data().toString();
    query->prepare("SELECT alma_tarihi FROM Odunc_al WHERE kitap_no = ?");
    query->addBindValue(a);

    if (query->exec()) {
        if (query->next()) {
            alma_tarihi = query->value(0).toString();
            qDebug() << "Alma Tarihi:" << almatarihi;
        } else {
            qDebug() << "Sonuç bulunamadı.";
        }
    } else {
        qDebug() << "Sorgu başarısız:" << query->lastError().text();
    }
    ui->lineEdit_memberNo->setText(modeloduncalinan->index(index.row(),0).data().toString());
    ui->lineEdit_bookNo->setText(modeloduncalinan->index(index.row(),1).data().toString());

}


