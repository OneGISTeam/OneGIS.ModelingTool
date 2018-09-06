/****************************************************************************
** Meta object code from reading C++ file 'C_ViewWidgetTimeAxis.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../C_ViewWidgetTimeAxis.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_ViewWidgetTimeAxis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_C_ViewWidgetTimeAxis[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,
      44,   38,   21,   21, 0x08,
      69,   38,   21,   21, 0x08,
      94,   38,   21,   21, 0x08,
     125,   21,   21,   21, 0x08,
     149,   21,   21,   21, 0x08,
     169,   21,   21,   21, 0x08,
     189,   21,   21,   21, 0x08,
     210,   21,   21,   21, 0x08,
     234,   21,   21,   21, 0x08,
     260,   21,   21,   21, 0x08,
     284,   21,   21,   21, 0x08,
     309,   21,   21,   21, 0x08,
     337,  331,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_C_ViewWidgetTimeAxis[] = {
    "C_ViewWidgetTimeAxis\0\0on_TimerEvent()\0"
    "event\0mousePress(QMouseEvent*)\0"
    "mouseWheel(QWheelEvent*)\0"
    "mouseDoubleClick(QMouseEvent*)\0"
    "mouseMove(QMouseEvent*)\0leaveEvent(QEvent*)\0"
    "enterEvent(QEvent*)\0on_playBtn_clicked()\0"
    "on_speedUpBtn_clicked()\0"
    "on_speedDownBtn_clicked()\0"
    "on_forwardBtn_clicked()\0"
    "on_backwardBtn_clicked()\0on_resetBtn_clicked()\0"
    "state\0On_timePointCheckBox_stateChanged(int)\0"
};

void C_ViewWidgetTimeAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        C_ViewWidgetTimeAxis *_t = static_cast<C_ViewWidgetTimeAxis *>(_o);
        switch (_id) {
        case 0: _t->on_TimerEvent(); break;
        case 1: _t->mousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseWheel((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 3: _t->mouseDoubleClick((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->mouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->leaveEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 6: _t->enterEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 7: _t->on_playBtn_clicked(); break;
        case 8: _t->on_speedUpBtn_clicked(); break;
        case 9: _t->on_speedDownBtn_clicked(); break;
        case 10: _t->on_forwardBtn_clicked(); break;
        case 11: _t->on_backwardBtn_clicked(); break;
        case 12: _t->on_resetBtn_clicked(); break;
        case 13: _t->On_timePointCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData C_ViewWidgetTimeAxis::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject C_ViewWidgetTimeAxis::staticMetaObject = {
    { &IC_ViewWidget::staticMetaObject, qt_meta_stringdata_C_ViewWidgetTimeAxis,
      qt_meta_data_C_ViewWidgetTimeAxis, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &C_ViewWidgetTimeAxis::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *C_ViewWidgetTimeAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *C_ViewWidgetTimeAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_C_ViewWidgetTimeAxis))
        return static_cast<void*>(const_cast< C_ViewWidgetTimeAxis*>(this));
    if (!strcmp(_clname, "Ui::ViewWidgetTimeAxis"))
        return static_cast< Ui::ViewWidgetTimeAxis*>(const_cast< C_ViewWidgetTimeAxis*>(this));
    return IC_ViewWidget::qt_metacast(_clname);
}

int C_ViewWidgetTimeAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IC_ViewWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
