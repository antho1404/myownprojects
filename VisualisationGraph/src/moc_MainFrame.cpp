/****************************************************************************
** Meta object code from reading C++ file 'MainFrame.h'
**
** Created: Tue Mar 2 15:21:04 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "view/MainFrame.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainFrame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainFrame[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      21,   10,   10,   10, 0x0a,
      32,   10,   10,   10, 0x0a,
      54,   10,   10,   10, 0x0a,
      72,   68,   10,   10, 0x0a,
      92,   10,   10,   10, 0x0a,
     103,   10,   10,   10, 0x0a,
     119,   10,   10,   10, 0x0a,
     135,  133,   10,   10, 0x0a,
     154,  133,   10,   10, 0x0a,
     173,  133,   10,   10, 0x0a,
     195,  133,   10,   10, 0x0a,
     216,  133,   10,   10, 0x0a,
     236,  133,   10,   10, 0x0a,
     259,  253,   10,   10, 0x0a,
     285,  280,   10,   10, 0x0a,
     326,   10,  312,   10, 0x0a,
     340,   10,   10,   10, 0x0a,
     350,   68,   10,   10, 0x0a,
     366,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainFrame[] = {
    "MainFrame\0\0runAlgo()\0stopAlgo()\0"
    "importGraphFromFile()\0importGraph()\0"
    "src\0importGraph(string)\0newGraph()\0"
    "generateGraph()\0exportGraph()\0b\0"
    "toolsVisible(bool)\0stateVisible(bool)\0"
    "showSmallWindow(bool)\0showFullScreen(bool)\0"
    "annimateGraph(bool)\0showValues(bool)\0"
    "speed\0changeAlgoSpeed(int)\0flag\0"
    "changeAlgoInteraction(int)\0list<string>*\0"
    "getAlgoList()\0addAlgo()\0addAlgo(string)\0"
    "removeAlgo()\0"
};

const QMetaObject MainFrame::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainFrame,
      qt_meta_data_MainFrame, 0 }
};

const QMetaObject *MainFrame::metaObject() const
{
    return &staticMetaObject;
}

void *MainFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainFrame))
        return static_cast<void*>(const_cast< MainFrame*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: runAlgo(); break;
        case 1: stopAlgo(); break;
        case 2: importGraphFromFile(); break;
        case 3: importGraph(); break;
        case 4: importGraph((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 5: newGraph(); break;
        case 6: generateGraph(); break;
        case 7: exportGraph(); break;
        case 8: toolsVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: stateVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: showSmallWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: showFullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: annimateGraph((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: showValues((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: changeAlgoSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: changeAlgoInteraction((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: { list<string>* _r = getAlgoList();
            if (_a[0]) *reinterpret_cast< list<string>**>(_a[0]) = _r; }  break;
        case 17: addAlgo(); break;
        case 18: addAlgo((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 19: removeAlgo(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
