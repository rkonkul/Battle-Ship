/*
Ryan Konkul - rkonku2
Scott Prentice - sprent2
CS 340
Project 5: Mine Sweeper
12/1/2011
*/

#ifndef BUTTON_H
#define BUTTON_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QDir>
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class Button : public QPushButton
{

private:
    int row;
    int col;
    Ui::MainWindow *ui;

public:
    bool has_ship;
    bool hit;
    bool maybe_ship;
    bool player_ship;

    Button(QString text, QWidget *parent = 0);
    //get a pointer to MainWindow into the button
    void setUI(Ui::MainWindow *uiparam);
    //constructs a button at row, col, with size x and y
    Button(int col, int row, int x, int y, int btn_size, bool p_ship, QString text, QWidget *parent);
    //resets state of button
    void reset_btn();
    //return the row
    int get_row();
    //return the col
    int get_col();
    //disables the button
    void disable();
    //enables the button
    void enable();
    ~Button();
};

#endif // BUTTON_H
