/****************************************************************************
** Meta object code from reading C++ file 'C_MainUI.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../C_MainUI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_MainUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_C_MainUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   10,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_C_MainUI[] = {
    "C_MainUI\0\0window\0"
    "on_subwindow_activated(QMdiSubWindow*)\0"
};

void C_MainUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        C_MainUI *_t = static_cast<C_MainUI *>(_o);
        switch (_id) {
        case 0: _t->on_subwindow_activated((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData C_MainUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject C_MainUI::staticMetaObject = {
    { &IC_MainUI::staticMetaObject, qt_meta_stringdata_C_MainUI,
      qt_meta_data_C_MainUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &C_MainUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *C_MainUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *C_MainUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_C_MainUI))
        return static_cast<void*>(const_cast< C_MainUI*>(this));
    return IC_MainUI::qt_metacast(_clname);
}

int C_MainUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IC_MainUI::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
