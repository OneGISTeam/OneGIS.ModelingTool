/****************************************************************************
** Meta object code from reading C++ file 'C_WidgetObjectClassBehavior.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../C_WidgetObjectClassBehavior.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_WidgetObjectClassBehavior.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_C_WidgetObjectClassBehavior[] = {

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
      29,   28,   28,   28, 0x08,
      61,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_C_WidgetObjectClassBehavior[] = {
    "C_WidgetObjectClassBehavior\0\0"
    "on_editPublicBehavior_clicked()\0"
    "on_addPrivateBehavior_clicked()\0"
};

void C_WidgetObjectClassBehavior::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        C_WidgetObjectClassBehavior *_t = static_cast<C_WidgetObjectClassBehavior *>(_o);
        switch (_id) {
        case 0: _t->on_editPublicBehavior_clicked(); break;
        case 1: _t->on_addPrivateBehavior_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData C_WidgetObjectClassBehavior::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject C_WidgetObjectClassBehavior::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_C_WidgetObjectClassBehavior,
      qt_meta_data_C_WidgetObjectClassBehavior, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &C_WidgetObjectClassBehavior::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *C_WidgetObjectClassBehavior::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *C_WidgetObjectClassBehavior::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_C_WidgetObjectClassBehavior))
        return static_cast<void*>(const_cast< C_WidgetObjectClassBehavior*>(this));
    if (!strcmp(_clname, "Ui::ObjectClassBehaviorWidget"))
        return static_cast< Ui::ObjectClassBehaviorWidget*>(const_cast< C_WidgetObjectClassBehavior*>(this));
    return QWidget::qt_metacast(_clname);
}

int C_WidgetObjectClassBehavior::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
