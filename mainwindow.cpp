/*
Ryan Konkul - rkonku2
Scott Prentice - sprent2
CS 340
Project 5: Mine Sweeper
12/1/2011
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    has_valid_row = false;
    has_valid_col = false;
    setting_ships = true;
    ui->ship_to_set->setText("Setting ship: 5 Aircraft Carrier");
    ui->shipset->setEnabled(false);
    ui->column_box->setEnabled(false);
    ui->row_box->setEnabled(false);
    ui->auto_set_ships->setEnabled(false);
    state = SETTING_A_CARRIER;
    other_player_waiting = false;
    used_auto = false;
    opponent_hits = 0;
    player_hits = 0;
    opponent_misses = 0;
    player_misses = 0;
    hitmiss_ratio = 0;

    clientMode = false;
    connected = false;
    connect (ui->actionClient, SIGNAL(triggered()), this, SLOT(setClientMode()));
    connect (ui->actionServer, SIGNAL(triggered()), this, SLOT(setServerMode()));

    int GRID_SIZE = 11;
    prepare_grid_player(30, 40, GRID_SIZE, this);
    prepare_grid_opponent(250, 40, GRID_SIZE, this);
    QWidget::setFixedSize(this->size());
    QWidget::setWindowTitle("Battle Ship");
    setClientMode();
}

void MainWindow::prepare_grid_player(int top_left_x, int top_left_y, int grid_size, QWidget *parent) {
    //create the buttons
    for(int i=0; i<grid_size; ++i) {
        for(int j=0; j<grid_size; ++j) {
            //create and display the button
            Button* p = new Button(i, j, top_left_x, top_left_y, 16, true, "", parent);
            //connect signals
            p->setUI(ui);
            p->hit = false;
            //add button to vector
            player_buttons.push_back(p);
            connect(p, SIGNAL(clicked()), this, SLOT(btn_clicked()));
        }
    }
    //set displays
    //top row and left most column are displays (A-K), (1-10)
    //rest are water images
    for(unsigned int i=0; i<player_buttons.size(); ++i) {
        char c = 'A';
        Button* p = player_buttons[i];
        if(player_buttons[i]->get_col() == 0) {
            QString f;
            f.setNum(p->get_row());
            p->setText(f);
            p->disable();
        }
        else if(player_buttons[i]->get_row() == 0) {
            QString f;
            f = (char) c + player_buttons[i]->get_col() - 1;
            p->setText(f);
            p->disable();
        }
        else {
            QIcon f(":images/batt101.gif");
            p->setIcon(f);
        }
    }
}

void MainWindow::prepare_grid_opponent(int top_left_x, int top_left_y, int grid_size, QWidget *parent) {
    //create the buttons
    for(int i=0; i<grid_size; ++i) {
        for(int j=0; j<grid_size; ++j) {
            //create and display the button
            Button* p = new Button(i, j, top_left_x, top_left_y, 16, false, "", parent);
            //connect signals
            p->setUI(ui);
            p->hit = false;
            //add button to vector
            opponent_buttons.push_back(p);
            connect(p, SIGNAL(clicked()), this, SLOT(btn_clicked()));
        }
    }
    //set displays
    //top row and left most column are displays (A-K), (1-10)
    //rest are water images
    for(unsigned int i=0; i<opponent_buttons.size(); ++i) {
        char c = 'A';
        Button* p = opponent_buttons[i];
        if(opponent_buttons[i]->get_col() == 0) {
            QString f;
            f.setNum(p->get_row());
            p->setText(f);
            p->disable();
        }
        else if(opponent_buttons[i]->get_row() == 0) {
            QString f;
            f = (char) c + opponent_buttons[i]->get_col() - 1;
            p->setText(f);
            p->disable();
        }
        else {
            QIcon f(":images/batt101.gif");
            p->setIcon(f);
        }
    }
}

void MainWindow::auto_set_ships() {
    used_auto = true;
    srand(time(NULL));
    bool try_again = true;
    while(try_again) {
        for(unsigned int i=0; i<player_buttons.size(); ++i) {
            Button* b = player_buttons[i];
            b->has_ship = false;
            if(b->isEnabled()) {
                QIcon q(":/images/batt101.gif");
                b->setIcon(q);
            }
        }
        setting_ships = true;
        state = SETTING_A_CARRIER;
        while(setting_ships) {
            int row = (rand() % 10) + 1;
            char col = (char) ((rand() % 10) + 97);
            bool vertical = (rand() % 2);
            if(vertical) {
                ui->is_vertical->setChecked(true);
            }
            else {
                ui->is_vertical->setChecked(false);
            }
            QString r;
            r.setNum(row);
            ui->row_box->setText(r);
            r = col;
            ui->column_box->setText(r);
            if(has_valid_row && has_valid_col) {
                set_ship();
            }
        }
        int num_ship_blocks = 0;
        for(unsigned int i=0; i<player_buttons.size(); ++i) {
            if(player_buttons[i]->has_ship) {
                num_ship_blocks++;
            }
        }
        if(num_ship_blocks != 17) {
            try_again = true;
        }
        else {
            try_again = false;
        }
    }
    if(connected) {
        sendMessage("Done");
        ui->auto_set_ships->setEnabled(false);
        if(!other_player_waiting) {
            state = PLAYER_TURN;
            ui->current_turn_label->setText("Player's turn");
        }
        else {
            state = OPPONENT_TURN;
            ui->current_turn_label->setText("Opponent's turn");
        }
     }
}

bool MainWindow::player_set_a_carrier(int row, char col) {
    print("setting aircraft carrier");
    if(ui->is_vertical->isChecked()) {
        if(row <= 6 && row >= 1) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<5; ++i) {
                Button* b = get_p(row+i, col);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt6.gif");
                    else if(i==1) q.addFile(":/images/batt7.gif");
                    else if(i==2) q.addFile(":/images/batt8.gif");
                    else if(i==3) q.addFile(":/images/batt9.gif");
                    else if(i==4) q.addFile(":/images/batt10.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
        else if(row >= 6 && row <= 10) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<5; ++i) {
                Button* b = get_p(row-i, col);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt10.gif");
                    else if(i==1) q.addFile(":/images/batt9.gif");
                    else if(i==2) q.addFile(":/images/batt8.gif");
                    else if(i==3) q.addFile(":/images/batt7.gif");
                    else if(i==4) q.addFile(":/images/batt6.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
    }
    else { //horizontal
        if((col <= 'E' && col >= 'A') || (col <= 'e' && col >= 'a')) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<5; ++i) {
                Button* b = get_p(row, col+i);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt1.gif");
                    else if(i==1) q.addFile(":/images/batt2.gif");
                    else if(i==2) q.addFile(":/images/batt3.gif");
                    else if(i==3) q.addFile(":/images/batt4.gif");
                    else if(i==4) q.addFile(":/images/batt5.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
        else if((col >= 'F' && col <= 'J') || (col >= 'f' && col <= 'j')) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<5; ++i) {
                Button* b = get_p(row, col-i);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt5.gif");
                    else if(i==1) q.addFile(":/images/batt4.gif");
                    else if(i==2) q.addFile(":/images/batt3.gif");
                    else if(i==3) q.addFile(":/images/batt2.gif");
                    else if(i==4) q.addFile(":/images/batt1.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool MainWindow::player_set_battle_ship(int row, int col) {
    if(ui->is_vertical->isChecked()) {
        if(row <= 7 && row >= 1) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<4; ++i) {
                Button* b = get_p(row+i, col);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt6.gif");
                    else if(i==1) q.addFile(":/images/batt7.gif");
                    else if(i==2) q.addFile(":/images/batt8.gif");
                    else if(i==3) q.addFile(":/images/batt10.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
        else if(row >= 7 && row <= 10) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<4; ++i) {
                Button* b = get_p(row-i, col);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt10.gif");
                    else if(i==1) q.addFile(":/images/batt9.gif");
                    else if(i==2) q.addFile(":/images/batt8.gif");
                    else if(i==3) q.addFile(":/images/batt6.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
    }
    else { //horizontal
        if((col <= 'E' && col >= 'A') || (col <= 'e' && col >= 'a')) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<4; ++i) {
                Button* b = get_p(row, col+i);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt1.gif");
                    else if(i==1) q.addFile(":/images/batt2.gif");
                    else if(i==2) q.addFile(":/images/batt3.gif");
                    else if(i==3) q.addFile(":/images/batt5.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
        else if((col >= 'F' && col <= 'J') || (col >= 'f' && col <= 'j')) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<4; ++i) {
                Button* b = get_p(row, col-i);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt5.gif");
                    else if(i==1) q.addFile(":/images/batt4.gif");
                    else if(i==2) q.addFile(":/images/batt3.gif");
                    else if(i==3) q.addFile(":/images/batt1.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool MainWindow::player_set_destroyer(int row, int col) {
    if(ui->is_vertical->isChecked()) {
        if(row <= 8 && row >= 1) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<3; ++i) {
                Button* b = get_p(row+i, col);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt6.gif");
                    else if(i==1) q.addFile(":/images/batt8.gif");
                    else if(i==2) q.addFile(":/images/batt10.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
        else if(row >= 8 && row <= 10) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<3; ++i) {
                Button* b = get_p(row-i, col);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt10.gif");
                    else if(i==1) q.addFile(":/images/batt8.gif");
                    else if(i==2) q.addFile(":/images/batt6.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
    }
    else { //horizontal
        if((col <= 'H' && col >= 'A') || (col <= 'h' && col >= 'a')) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<3; ++i) {
                Button* b = get_p(row, col+i);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt1.gif");
                    else if(i==1) q.addFile(":/images/batt3.gif");
                    else if(i==2) q.addFile(":/images/batt5.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
        else if((col >= 'I' && col <= 'J') || (col >= 'i' && col <= 'j')) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<3; ++i) {
                Button* b = get_p(row, col-i);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt5.gif");
                    else if(i==1) q.addFile(":/images/batt3.gif");
                    else if(i==2) q.addFile(":/images/batt1.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool MainWindow::player_set_sub(int row, int col) {
    if(ui->is_vertical->isChecked()) {
        if(row <= 8 && row >= 1) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<3; ++i) {
                Button* b = get_p(row+i, col);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt6.gif");
                    else if(i==1) q.addFile(":/images/batt7.gif");
                    else if(i==2) q.addFile(":/images/batt10.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
        else if(row >= 8 && row <= 10) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<3; ++i) {
                Button* b = get_p(row-i, col);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt10.gif");
                    else if(i==1) q.addFile(":/images/batt7.gif");
                    else if(i==2) q.addFile(":/images/batt6.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
    }
    else { //horizontal
        if((col <= 'H' && col >= 'A') || (col <= 'h' && col >= 'a')) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<3; ++i) {
                Button* b = get_p(row, col+i);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt1.gif");
                    else if(i==1) q.addFile(":/images/batt4.gif");
                    else if(i==2) q.addFile(":/images/batt5.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
        else if((col >= 'I' && col <= 'J') || (col >= 'i' && col <= 'j')) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<3; ++i) {
                Button* b = get_p(row, col-i);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt5.gif");
                    else if(i==1) q.addFile(":/images/batt4.gif");
                    else if(i==2) q.addFile(":/images/batt1.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool MainWindow::player_set_patrol(int row, int col) {
    if(ui->is_vertical->isChecked()) {
        if(row <= 9 && row >= 1) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<2; ++i) {
                Button* b = get_p(row+i, col);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt6.gif");
                    else if(i==1) q.addFile(":/images/batt10.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
        else if(row >= 10 && row <= 10) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<2; ++i) {
                Button* b = get_p(row-i, col);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt10.gif");
                    else if(i==1) q.addFile(":/images/batt6.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
    }
    else { //horizontal
        if((col <= 'I' && col >= 'A') || (col <= 'i' && col >= 'a')) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<2; ++i) {
                Button* b = get_p(row, col+i);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt1.gif");
                    else if(i==1) q.addFile(":/images/batt5.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
        else if((col >= 'J' && col <= 'J') || (col >= 'j' && col <= 'j')) {
            ui->shipset->setEnabled(true);
            for(int i=0; i<2; ++i) {
                Button* b = get_p(row, col-i);
                if(!b->has_ship) {
                    QIcon q;
                    b->maybe_ship = true;
                    possible_ships.push_back(b);
                    if(i==0) q.addFile(":/images/batt5.gif");
                    else if(i==1) q.addFile(":/images/batt1.gif");
                    b->setIcon(q);
                }
                else {
                    clear_maybe_ships();
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool MainWindow::player_set_ship(int row, char col) {
    if(state == SETTING_A_CARRIER) {
        return player_set_a_carrier(row, col);
    }
    else if(state == SETTING_BATTLESHIP) {
        return player_set_battle_ship(row, col);
    }
    else if(state == SETTING_DESTROYER) {
        return player_set_destroyer(row, col);
    }
    else if(state == SETTING_SUB) {
        return player_set_sub(row, col);
    }
    else if(state == SETTING_PATROL) {
        return player_set_patrol(row, col);
    }
    return false;
}

void MainWindow::set_ship() {
    for(unsigned int i=0; i<possible_ships.size(); ++i) {
        Button* b = possible_ships[i];
        b->has_ship = true;
        b->maybe_ship = false;
    }
    possible_ships.clear();
    if(state == SETTING_A_CARRIER) {
        state = SETTING_BATTLESHIP;
        ui->ship_to_set->setText("Setting ship: 4 Battle Ship");
    }
    else if(state == SETTING_BATTLESHIP) {
        state = SETTING_DESTROYER;
        ui->ship_to_set->setText("Setting ship: 3 Destroyer");
    }
    else if(state == SETTING_DESTROYER) {
        state = SETTING_SUB;
        ui->ship_to_set->setText("Setting ship: 3 Submarine");
    }
    else if(state == SETTING_SUB) {
        state = SETTING_PATROL;
        ui->ship_to_set->setText("Setting ship: 2 Patrol Boat");
    }
    else if(state == SETTING_PATROL) {
        setting_ships = false;
        if(!used_auto && connected) {
            sendMessage("Done");
            ui->auto_set_ships->setEnabled(false);
            if(!other_player_waiting) {
                state = PLAYER_TURN;
                ui->current_turn_label->setText("Player's turn");
            }
            else {
                state = OPPONENT_TURN;
                ui->current_turn_label->setText("Opponent's turn");
            }
        }
    }
    ui->shipset->setEnabled(false);
}

Button* MainWindow::get_p(int row, char col) {
    for(unsigned int i=0; i<player_buttons.size(); ++i) {
        Button* b = player_buttons[i];
        if(b->get_row() == row) {
            if(b->get_col() == (col - 64) || b->get_col() == (col - 96)) {
                return b;
            }
        }
    }
    return NULL;
}

Button* MainWindow::get_o(int row, char col) {
    for(unsigned int i=0; i<opponent_buttons.size(); ++i) {
        Button* b = opponent_buttons[i];
        if(b->get_row() == row) {
            if(b->get_col() == (col - 64) || b->get_col() == (col - 96)) {
                return b;
            }
        }
    }
    return NULL;
}

void MainWindow::clear_maybe_ships() {
    for(unsigned int i=0; i<possible_ships.size(); ++i) {
        possible_ships[i]->setIcon(QIcon(":images/batt101.gif"));
    }
    possible_ships.clear();

}

bool MainWindow::is_valid_rowcol(int row, char col) {
    if(row > 0 && row < 11) {
        if((col >= 'a' && col <= 'j') || (col >= 'A' && col <= 'J')) {
            return true;
        }
    }
    return false;
}
bool MainWindow::is_valid_row(int row) {
    if(row > 0 && row < 11) {
        return true;
    }
    return false;
}
bool MainWindow::is_valid_col(char col) {
    if((col >= 'a' && col <= 'j') || (col >= 'A' && col <= 'J')) {
        return true;
    }
    return false;
}

void MainWindow::row_box_changed() {
    clear_maybe_ships();
    int f = ui->row_box->text().toInt();
    if(is_valid_row(f)) {
        has_valid_row = true;
    }
    else {
        has_valid_row = false;
        ui->shipset->setEnabled(false);
    }
    if(has_valid_row && has_valid_col) {
        if(!player_set_ship(f, ui->column_box->text().toStdString().at(0))) {
            ui->shipset->setEnabled(false);
        }
    }
}

void MainWindow::col_box_changed() {
    clear_maybe_ships();
    if(setting_ships) {
        if(ui->column_box->text().size() > 0) {
            char c = ui->column_box->text().toStdString().at(0);
            if(is_valid_col(c)) {
                has_valid_col = true;
            }
            else {
                has_valid_col = false;
                ui->shipset->setEnabled(false);
            }
            if(has_valid_row && has_valid_col) {
                if(!player_set_ship(ui->row_box->text().toInt(), c)) {
                    ui->shipset->setEnabled(false);
                }
            }
        }
    }
}

void MainWindow::setClientMode() {
    if(!connected) {
        clientMode = true;
        ui->client_label->setText("Client Mode");
        ui->ip_address_box->setText("127.0.0.1");
        ui->connect_server_button->setEnabled(true);
        ui->port_box->setEnabled(true);
    }
}

void MainWindow::setServerMode() {
    if(!connected) {
        clientMode = false;
        ui->client_label->setText("Server Mode");
        connectionSocket = new QTcpServer(this);
        if (!connectionSocket->listen()) {
            QMessageBox::critical(this, tr("Echo Server"),
                              tr("Unable to start the server: %1.")
                              .arg(connectionSocket->errorString()));
            close();
            return;
        }
        ui->ip_address_box->setText("127.0.0.1");
        QString portNum;
        portNum.setNum(connectionSocket->serverPort());
        ui->port_box->setText(portNum);
        print("Server started - Waiting for Connection");
        connect(connectionSocket, SIGNAL(newConnection()), this, SLOT(connectToClient()));
        ui->connect_server_button->setEnabled(false);
        ui->port_box->setEnabled(false);
    }
}

void MainWindow::disconnection() {
    print("disconnected");
    ui->connected_label->setText("Status: Disconnected");
    connected = false;
}

void MainWindow::connectToClient() {
    print("Connection request Arrived");
    communicationSocket = connectionSocket->nextPendingConnection();
    connect(communicationSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(communicationSocket, SIGNAL(disconnected()),
            communicationSocket, SLOT(deleteLater()));
    connect(communicationSocket, SIGNAL(disconnected()),
            this, SLOT(disconnection()));
    connect(communicationSocket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));
    connected = true;
    ui->connected_label->setText("Status: Connected");
    blockSize = 0;
    ui->column_box->setEnabled(true);
    ui->row_box->setEnabled(true);
    ui->auto_set_ships->setEnabled(true);
}

void MainWindow::connectToServer() {
    if (!clientMode) {
        return;
    }
    if (connected) {
        return;
    }
    communicationSocket = new QTcpSocket(this);
    connect(communicationSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(communicationSocket, SIGNAL(disconnected()),
                communicationSocket, SLOT(deleteLater()));
    connect(communicationSocket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));

    communicationSocket->abort();
    communicationSocket->connectToHost(ui->ip_address_box->text(),
                             ui->port_box->text().toInt());
    blockSize = 0;
    print("Connecting to Server");
    if(communicationSocket->waitForConnected(50)) {
        ui->connected_label->setText("Status: Connected");
        connected = true;
        ui->column_box->setEnabled(true);
        ui->row_box->setEnabled(true);
        ui->auto_set_ships->setEnabled(true);
    }
}

void MainWindow::sendMessage(QString s) {
    if(connected) {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out << (quint16)0;
        out << s;
        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));
        communicationSocket->write(block);
        print(tr("Sending message to %1").arg(communicationSocket->peerPort()));
    }
}

void MainWindow::readFromSocket() {
    QDataStream in(communicationSocket);
    in.setVersion(QDataStream::Qt_4_0);
    if (blockSize == 0) {
        if (communicationSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }
    if (communicationSocket->bytesAvailable() < blockSize)
        return;
    QString message;
    in >> message;
    print(message);
    if(message == "Done" && !other_player_waiting) {
        other_player_waiting = true;
    }
    else if(message == "You Won") {
        print("You Won!");
        for(unsigned int i=0; i<player_buttons.size(); ++i) {
            player_buttons[i]->setEnabled(false);
            opponent_buttons[i]->setEnabled(false);
        }
    }
    else if(state == PLAYER_TURN) {
        //get hit or miss
        print("todo recieve hit or miss");
        if(message.size() < 1) {
            print("Error 3");
        }
        else {
            if(message.at(0) == 'H') {
                Button *b = get_o(row_sent, col_sent);
                QIcon q(":/images/batt103.gif");
                b->setIcon(q);
                player_hits++;
                if(player_hits >= 17) {
                    print("You Won!");
                    for(unsigned int i=0; i<player_buttons.size(); ++i) {
                        player_buttons[i]->setEnabled(false);
                        opponent_buttons[i]->setEnabled(false);
                    }
                    ui->win_label->setText("You Won!");
                }
                hitmiss_ratio = 1;
                if(player_misses != 0) {
                    hitmiss_ratio = (double)player_hits / ((double)player_misses + (double)player_hits);
                }
            }
            else if(message.at(0) == 'M') {
                Button *b = get_o(row_sent, col_sent);
                QIcon q(":/images/batt102.gif");
                b->setIcon(q);
                player_misses++;
                hitmiss_ratio = 1;
                if(player_misses != 0) {
                    hitmiss_ratio = (double)player_hits / ((double)player_misses + (double)player_hits);
                }
            }
            else {
                print("errornothit or miss");
                print(message);
            }
            state = OPPONENT_TURN;
            ui->current_turn_label->setText("Opponent's turn");
        }
    }
    else if(state == OPPONENT_TURN) {
        print("opponentturn read");
        QStringList s;
        s = message.split(' ');
        for(int i=0; i<s.size(); i++) {
            print(s.at(i));
        }
        int row = s.at(1).toInt();
        char col = s.at(2).toStdString().at(0);
        Button* b = get_p(row, col);
        if(s.size() < 3) {
            print("error 5");
        }
        else if(!b->hit) {
            if(b->has_ship) {
                b->hit = true;
                sendMessage("H");
                QIcon q(":/images/batt103.gif");
                b->setIcon(q);
                opponent_hits++;
                if(opponent_hits >= 17) {
                    print("You Lost");
                    for(unsigned int i=0; i<player_buttons.size(); ++i) {
                        player_buttons[i]->setEnabled(false);
                        opponent_buttons[i]->setEnabled(false);
                    }
                    ui->win_label->setText("You Lost");
                }
            }
            else {
                b->hit = true;
                opponent_misses++;
                sendMessage("M");
                QIcon q(":/images/batt102.gif");
                b->setIcon(q);
            }
            state = PLAYER_TURN;
            ui->current_turn_label->setText("Player's turn");
        }
    }
    blockSize = 0;
}

void MainWindow::btn_clicked() {
    Button* p = (Button*) sender();
    if(p->player_ship) {
        //ignore input
    }
    else { //clicked on opponent
        if(state == PLAYER_TURN && !p->hit) {
            QString s;
            s.append("S ");
            QString f;
            f.setNum(p->get_row());
            s.append(f);
            s.append(" ");
            f = p->get_col() + 96;
            s.append(f);
            row_sent = p->get_row();
            col_sent = p->get_col() + 96;
            print("clicked on opopnent");
            print(s);
            sendMessage(s);
        }
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError) {
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
         QMessageBox::information(this, tr("Echo Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
         QMessageBox::information(this, tr("Echo Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
         QMessageBox::information(this, tr("Echo Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(communicationSocket->errorString()));
    }
}

void MainWindow::test() {
    if(state == OPPONENT_TURN) {
        print("oponentturn");
    }
    else if(state == PLAYER_TURN) {
        print("playerturn");
    }
    else {
        print("lolidk");
    }
}

void MainWindow::print(QString s) {
    s.append("");
    //ui->debugbox->appendPlainText(s);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText("Authors: Ryan Konkul(rkonku2) and Scott Prentice(sprent2)\n\nBattleship - Project 5\n"
                   "CS340 Fall 2011 - Professor Troy\n12/1/2011");
    msgBox.exec();
}

void MainWindow::on_actionConnecting_Help_triggered() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Connecting Help");
    msgBox.setText("To connect to another instance of the program, one is decided to be the server. "
                   "This instance selects Server from the drop down menu. The client instance enters "
                   "the IP and port of the Server instance. The client then clicks connect to server.");
    msgBox.exec();
}

void MainWindow::on_actionBattleship_Help_triggered() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Battleship Help");
    msgBox.setText("To begin the game after connecting to another player, the players may set their "
                   "ships using the Auto Set Ships button or select a row and col and whether the "
                   "ship is vertical or not then pressing Set Ship. Once both players have their "
                   "ships set, whoever placed ships first goes first. Each player takes turns clicking "
                   "on the opponent board. The game ends when one player has sunk the other's fleet.");
    msgBox.exec();
}

void MainWindow::on_actionStatistics_triggered() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Statistics");
    msgBox.setText(tr("Number of player hits:     %1"
                   "\nNumber of player misses:   %2"
                   "\nPlayer hit / miss ratio:   %3"
                   "\n"
                   "\nNumber of opponent hits:   %4"
                   "\nNumber of opponent misses: %5").arg(player_hits).arg(player_misses).arg(hitmiss_ratio).arg(
                                                                               opponent_hits).arg(opponent_misses));
    msgBox.exec();
}

void MainWindow::on_actionQuit_triggered()  {
     exit(0);
}

