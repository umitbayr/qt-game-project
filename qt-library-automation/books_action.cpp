/*ÜMİT BAYRAM 20010011507*/

#include "books_action.h"
#include "ui_books_action.h"

book::book(QSqlDatabase db,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::book)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
    listbook();
}

book::~book()
{
    delete ui;
}

void book::listbook(){

    query->prepare("select * from Books");
    if(!query->exec())
    {
        QMessageBox::critical(this,"Hata",query->lastError().text(),"Ok");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*query);
    ui->tView_allbooks->setModel(model);
}

void book::on_pushButton_yenisave_clicked()
{
    // Boş olan LineEdit kontrolü
    if (ui->lineEdit_bookName->text().isEmpty() ||
        ui->lineEdit_bookStok->text().isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Gerekli alanları doldurunuz!", "Ok");
        return;
    }

    QString kitapAd = ui->lineEdit_bookName->text();
    int kitapSayisi = ui->lineEdit_bookStok->text().toInt();

    // Yeni kitap ekleme
    QSqlQuery query;
    query.prepare("INSERT INTO Books (kitap_ad, kitap_sayisi) VALUES ( ?, ?)");
    query.addBindValue(kitapAd);
    query.addBindValue(kitapSayisi);

    if (!query.exec()) {
        QMessageBox::critical(this, "Hata!", query.lastError().text(), "Ok");
        return;
    }

    // Tablodaki verileri güncelle
    listbook();

    // LineEdit'leri temizle
    ui->lineEdit_bookName->setText("");
    ui->lineEdit_bookStok->setText("");


}


void book::on_pushButton_update_clicked()
{// Boş olan LineEdit kontrolü
    if (ui->lineEdit_bookName->text().isEmpty() ||
        ui->lineEdit_bookStok->text().isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Gerekli alanları doldurunuz!", "Ok");
        return;
    }

    int kitapNo = ui->lineEdit_bookNo->text().toInt();
    QString kitapAd = ui->lineEdit_bookName->text();
    int kitapSayisi = ui->lineEdit_bookStok->text().toInt();

    // Kitap bilgilerini güncelle
    QSqlQuery query;
    query.prepare("UPDATE Books SET kitap_ad = ?, kitap_sayisi = ? WHERE kitap_no = ?");
    query.addBindValue(kitapAd);
    query.addBindValue(kitapSayisi);
    query.addBindValue(kitapNo);

    if (!query.exec()) {
        QMessageBox::critical(this, "Hata!", query.lastError().text(), "Ok");
        return;
    }

    // Tablodaki verileri güncelle
    listbook();

    // LineEdit'leri temizle
    ui->lineEdit_bookNo->setText("");
    ui->lineEdit_bookName->setText("");
    ui->lineEdit_bookStok->setText("");
}


void book::on_pushButton_del_clicked()
{
    // Boş olan LineEdit kontrolü
    if (ui->lineEdit_bookNo->text().isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Listeden bir kayıt seçiniz!", "Ok");
        return;
    }

    int kitapNo = ui->lineEdit_bookNo->text().toInt();

    // Kitap ödünç verilmiş mi kontrol et
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Odunc_al o JOIN Teslim t ON o.kitap_no = t.kitap_no WHERE o.kitap_no = ? AND t.verme_tarihi IS NULL");
    query.addBindValue(kitapNo);


    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Hata!", "olmadı", "Ok");
        return;
    }

    int count = query.value(0).toInt();
    if (count > 0) {
        QMessageBox::critical(this, "Hata!", "Bu kitap silinemez! Bu kitap bir üyeye ödünç verilmiştir.", "Ok");
        return;
    }

    // Kitabı sil
    query.prepare("DELETE FROM Books WHERE kitap_no = ?");
    query.addBindValue(kitapNo);

    if (!query.exec()) {
        QMessageBox::critical(this, "Hata!", query.lastError().text(), "Ok");
        return;
    }

    // Tablodaki verileri güncelle
    listbook();

    // LineEdit'leri temizle
    ui->lineEdit_bookNo->setText("");
    ui->lineEdit_bookName->setText("");
    ui->lineEdit_bookStok->setText("");
}

int book_no;

void book::on_tView_allbooks_clicked(const QModelIndex &index)
{
    ui->lineEdit_bookNo->setText(model->index(index.row(), 0).data().toString());
    ui->lineEdit_bookName->setText(model->index(index.row(), 1).data().toString());
    ui->lineEdit_bookStok->setText(model->index(index.row(), 2).data().toString());
    book_no = model->index(index.row(), 0).data().toInt();

    // İlk sorgu için yeni bir QSqlQuery ve QSqlQueryModel oluşturun
    QSqlQuery *queryOdunc = new QSqlQuery();
    queryOdunc->prepare("select * from Odunc_al WHERE kitap_no = ?");
    queryOdunc->addBindValue(book_no);

    if (!queryOdunc->exec())
    {
        QMessageBox::critical(this, "Hata", queryOdunc->lastError().text(), "Ok");
        delete queryOdunc;
        return;
    }

    QSqlQueryModel *modelOdunc = new QSqlQueryModel();
    modelOdunc->setQuery(*queryOdunc);
    ui->tView_oduncalmadurum->setModel(modelOdunc);

    // İkinci sorgu için yeni bir QSqlQuery ve QSqlQueryModel oluşturun
    QSqlQuery *queryTeslim = new QSqlQuery();
    queryTeslim->prepare("select * from Teslim WHERE kitap_no = ?");
    queryTeslim->addBindValue(book_no);

    if (!queryTeslim->exec())
    {
        QMessageBox::critical(this, "Hata", queryTeslim->lastError().text(), "Ok");
        delete queryTeslim;
        return;
    }

    QSqlQueryModel *modelTeslim = new QSqlQueryModel();
    modelTeslim->setQuery(*queryTeslim);
    ui->tView_oncedeoduncalma->setModel(modelTeslim);

    // Dinamik olarak oluşturduğunuz query nesnelerini serbest bırakın
    delete queryOdunc;
    delete queryTeslim;
}





