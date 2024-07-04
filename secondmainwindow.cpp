#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExpValidator>
secondwindow::secondwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::secondwindow)
{
    ui->setupUi(this);
    setWindowTitle("Second Window");
    resize(900, 600); // Taille de la nouvelle fenêtre
    ui->tableView->setModel(ens.affiche());

}

secondwindow::~secondwindow()
{
    delete ui;
}

void secondwindow::on_pushButton_clicked()
{
        QString nom = ui->lineEdit_3->text();
        QString prenom = ui->lineEdit_4->text();
        int cin = ui->lineEdit_5->text().toInt();
        QString matiere = ui->lineEdit_6->text();
        enseignant ens(nom, prenom, cin, matiere);

        if (nom.isEmpty() || prenom.isEmpty() || cin == 0 || matiere.isEmpty()) {
                QMessageBox::critical(this, "Erreur de saisie", "Tous les champs doivent être remplis.");
                return;
            }
        if (nom.length() > 50 || prenom.length() > 50) {
                QMessageBox::critical(this, "Erreur de saisie", "Le nom et le prénom ne doivent pas dépasser 50 caractères.");
                return;
            }

        if (ens.existeCin(cin)) {
               QMessageBox::critical(this, "Erreur d'ajout", "Un enseignant avec ce CIN existe déjà.");
               return;
           }
        bool test = ens.ajout();

            if (test) {
                ui->tableView->setModel(ens.affiche());
                QMessageBox::information(this, "Ajout réussi", "L'enseignant a été ajouté avec succès.");
            } else {
                QMessageBox::critical(this, "Erreur d'ajout", "Erreur lors de l'ajout de l'enseignant.");
            }

}
void secondwindow::on_pushButton_2_clicked()
{
    enseignant ens;
    ui->tableView->setModel(ens.affiche());

}

void secondwindow::on_pushButton_3_clicked()
{
    QString nom = ui->lineEdit_3->text();
    QString prenom = ui->lineEdit_4->text();
    int cin = ui->lineEdit_5->text().toInt();
    QString matiere = ui->lineEdit_6->text();
    enseignant ens(nom, prenom, cin, matiere);
    bool test = ens.modifie();

        if (test) {
            ui->tableView->setModel(ens.affiche());
            QMessageBox::information(this, "Modificiation réussi", "L'enseignant a été modifié avec succès.");
        } else {
            QMessageBox::critical(this, "Erreur de Modificiation", "Erreur lors de modifier de l'enseignant.");
        }


}

void secondwindow::on_pushButton_4_clicked()
{
    int cin = ui->lineEdit_2->text().toInt();
     bool test = ens.supprime(cin);

     if (test) {
         ui->tableView->setModel(ens.affiche());
         QMessageBox::information(this, "Suppression réussie", "L'enseignant a été supprimé avec succès.");
     } else {
         QMessageBox::critical(this, "Erreur de suppression", "Erreur lors de la suppression de l'enseignant.");
     }
}

void secondwindow::on_pushButton_retour_clicked()
{
    // Émettre le signal indiquant que le bouton retour a été cliqué
    emit retourButtonClicked();
      this->close();
}
