/*
Ryan Konkul - rkonku2
Scott Prentice - sprent2
CS 340
Project 5: Mine Sweeper
12/1/2011
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QGridLayout>
#include <QStringList>
#include "Button.h"
#include <vector>
#include <cstdlib>
#include <ctime>

namespace Ui {
    class MainWindow;
}
enum State { SETTING_A_CARRIER, SETTING_BATTLESHIP, SETTING_DESTROYER, SETTING_SUB, SETTING_PATROL, WAITING_ON_PLAYER,
           OPPONENT_TURN, PLAYER_TURN };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //constructs a grid of buttons for the player
    void prepare_grid_player(int top_left_x, int top_left_y, int grid_size, QWidget *parent);
    //opponent grid
    void prepare_grid_opponent(int top_left_x, int top_left_y, int grid_size, QWidget *parent);
    //depending on state, returns true if the ship may be placed at row, col
    bool player_set_ship(int row, char col);
    //returns true if set the ship
    bool player_set_a_carrier(int row, char col);
    bool player_set_battle_ship(int row, int col);
    bool player_set_destroyer(int row, int col);
    bool player_set_sub(int row, int col);
    bool player_set_patrol(int row, int col);
    void print(QString s);
    //returns true if row, col is part of board
    bool is_valid_rowcol(int row, char col);
    bool is_valid_row(int row);
    bool is_valid_col(char col);
    //returns pointer to player button at row, col
    Button* get_p(int row, char col);
    //get pointer to opponent button
    Button* get_o(int row, char col);
    void clear_maybe_ships();
    //sends
    void sendMessage(QString s);

    ~MainWindow();

public slots:
    void btn_clicked();
    void row_box_changed();
    void col_box_changed();
    void set_ship();
    void auto_set_ships();
    void connectToServer();
    void setClientMode();
    void setServerMode();
    void readFromSocket();
    void connectToClient();
    void displayError(QAbstractSocket::SocketError socketError);
    void disconnection();

    void test();

private slots:
    void on_actionAbout_triggered();
    void on_actionConnecting_Help_triggered();
    void on_actionBattleship_Help_triggered();
    void on_actionQuit_triggered();
    void on_actionStatistics_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<Button*> player_buttons;
    std::vector<Button*> opponent_buttons;
    std::vector<Button*> possible_ships;
    bool clientMode;
    bool connected;
    bool used_auto;
    State state;
    bool setting_ships;
    bool other_player_waiting;
    int opponent_hits;
    int player_hits;
    int opponent_misses;
    int player_misses;
    double hitmiss_ratio;
    quint16 blockSize;

    int row_sent;
    char col_sent;

    bool has_valid_row;
    bool has_valid_col;
    QTcpServer *connectionSocket;
    QTcpSocket *communicationSocket;
};

#endif // MAINWINDOW_H
