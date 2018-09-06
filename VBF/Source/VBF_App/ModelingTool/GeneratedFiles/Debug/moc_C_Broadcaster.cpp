/****************************************************************************
** Meta object code from reading C++ file 'C_Broadcaster.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../C_Broadcaster.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_Broadcaster.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_C_Broadcaster[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      60,   14,   14,   14, 0x05,
      99,   14,   14,   14, 0x05,
     145,   14,   14,   14, 0x05,
     196,   14,   14,   14, 0x05,
     236,   14,   14,   14, 0x05,
     284,   14,   14,   14, 0x05,
     314,   14,   14,   14, 0x05,
     367,   14,   14,   14, 0x05,
     406,   14,   14,   14, 0x05,
     457,   14,   14,   14, 0x05,
     497,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_C_Broadcaster[] = {
    "C_Broadcaster\0\0"
    "signal_STObjectAdded(vector<CVBF_STObject*>)\0"
    "signal_STObjectRemoved(vector<string>)\0"
    "signal_STObjectEdited(vector<CVBF_STObject*>)\0"
    "signal_STObjectVisibilityChanged(map<string,bool>)\0"
    "signal_STObjectSelected(vector<string>)\0"
    "signal_STObjectFiltered(vector<CVBF_STObject*>)\0"
    "signal_STObjectStyleChanged()\0"
    "signal_RelationAdded(vector<CVBF_STObjectRelation*>)\0"
    "signal_RelationRemoved(vector<string>)\0"
    "signal_RelationVisibilityChanged(map<string,bool>)\0"
    "signal_RelationSelected(vector<string>)\0"
    "signal_RelationStyleChanged()\0"
};

void C_Broadcaster::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        C_Broadcaster *_t = static_cast<C_Broadcaster *>(_o);
        switch (_id) {
        case 0: _t->signal_STObjectAdded((*reinterpret_cast< vector<CVBF_STObject*>(*)>(_a[1]))); break;
        case 1: _t->signal_STObjectRemoved((*reinterpret_cast< vector<string>(*)>(_a[1]))); break;
        case 2: _t->signal_STObjectEdited((*reinterpret_cast< vector<CVBF_STObject*>(*)>(_a[1]))); break;
        case 3: _t->signal_STObjectVisibilityChanged((*reinterpret_cast< map<string,bool>(*)>(_a[1]))); break;
        case 4: _t->signal_STObjectSelected((*reinterpret_cast< vector<string>(*)>(_a[1]))); break;
        case 5: _t->signal_STObjectFiltered((*reinterpret_cast< vector<CVBF_STObject*>(*)>(_a[1]))); break;
        case 6: _t->signal_STObjectStyleChanged(); break;
        case 7: _t->signal_RelationAdded((*reinterpret_cast< vector<CVBF_STObjectRelation*>(*)>(_a[1]))); break;
        case 8: _t->signal_RelationRemoved((*reinterpret_cast< vector<string>(*)>(_a[1]))); break;
        case 9: _t->signal_RelationVisibilityChanged((*reinterpret_cast< map<string,bool>(*)>(_a[1]))); break;
        case 10: _t->signal_RelationSelected((*reinterpret_cast< vector<string>(*)>(_a[1]))); break;
        case 11: _t->signal_RelationStyleChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData C_Broadcaster::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject C_Broadcaster::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_C_Broadcaster,
      qt_meta_data_C_Broadcaster, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &C_Broadcaster::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *C_Broadcaster::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *C_Broadcaster::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_C_Broadcaster))
        return static_cast<void*>(const_cast< C_Broadcaster*>(this));
    return QObject::qt_metacast(_clname);
}

int C_Broadcaster::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void C_Broadcaster::signal_STObjectAdded(vector<CVBF_STObject*> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void C_Broadcaster::signal_STObjectRemoved(vector<string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void C_Broadcaster::signal_STObjectEdited(vector<CVBF_STObject*> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void C_Broadcaster::signal_STObjectVisibilityChanged(map<string,bool> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void C_Broadcaster::signal_STObjectSelected(vector<string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void C_Broadcaster::signal_STObjectFiltered(vector<CVBF_STObject*> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void C_Broadcaster::signal_STObjectStyleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void C_Broadcaster::signal_RelationAdded(vector<CVBF_STObjectRelation*> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void C_Broadcaster::signal_RelationRemoved(vector<string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void C_Broadcaster::signal_RelationVisibilityChanged(map<string,bool> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void C_Broadcaster::signal_RelationSelected(vector<string> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void C_Broadcaster::signal_RelationStyleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}
QT_END_MOC_NAMESPACE
