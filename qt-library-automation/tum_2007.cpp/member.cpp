/*ÜMİT BAYRAM 20010011507*/
#include "member.h"
#include "ui_member.h"

member::member(QSqlDatabase db,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::member)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
    listmember();
}

member::~member()
{
    delete ui;
}

void member::listmember(){

    query->prepare("select * from Members");
    if(!query->exec())
    {
        QMessageBox::critical(this,"Hata","BOZUK","Ok");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*query);
    ui->tView_members->setModel(model);
}


void member::on_btn_yenimember_clicked()
{
    // Boş alan kontrolü
    if (ui->lineEdit_memberName->text().isEmpty() ||
        ui->lineEdit_memberSurname->text().isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Gerekli alanlari doldurunuz!", "Ok");
        return;
    }

    QString memberName = ui->lineEdit_memberName->text();
    QString memberSurname = ui->lineEdit_memberSurname->text();

    // Yeni üye ekleme
    QSqlQuery query;
    query.prepare("INSERT INTO Members (uye_ad, uye_soyad) VALUES (?, ?)");
    query.addBindValue(memberName);
    query.addBindValue(memberSurname);

    if (!query.exec()) {
        QMessageBox::critical(this, "Hata!", query.lastError().text(), "Ok");
        return;
    }

    // Tablodaki verileri güncelle
    listmember();

    // LineEdit'leri temizle
    ui->lineEdit_memberName->setText("");
    ui->lineEdit_memberSurname->setText("");
}


void member::on_btn_update_clicked()
{
    // Boş olan LineEdit kontrolü
    if (ui->lineEdit_memberName->text().isEmpty() ||
        ui->lineEdit_memberSurname->text().isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Gerekli alanlari doldurunuz!", "Ok");
        return;
    }
    int memberNo = ui->lineEdit_memberNo->text().toInt();
    QString memberName = ui->lineEdit_memberName->text();
    QString memberSurname = ui->lineEdit_memberSurname->text();

    // Üye bilgilerini güncelle
    QSqlQuery query;
    query.prepare("UPDATE Members SET uye_ad = ?, uye_soyad = ? where uye_no=?");
    query.addBindValue(memberName);
    query.addBindValue(memberSurname);
    query.addBindValue(memberNo);

    if (!query.exec()) {
        QMessageBox::critical(this, "Hata!", query.lastError().text(), "Ok");
        return;
    }

    // Tablodaki verileri güncelle
    listmember();

    // LineEdit'leri temizle
    ui->lineEdit_memberName->setText("");
    ui->lineEdit_memberSurname->setText("");
    ui->lineEdit_memberNo->setText("");
}






void member::on_btn_del_clicked()
{
    // Boş olan LineEdit kontrolü
    if (ui->lineEdit_memberNo->text().isEmpty()){
        QMessageBox::critical(this, "Hata!", "Listeden bir kayıt seçiniz!", "Ok");
        return;
    }

    int memberNo = ui->lineEdit_memberNo->text().toInt();

    // Üyenin henüz teslim etmediği kitapları kontrol et
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM Odunc_al WHERE uye_no = ? AND NOT EXISTS (SELECT 1 FROM Teslim WHERE Teslim.uye_no = Odunc_al.uye_no AND Teslim.kitap_no = Odunc_al.kitap_no)");
    checkQuery.addBindValue(memberNo);

    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::critical(this, "Hata!", "Ödünç alma kayıtlarını kontrol ederken bir hata oluştu.", "Ok");
        return;
    }

    int notReturnedBooks = checkQuery.value(0).toInt();
    if (notReturnedBooks > 0) {
        QMessageBox::critical(this, "Hata!", "Bu üyenin henüz teslim etmediği kitaplar var. Üye silinemez.", "Ok");
        return;
    }

    // Üyeyi sil
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM Members WHERE uye_no = ?");
    deleteQuery.addBindValue(memberNo);

    if (!deleteQuery.exec()) {
        QMessageBox::critical(this, "Hata!", deleteQuery.lastError().text(), "Ok");
        return;
    }

    // Tablodaki verileri güncelle
    listmember();

    // LineEdit'leri temizle
    ui->lineEdit_memberName->setText("");
    ui->lineEdit_memberSurname->setText("");
    ui->lineEdit_memberNo->setText("");
}



void member::on_tView_members_clicked(const QModelIndex &index)
{
    ui->lineEdit_memberNo->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_memberName->setText(model->index(index.row(),1).data().toString());
    ui->lineEdit_memberSurname->setText(model->index(index.row(),2).data().toString());
}

