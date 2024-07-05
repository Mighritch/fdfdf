#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QDebug>
#include <QSqlError>
#include <QSortFilterProxyModel>

secondwindow::secondwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::secondwindow)
{
    ui->setupUi(this);
    setWindowTitle("Second Window");
    resize(900, 600); // Taille de la nouvelle fenêtre

    QSqlDatabase db = QSqlDatabase::database(); // Accéder à la base de données par défaut de l'application

       if (!db.isOpen()) {
           qDebug() << "Erreur de connexion à la base de données.";
           QMessageBox::critical(this, "Erreur de connexion", "Impossible de se connecter à la base de données.");
           // Gérer la fermeture de la fenêtre ou d'autres actions nécessaires
           return;
       }

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



void secondwindow::on_pushButton_5_clicked()
{
    QString nom = ui->lineEdit_7->text().trimmed(); // Trim pour enlever les espaces blancs autour
    QSqlQueryModel *model = ens.recherche(nom);

    if (!model) {
        qDebug() << "Erreur lors de la recherche.";
        QMessageBox::critical(this, "Erreur de recherche", "Une erreur s'est produite lors de la recherche.");
        return;
    }

    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL:" << model->lastError().text();
        QMessageBox::critical(this, "Erreur SQL", "Une erreur SQL s'est produite lors de la recherche.");
        delete model;  // Libérer la mémoire du modèle
        return;
    }

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Aucun résultat", "Aucun enseignant trouvé avec le nom spécifié.");
        ui->tableView->setModel(nullptr);  // Effacer le modèle actuel du tableView s'il y en a un
    } else {
       ui->tableView->setModel(model);
    }
}




void secondwindow::on_pushButton_7_clicked()
{
    enseignant ens;
      QSqlQueryModel *modelTri = ens.triParCIN();
      if (modelTri) {
          // Utiliser un proxy model pour trier
          QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
          proxyModel->setSourceModel(modelTri);
          ui->tableView->setModel(proxyModel);
      } else {
          QMessageBox::critical(this, "Erreur de tri", "Erreur lors du tri des données par CIN.");
      }
}


void secondwindow::on_pushButton_6_clicked()
{
    QString matiere = ui->lineEdit_8->text().trimmed(); // Trim pour enlever les espaces blancs autour
    QSqlQueryModel *model = ens.cherche(matiere);

    if (!model) {
        qDebug() << "Erreur lors de la recherche.";
        QMessageBox::critical(this, "Erreur de recherche", "Une erreur s'est produite lors de la recherche.");
        return;
    }

    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL:" << model->lastError().text();
        QMessageBox::critical(this, "Erreur SQL", "Une erreur SQL s'est produite lors de la recherche.");
        delete model;  // Libérer la mémoire du modèle
        return;
    }

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Aucun résultat", "Aucun enseignant trouvé avec cette matière spécifiée.");
        ui->tableView->setModel(nullptr);  // Effacer le modèle actuel du tableView s'il y en a un
    } else {
        ui->tableView->setModel(model);
    }
}
