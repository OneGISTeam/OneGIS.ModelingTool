/****************************************************************************
** Meta object code from reading C++ file 'C_DialogBehaviorDebug.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../C_DialogBehaviorDebug.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_DialogBehaviorDebug.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_C_DialogBehaviorDebug[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_C_DialogBehaviorDebug[] = {
    "C_DialogBehaviorDebug\0"
};

void C_DialogBehaviorDebug::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData C_DialogBehaviorDebug::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject C_DialogBehaviorDebug::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_C_DialogBehaviorDebug,
      qt_meta_data_C_DialogBehaviorDebug, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &C_DialogBehaviorDebug::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *C_DialogBehaviorDebug::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *C_DialogBehaviorDebug::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_C_DialogBehaviorDebug))
        return static_cast<void*>(const_cast< C_DialogBehaviorDebug*>(this));
    if (!strcmp(_clname, "Ui::BehaviorDebugDialog"))
        return static_cast< Ui::BehaviorDebugDialog*>(const_cast< C_DialogBehaviorDebug*>(this));
    return QDialog::qt_metacast(_clname);
}

int C_DialogBehaviorDebug::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
