/****************************************************************************
** Meta object code from reading C++ file 'control.h'
**
** Created: Sun 15. Jan 22:02:25 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../control.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'control.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Control[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      18,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   28,    8,    8, 0x0a,
      59,   53,    8,    8, 0x0a,
      77,   53,    8,    8, 0x0a,
      94,   53,    8,    8, 0x0a,
     108,   53,    8,    8, 0x0a,
     118,   53,    8,    8, 0x0a,
     135,   53,    8,    8, 0x0a,
     153,   28,    8,    8, 0x0a,
     170,   28,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Control[] = {
    "Control\0\0zoomin()\0zoomout()\0show\0"
    "showWaypoints(bool)\0value\0simWallForce(int)\0"
    "simPedForce(int)\0simSpeed(int)\0simh(int)\0"
    "mlTendency(bool)\0mlLookAhead(bool)\0"
    "showForces(bool)\0showDirection(bool)\0"
};

void Control::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Control *_t = static_cast<Control *>(_o);
        switch (_id) {
        case 0: _t->zoomin(); break;
        case 1: _t->zoomout(); break;
        case 2: _t->showWaypoints((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->simWallForce((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->simPedForce((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->simSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->simh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->mlTendency((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->mlLookAhead((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->showForces((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->showDirection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Control::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Control::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_Control,
      qt_meta_data_Control, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Control::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Control::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Control::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Control))
        return static_cast<void*>(const_cast< Control*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int Control::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Control::zoomin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Control::zoomout()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
