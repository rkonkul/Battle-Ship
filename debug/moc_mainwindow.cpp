/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Dec 1 19:13:00 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      26,   11,   11,   11, 0x0a,
      44,   11,   11,   11, 0x0a,
      62,   11,   11,   11, 0x0a,
      73,   11,   11,   11, 0x0a,
      90,   11,   11,   11, 0x0a,
     108,   11,   11,   11, 0x0a,
     124,   11,   11,   11, 0x0a,
     140,   11,   11,   11, 0x0a,
     157,   11,   11,   11, 0x0a,
     187,  175,   11,   11, 0x0a,
     230,   11,   11,   11, 0x0a,
     246,   11,   11,   11, 0x0a,
     253,   11,   11,   11, 0x08,
     280,   11,   11,   11, 0x08,
     317,   11,   11,   11, 0x08,
     354,   11,   11,   11, 0x08,
     380,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0btn_clicked()\0row_box_changed()\0"
    "col_box_changed()\0set_ship()\0"
    "auto_set_ships()\0connectToServer()\0"
    "setClientMode()\0setServerMode()\0"
    "readFromSocket()\0connectToClient()\0"
    "socketError\0displayError(QAbstractSocket::SocketError)\0"
    "disconnection()\0test()\0"
    "on_actionAbout_triggered()\0"
    "on_actionConnecting_Help_triggered()\0"
    "on_actionBattleship_Help_triggered()\0"
    "on_actionQuit_triggered()\0"
    "on_actionStatistics_triggered()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: btn_clicked(); break;
        case 1: row_box_changed(); break;
        case 2: col_box_changed(); break;
        case 3: set_ship(); break;
        case 4: auto_set_ships(); break;
        case 5: connectToServer(); break;
        case 6: setClientMode(); break;
        case 7: setServerMode(); break;
        case 8: readFromSocket(); break;
        case 9: connectToClient(); break;
        case 10: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 11: disconnection(); break;
        case 12: test(); break;
        case 13: on_actionAbout_triggered(); break;
        case 14: on_actionConnecting_Help_triggered(); break;
        case 15: on_actionBattleship_Help_triggered(); break;
        case 16: on_actionQuit_triggered(); break;
        case 17: on_actionStatistics_triggered(); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
