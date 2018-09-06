/****************************************************************************
** Meta object code from reading C++ file 'C_WidgetObjectPosition.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../C_WidgetObjectPosition.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_WidgetObjectPosition.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_C_WidgetObjectPosition[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x0a,
      49,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_C_WidgetObjectPosition[] = {
    "C_WidgetObjectPosition\0\0"
    "cbTimeFormatChanged(int)\0"
    "cbPostionFormatChanged(int)\0"
};

void C_WidgetObjectPosition::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        C_WidgetObjectPosition *_t = static_cast<C_WidgetObjectPosition *>(_o);
        switch (_id) {
        case 0: _t->cbTimeFormatChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->cbPostionFormatChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData C_WidgetObjectPosition::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject C_WidgetObjectPosition::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_C_WidgetObjectPosition,
      qt_meta_data_C_WidgetObjectPosition, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &C_WidgetObjectPosition::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *C_WidgetObjectPosition::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *C_WidgetObjectPosition::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_C_WidgetObjectPosition))
        return static_cast<void*>(const_cast< C_WidgetObjectPosition*>(this));
    if (!strcmp(_clname, "Ui::ObjectPositionWidget"))
        return static_cast< Ui::ObjectPositionWidget*>(const_cast< C_WidgetObjectPosition*>(this));
    return QDialog::qt_metacast(_clname);
}

int C_WidgetObjectPosition::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
