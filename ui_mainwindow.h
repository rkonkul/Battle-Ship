/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Dec 1 21:26:39 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClient;
    QAction *actionServer;
    QAction *actionAbout;
    QAction *actionConnecting_Help;
    QAction *actionBattleship_Help;
    QAction *actionQuit;
    QAction *actionStatistics;
    QWidget *centralWidget;
    QLineEdit *column_box;
    QLabel *columnlabel;
    QLineEdit *row_box;
    QLabel *rowlabel;
    QCheckBox *is_vertical;
    QPushButton *shipset;
    QLabel *ship_to_set;
    QLabel *client_label;
    QPushButton *auto_set_ships;
    QLineEdit *ip_address_box;
    QLabel *ip_label;
    QLabel *port_label;
    QLineEdit *port_box;
    QPushButton *connect_server_button;
    QLabel *connected_label;
    QLabel *current_turn_label;
    QLabel *win_label;
    QMenuBar *menuBar;
    QMenu *menuMode;
    QMenu *menuHelp;
    QMenu *menuBattle_Ship;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(584, 393);
        actionClient = new QAction(MainWindow);
        actionClient->setObjectName(QString::fromUtf8("actionClient"));
        actionServer = new QAction(MainWindow);
        actionServer->setObjectName(QString::fromUtf8("actionServer"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionConnecting_Help = new QAction(MainWindow);
        actionConnecting_Help->setObjectName(QString::fromUtf8("actionConnecting_Help"));
        actionBattleship_Help = new QAction(MainWindow);
        actionBattleship_Help->setObjectName(QString::fromUtf8("actionBattleship_Help"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionStatistics = new QAction(MainWindow);
        actionStatistics->setObjectName(QString::fromUtf8("actionStatistics"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        column_box = new QLineEdit(centralWidget);
        column_box->setObjectName(QString::fromUtf8("column_box"));
        column_box->setGeometry(QRect(80, 230, 31, 21));
        columnlabel = new QLabel(centralWidget);
        columnlabel->setObjectName(QString::fromUtf8("columnlabel"));
        columnlabel->setGeometry(QRect(80, 210, 51, 16));
        row_box = new QLineEdit(centralWidget);
        row_box->setObjectName(QString::fromUtf8("row_box"));
        row_box->setGeometry(QRect(10, 230, 31, 20));
        rowlabel = new QLabel(centralWidget);
        rowlabel->setObjectName(QString::fromUtf8("rowlabel"));
        rowlabel->setGeometry(QRect(20, 210, 46, 13));
        is_vertical = new QCheckBox(centralWidget);
        is_vertical->setObjectName(QString::fromUtf8("is_vertical"));
        is_vertical->setGeometry(QRect(20, 260, 121, 18));
        shipset = new QPushButton(centralWidget);
        shipset->setObjectName(QString::fromUtf8("shipset"));
        shipset->setGeometry(QRect(20, 310, 75, 23));
        ship_to_set = new QLabel(centralWidget);
        ship_to_set->setObjectName(QString::fromUtf8("ship_to_set"));
        ship_to_set->setGeometry(QRect(10, 280, 211, 16));
        client_label = new QLabel(centralWidget);
        client_label->setObjectName(QString::fromUtf8("client_label"));
        client_label->setGeometry(QRect(330, 210, 121, 20));
        auto_set_ships = new QPushButton(centralWidget);
        auto_set_ships->setObjectName(QString::fromUtf8("auto_set_ships"));
        auto_set_ships->setGeometry(QRect(130, 310, 121, 23));
        ip_address_box = new QLineEdit(centralWidget);
        ip_address_box->setObjectName(QString::fromUtf8("ip_address_box"));
        ip_address_box->setGeometry(QRect(430, 230, 113, 20));
        ip_label = new QLabel(centralWidget);
        ip_label->setObjectName(QString::fromUtf8("ip_label"));
        ip_label->setGeometry(QRect(340, 230, 81, 20));
        port_label = new QLabel(centralWidget);
        port_label->setObjectName(QString::fromUtf8("port_label"));
        port_label->setGeometry(QRect(390, 260, 31, 16));
        port_box = new QLineEdit(centralWidget);
        port_box->setObjectName(QString::fromUtf8("port_box"));
        port_box->setGeometry(QRect(430, 260, 113, 20));
        connect_server_button = new QPushButton(centralWidget);
        connect_server_button->setObjectName(QString::fromUtf8("connect_server_button"));
        connect_server_button->setGeometry(QRect(430, 300, 141, 23));
        connected_label = new QLabel(centralWidget);
        connected_label->setObjectName(QString::fromUtf8("connected_label"));
        connected_label->setGeometry(QRect(300, 300, 131, 21));
        current_turn_label = new QLabel(centralWidget);
        current_turn_label->setObjectName(QString::fromUtf8("current_turn_label"));
        current_turn_label->setGeometry(QRect(200, 210, 81, 16));
        win_label = new QLabel(centralWidget);
        win_label->setObjectName(QString::fromUtf8("win_label"));
        win_label->setGeometry(QRect(210, 250, 46, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 584, 21));
        menuMode = new QMenu(menuBar);
        menuMode->setObjectName(QString::fromUtf8("menuMode"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuBattle_Ship = new QMenu(menuBar);
        menuBattle_Ship->setObjectName(QString::fromUtf8("menuBattle_Ship"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuBattle_Ship->menuAction());
        menuBar->addAction(menuMode->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuMode->addAction(actionClient);
        menuMode->addAction(actionServer);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionConnecting_Help);
        menuHelp->addAction(actionBattleship_Help);
        menuBattle_Ship->addAction(actionStatistics);
        menuBattle_Ship->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(row_box, SIGNAL(textChanged(QString)), MainWindow, SLOT(row_box_changed()));
        QObject::connect(column_box, SIGNAL(textChanged(QString)), MainWindow, SLOT(col_box_changed()));
        QObject::connect(shipset, SIGNAL(clicked()), MainWindow, SLOT(set_ship()));
        QObject::connect(is_vertical, SIGNAL(clicked()), MainWindow, SLOT(row_box_changed()));
        QObject::connect(auto_set_ships, SIGNAL(clicked()), MainWindow, SLOT(auto_set_ships()));
        QObject::connect(connect_server_button, SIGNAL(clicked()), MainWindow, SLOT(connectToServer()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionClient->setText(QApplication::translate("MainWindow", "Client", 0, QApplication::UnicodeUTF8));
        actionServer->setText(QApplication::translate("MainWindow", "Server", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionConnecting_Help->setText(QApplication::translate("MainWindow", "Connecting Help", 0, QApplication::UnicodeUTF8));
        actionBattleship_Help->setText(QApplication::translate("MainWindow", "Battleship Help", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionStatistics->setText(QApplication::translate("MainWindow", "Statistics", 0, QApplication::UnicodeUTF8));
        columnlabel->setText(QApplication::translate("MainWindow", "Column", 0, QApplication::UnicodeUTF8));
        rowlabel->setText(QApplication::translate("MainWindow", "Row", 0, QApplication::UnicodeUTF8));
        is_vertical->setText(QApplication::translate("MainWindow", "vertical or not", 0, QApplication::UnicodeUTF8));
        shipset->setText(QApplication::translate("MainWindow", "Set Ship", 0, QApplication::UnicodeUTF8));
        ship_to_set->setText(QApplication::translate("MainWindow", "Setting ship:", 0, QApplication::UnicodeUTF8));
        client_label->setText(QApplication::translate("MainWindow", "Current Mode:", 0, QApplication::UnicodeUTF8));
        auto_set_ships->setText(QApplication::translate("MainWindow", "Auto Set Ships", 0, QApplication::UnicodeUTF8));
        ip_label->setText(QApplication::translate("MainWindow", "IP Address:", 0, QApplication::UnicodeUTF8));
        port_label->setText(QApplication::translate("MainWindow", "Port:", 0, QApplication::UnicodeUTF8));
        connect_server_button->setText(QApplication::translate("MainWindow", "Connect To Server", 0, QApplication::UnicodeUTF8));
        connected_label->setText(QApplication::translate("MainWindow", "Status: Disconnected", 0, QApplication::UnicodeUTF8));
        current_turn_label->setText(QApplication::translate("MainWindow", "Current Turn", 0, QApplication::UnicodeUTF8));
        win_label->setText(QString());
        menuMode->setTitle(QApplication::translate("MainWindow", "Mode", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuBattle_Ship->setTitle(QApplication::translate("MainWindow", "Battle Ship", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
