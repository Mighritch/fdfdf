#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>
#include "enseignant.h"
#include "mainwindow.h" // Inclure le fichier d'en-tête de la fenêtre principale

namespace Ui {
class secondwindow;
}

class MainWindow; // Déclarer la classe MainWindow pour éviter l'erreur de type

class secondwindow : public QWidget
{
    Q_OBJECT

public:
    explicit secondwindow(QWidget *parent = nullptr);
    ~secondwindow();

signals:
    void retourButtonClicked();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_retour_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::secondwindow *ui;
    enseignant ens;
    MainWindow *mainWindow;
};

#endif // SECONDWINDOW_H
