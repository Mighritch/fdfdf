#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h" // Inclure le fichier d'en-tête de la deuxième fenêtre

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class secondwindow; // Déclarer la classe secondwindow pour éviter l'erreur de type

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void afficherMainWindow();


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    secondwindow *secondWindow; // Déclarer un pointeur pour la deuxième fenêtre
};

#endif // MAINWINDOW_H
