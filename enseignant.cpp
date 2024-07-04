#include "enseignant.h"
#include <QtSql>
#include <QMessageBox>
#include <QVariant>

enseignant::enseignant()
{

}

enseignant::enseignant(const QString &nom, const QString &prenom, int cin, QString &matiere)
       :nom(nom), prenom(prenom), cin(cin), matiere(matiere)
{

}


QString enseignant::getNom() const {
    return nom;
}

void enseignant::setNom(const QString &nom) {
    this->nom = nom;
}

QString enseignant::getPrenom() const {
    return prenom;
}

void enseignant::setPrenom(const QString &prenom) {
    this->prenom = prenom;
}
int enseignant::getCin() const {
    return cin;
}

void enseignant::setCin(int cin) {
    this->cin = cin;
}

QString enseignant::getMatiere() const {
    return matiere;
}

void enseignant::setMatiere(const QString &matiere) {
    this->matiere = matiere;
}

bool enseignant::ajout() {
    QSqlQuery query;
    query.prepare("INSERT INTO ENSEIGNANT (nom, prenom, cin, matiere) "
                  "VALUES (:nom, :prenom, :cin, :matiere)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":cin", cin);
    query.bindValue(":matiere", matiere);

    return query.exec();
}
bool enseignant::existeCin(int cin) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM ENSEIGNANT WHERE cin = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}


QSqlQueryModel *enseignant::affiche() {
    QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery("SELECT * FROM ENSEIGNANT");
       return model;

    return model;
}

bool enseignant::modifie(){
    QSqlQuery query;
       query.prepare("UPDATE ENSEIGNANT SET nom = :nom, prenom = :prenom, matiere = :matiere WHERE cin = :cin");
       query.bindValue(":nom", nom);
       query.bindValue(":prenom", prenom);
       query.bindValue(":matiere", matiere);
       query.bindValue(":cin", cin);

       return query.exec();
}

bool enseignant::supprime(int cin){
    QSqlQuery query;
    QString res = QString::number(cin);

    query.prepare("Delete from ENSEIGNANT where cin= :cin");
    query.bindValue(":cin",cin);

    return query.exec();
}
