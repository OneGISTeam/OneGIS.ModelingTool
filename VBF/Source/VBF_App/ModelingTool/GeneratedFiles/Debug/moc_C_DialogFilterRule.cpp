/****************************************************************************
** Meta object code from reading C++ file 'C_DialogFilterRule.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../C_DialogFilterRule.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_DialogFilterRule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_C_DialogFilterRule[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      33,   19,   19,   19, 0x08,
      45,   19,   19,   19, 0x08,
      81,   19,   19,   19, 0x08,
      93,   19,   19,   19, 0x08,
     105,   19,   19,   19, 0x08,
     117,   19,   19,   19, 0x08,
     129,   19,   19,   19, 0x08,
     141,   19,   19,   19, 0x08,
     153,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_C_DialogFilterRule[] = {
    "C_DialogFilterRule\0\0onBtnClear()\0"
    "onBtnSave()\0onDoubleClickItem(QListWidgetItem*)\0"
    "onClick_1()\0onClick_2()\0onClick_3()\0"
    "onClick_4()\0onClick_5()\0onClick_6()\0"
    "onClick_7()\0"
};

void C_DialogFilterRule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        C_DialogFilterRule *_t = static_cast<C_DialogFilterRule *>(_o);
        switch (_id) {
        case 0: _t->onBtnClear(); break;
        case 1: _t->onBtnSave(); break;
        case 2: _t->onDoubleClickItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->onClick_1(); break;
        case 4: _t->onClick_2(); break;
        case 5: _t->onClick_3(); break;
        case 6: _t->onClick_4(); break;
        case 7: _t->onClick_5(); break;
        case 8: _t->onClick_6(); break;
        case 9: _t->onClick_7(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData C_DialogFilterRule::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject C_DialogFilterRule::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_C_DialogFilterRule,
      qt_meta_data_C_DialogFilterRule, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &C_DialogFilterRule::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *C_DialogFilterRule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *C_DialogFilterRule::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_C_DialogFilterRule))
        return static_cast<void*>(const_cast< C_DialogFilterRule*>(this));
    if (!strcmp(_clname, "Ui::C_DialogFilterRule"))
        return static_cast< Ui::C_DialogFilterRule*>(const_cast< C_DialogFilterRule*>(this));
    return QDialog::qt_metacast(_clname);
}

int C_DialogFilterRule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
