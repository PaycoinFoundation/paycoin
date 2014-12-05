/****************************************************************************
** Meta object code from reading C++ file 'multisigaddressentry.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/multisigaddressentry.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multisigaddressentry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MultisigAddressEntry[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      71,   63,   21,   21, 0x0a,
      94,   21,   21,   21, 0x0a,
     109,  102,   21,   21, 0x08,
     140,   21,   21,   21, 0x08,
     165,   21,   21,   21, 0x08,
     199,  191,   21,   21, 0x08,
     231,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MultisigAddressEntry[] = {
    "MultisigAddressEntry\0\0entry\0"
    "removeEntry(MultisigAddressEntry*)\0"
    "enabled\0setRemoveEnabled(bool)\0clear()\0"
    "pubkey\0on_pubkey_textChanged(QString)\0"
    "on_pasteButton_clicked()\0"
    "on_deleteButton_clicked()\0address\0"
    "on_address_textChanged(QString)\0"
    "on_addressBookButton_clicked()\0"
};

void MultisigAddressEntry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MultisigAddressEntry *_t = static_cast<MultisigAddressEntry *>(_o);
        switch (_id) {
        case 0: _t->removeEntry((*reinterpret_cast< MultisigAddressEntry*(*)>(_a[1]))); break;
        case 1: _t->setRemoveEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->clear(); break;
        case 3: _t->on_pubkey_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_pasteButton_clicked(); break;
        case 5: _t->on_deleteButton_clicked(); break;
        case 6: _t->on_address_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_addressBookButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MultisigAddressEntry::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MultisigAddressEntry::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_MultisigAddressEntry,
      qt_meta_data_MultisigAddressEntry, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MultisigAddressEntry::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MultisigAddressEntry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MultisigAddressEntry::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MultisigAddressEntry))
        return static_cast<void*>(const_cast< MultisigAddressEntry*>(this));
    return QFrame::qt_metacast(_clname);
}

int MultisigAddressEntry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MultisigAddressEntry::removeEntry(MultisigAddressEntry * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
