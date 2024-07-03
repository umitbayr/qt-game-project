/*ÜMİT BAYRAM 20010011507*/
#include "oduncalma.h"
#include "ui_oduncalma.h"

oduncalma::oduncalma(QSqlDatabase db,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::oduncalma)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
    querymember = new QSqlQuery(db);
    querybook = new QSqlQuery(db);
    queryoduncalinan = new QSqlQuery(db);
    queryAynikitapalinmismi = new QSqlQuery(db);
    listbook();
    listmember();
    oduncalinanktplistele();
}

oduncalma::~oduncalma()
{
    delete ui;
}


void oduncalma::listbook()
{
    querybook->prepare("select * from Books");
    if(!querybook->exec())
    {
        QMessageBox::critical(this,"Hata",querybook->lastError().text(),"Ok");
        return;
    }

    modelbook = new QSqlQueryModel();
    modelbook->setQuery(*querybook);
    ui->tView_books->setModel(modelbook);

}


void oduncalma::listmember()
{

    querymember->prepare("select * from Members");
    if(!querymember->exec())
    {
        QMessageBox::critical(this,"Hata",querymember->lastError().text(),"Ok");
        return;
    }

    modelmember = new QSqlQueryModel();
    modelmember->setQuery(*querymember);
    ui->tView_members->setModel(modelmember);
}

void oduncalma::oduncalinanktplistele()
{
    queryoduncalinan->prepare("select * from Odunc_al");
    if(!queryoduncalinan->exec())
    {
        QMessageBox::critical(this,"Hata",queryoduncalinan->lastError().text(),"Ok");
        return;
    }

    modeloduncalinan = new QSqlQueryModel();
    modeloduncalinan->setQuery(*queryoduncalinan);
    ui->tView_oduncalinanbooks->setModel(modeloduncalinan);
}


void oduncalma::on_btn_odncAl_clicked()
{
    // Üye numarasını ve kitap numarasını line editlerden al
    QString memberNo = ui->lineEdit_memberNo->text();
    QString bookNo = ui->lineEdit_bookNo->text();

    // Hem üye numarasının hem de kitap numarasının boş olmadığını kontrol et
    if (memberNo.isEmpty() || bookNo.isEmpty())
    {
        QMessageBox::warning(this, "Eksik Bilgi", "Lütfen üye ve kitap seçimini yapınız.", "Tamam");
        return;
    }

    // Güncel tarihi al
    QString currentDate = ui->dateEdit->date().toString("dd.MM.yyyy");

    // Stok sayısını kontrol et
    query->prepare("SELECT kitap_sayisi FROM Books WHERE kitap_no = " + bookNo);

    if (!query->exec()) {
        QMessageBox::critical(this, "Hata", "Sorgu gerçekleştirilemedi!", "Tamam");
        return;
    }

    if (!query->next()) {
        QMessageBox::warning(this, "Uyarı", "Seçili kitap kütüphanede mevcut değildir!", "Tamam");
        return;
    }

    int varolanKitapSayisi = query->value("kitap_sayisi").toInt();
    if (varolanKitapSayisi == 0) {
        QMessageBox::warning(this, "Uyarı", "Seçili kitap kütüphanede mevcut değildir!", "Tamam");
        return;
    }

    // Aynı kitabın ödünç alınıp alınmadığını kontrol et
    queryAynikitapalinmismi->prepare("SELECT * FROM Odunc_al WHERE kitap_no = " + bookNo + " AND uye_no = " + memberNo);

    if (queryAynikitapalinmismi->exec() && queryAynikitapalinmismi->next()){
        QMessageBox::information(this, "Hata", "Bu üye bu kitabın bir tanesini zaten ödünç almış, tekrar ödünç verilemez!", "Tamam");
        return;
    }

    // Odunc_alinan tablosuna veri eklemek için sorguyu hazırla
    queryoduncalinan->prepare("INSERT INTO Odunc_al (uye_no, kitap_no, alma_tarihi) VALUES (" + memberNo + ", " + bookNo + ", '" + currentDate + "')");

    // Sorguyu çalıştır
    if (!queryoduncalinan->exec())
    {
        QMessageBox::critical(this, "Hata", "Sorgu çalışmıyor!", "Tamam");
        return;
    }

    // Stok sayısını bir azalt
    queryoduncalinan->prepare("UPDATE Books SET kitap_sayisi = kitap_sayisi - 1 WHERE kitap_no = " + bookNo);

    if (!queryoduncalinan->exec()) {
        QMessageBox::critical(this, "Hata", "Stok güncellerken hatayla karşılaşıldı!", "Tamam");
        return;
    }

    // Ödünç alınan kitapların listesini güncelle
    oduncalinanktplistele();
    listbook();
    listmember();

    // Başarılı işlem mesajı göster
    QMessageBox::information(this, "Başarılı", "Kitap ödünç alma işlemi başarılı.", "Tamam");

    // Line editleri temizle
    ui->lineEdit_memberNo->clear();
    ui->lineEdit_bookNo->clear();
}






void oduncalma::on_tView_books_clicked(const QModelIndex &index)
{
    ui->lineEdit_bookNo->setText(modelbook->index(index.row(),0).data().toString());

}


void oduncalma::on_tView_members_clicked(const QModelIndex &index)
{
    ui->lineEdit_memberNo->setText(modelmember->index(index.row(),0).data().toString());
}

