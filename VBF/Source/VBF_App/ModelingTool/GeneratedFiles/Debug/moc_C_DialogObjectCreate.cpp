/****************************************************************************
** Meta object code from reading C++ file 'C_DialogObjectCreate.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../C_DialogObjectCreate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_DialogObjectCreate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_C_DialogObjectCreate[] = {

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
      31,   22,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_C_DialogObjectCreate[] = {
    "C_DialogObjectCreate\0\0rowCount\0"
    "on_currentRow_changed(int)\0"
};

void C_DialogObjectCreate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        C_DialogObjectCreate *_t = static_cast<C_DialogObjectCreate *>(_o);
        switch (_id) {
        case 0: _t->on_currentRow_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData C_DialogObjectCreate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject C_DialogObjectCreate::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_C_DialogObjectCreate,
      qt_meta_data_C_DialogObjectCreate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &C_DialogObjectCreate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *C_DialogObjectCreate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *C_DialogObjectCreate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_C_DialogObjectCreate))
        return static_cast<void*>(const_cast< C_DialogObjectCreate*>(this));
    if (!strcmp(_clname, "Ui::CreateObjectDialog"))
        return static_cast< Ui::CreateObjectDialog*>(const_cast< C_DialogObjectCreate*>(this));
    return QDialog::qt_metacast(_clname);
}

int C_DialogObjectCreate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
