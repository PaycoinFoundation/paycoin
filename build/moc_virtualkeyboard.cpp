/****************************************************************************
** Meta object code from reading C++ file 'virtualkeyboard.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/virtualkeyboard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'virtualkeyboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KeyboardKey[] = {

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

static const char qt_meta_stringdata_KeyboardKey[] = {
    "KeyboardKey\0"
};

void KeyboardKey::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData KeyboardKey::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KeyboardKey::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_KeyboardKey,
      qt_meta_data_KeyboardKey, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KeyboardKey::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KeyboardKey::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KeyboardKey::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KeyboardKey))
        return static_cast<void*>(const_cast< KeyboardKey*>(this));
    return QToolButton::qt_metacast(_clname);
}

int KeyboardKey::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_VirtualKeyboard[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      37,   30,   16,   16, 0x0a,
      56,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VirtualKeyboard[] = {
    "VirtualKeyboard\0\0keyPressed()\0sender\0"
    "setInput(QObject*)\0toggleKeyboard()\0"
};

void VirtualKeyboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VirtualKeyboard *_t = static_cast<VirtualKeyboard *>(_o);
        switch (_id) {
        case 0: _t->keyPressed(); break;
        case 1: _t->setInput((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: _t->toggleKeyboard(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VirtualKeyboard::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VirtualKeyboard::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VirtualKeyboard,
      qt_meta_data_VirtualKeyboard, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VirtualKeyboard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VirtualKeyboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VirtualKeyboard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VirtualKeyboard))
        return static_cast<void*>(const_cast< VirtualKeyboard*>(this));
    return QWidget::qt_metacast(_clname);
}

int VirtualKeyboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
