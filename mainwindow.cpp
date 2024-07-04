#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include <QDebug> // Inclure pour les messages de débogage

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , secondWindow(nullptr) // Initialiser le pointeur à nullptr
{
    ui->setupUi(this);
    connect(secondWindow, &secondwindow::retourButtonClicked, this, &MainWindow::afficherMainWindow);

}

MainWindow::~MainWindow()
{
    delete ui;
    if (secondWindow) {
        delete secondWindow; // Nettoyer la mémoire si secondWindow est alloué
    }
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Button clicked!"; // Ajouter un message de débogage

    if (!secondWindow) {
        secondWindow = new secondwindow();
        // Connecter le signal pour la fermeture de secondwindow et l'ouverture de MainWindow
        connect(secondWindow, &secondwindow::retourButtonClicked, this, &MainWindow::afficherMainWindow);
    }

    secondWindow->show();
    this->hide(); // Cacher la fenêtre principale
}


void MainWindow::afficherMainWindow()
{
    // Afficher à nouveau la fenêtre principale
    this->show();
    if (secondWindow) {
           secondWindow->close(); // Fermer la fenêtre secondwindow si elle est ouverte
       }
}
