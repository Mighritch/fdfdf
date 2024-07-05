#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

#include <QString>
#include <QSqlQueryModel>

class enseignant
{
public:
    enseignant();
    enseignant(const QString &nom, const QString &prenom, int cin, QString &matiere);

       // Accesseurs
       QString getNom() const;
       void setNom(const QString &nom);

       QString getPrenom() const;
       void setPrenom(const QString &prenom);

       int getCin() const;
       void setCin(int cin);

       QString getMatiere() const;
       void setMatiere(const QString &matiere);

           bool ajout();
           bool existeCin(int cin);
           QSqlQueryModel *affiche();
           QSqlQueryModel *recherche(const QString &nom);
           QSqlQueryModel *cherche(const QString &matiere);
           bool supprime(int cin);
           bool modifie();
           QSqlQueryModel* triParCIN();


private:
QString nom,prenom,matiere;
int cin;
};

#endif // ENSEIGNANT_H
