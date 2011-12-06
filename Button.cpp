/*
Ryan Konkul - rkonku2
Scott Prentice - sprent2
CS 340
Project 5: Mine Sweeper
12/1/2011
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Button.h"
#include <QGridLayout>
#include <QBitmap>
#include <QMouseEvent>

namespace Ui {
    class MainWindow;
}

void Button::setUI (Ui::MainWindow *uiparam) {
    ui = uiparam;
}

Button::Button(QString text, QWidget *parent)
    : QPushButton(text, parent)
{

}
Button::Button(int row, int col, int x, int y, int btn_size, bool p_ship, QString text, QWidget *parent)
    :QPushButton(text, parent)
{
    //save off the row and col
    this->row = col;
    this->col = row;
    //set position and size
    has_ship = false;
    hit = false;
    maybe_ship = false;
    player_ship = p_ship;
    this->setGeometry(row*btn_size+x, col*btn_size+y, btn_size, btn_size);
    //intialize state
    enable();
}

void Button::reset_btn() {
    setText("");
    enable();
}

int Button::get_row() {
    return row;
}

int Button::get_col() {
    return col;
}

void Button::disable() {
    this->setEnabled(false);
  //  setStyleSheet("background-color: rgba( 100, 100, 100, 80% ); border: 1px solid #8f8f91; color: white;" );
}

void Button::enable() {
    this->setEnabled(true);
//    setStyleSheet( "background-color: rgba( 20, 20, 20, 65% ); border: 1px solid #8f8f91; color: white;" );
}

Button::~Button()
{
}

