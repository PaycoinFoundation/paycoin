/****************************************************************************
** Meta object code from reading C++ file 'multisiginputentry.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/multisiginputentry.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multisiginputentry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MultisigInputEntry[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   20,   19,   19, 0x05,
      59,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      82,   74,   19,   19, 0x0a,
     105,   19,   19,   19, 0x0a,
     127,  113,   19,   19, 0x08,
     165,   19,   19,   19, 0x08,
     203,   19,   19,   19, 0x08,
     235,  229,   19,   19, 0x08,
     281,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MultisigInputEntry[] = {
    "MultisigInputEntry\0\0entry\0"
    "removeEntry(MultisigInputEntry*)\0"
    "updateAmount()\0enabled\0setRemoveEnabled(bool)\0"
    "clear()\0transactionId\0"
    "on_transactionId_textChanged(QString)\0"
    "on_pasteTransactionIdButton_clicked()\0"
    "on_deleteButton_clicked()\0index\0"
    "on_transactionOutput_currentIndexChanged(int)\0"
    "on_pasteRedeemScriptButton_clicked()\0"
};

void MultisigInputEntry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MultisigInputEntry *_t = static_cast<MultisigInputEntry *>(_o);
        switch (_id) {
        case 0: _t->removeEntry((*reinterpret_cast< MultisigInputEntry*(*)>(_a[1]))); break;
        case 1: _t->updateAmount(); break;
        case 2: _t->setRemoveEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->clear(); break;
        case 4: _t->on_transactionId_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_pasteTransactionIdButton_clicked(); break;
        case 6: _t->on_deleteButton_clicked(); break;
        case 7: _t->on_transactionOutput_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_pasteRedeemScriptButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MultisigInputEntry::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MultisigInputEntry::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_MultisigInputEntry,
      qt_meta_data_MultisigInputEntry, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MultisigInputEntry::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MultisigInputEntry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MultisigInputEntry::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MultisigInputEntry))
        return static_cast<void*>(const_cast< MultisigInputEntry*>(this));
    return QFrame::qt_metacast(_clname);
}

int MultisigInputEntry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MultisigInputEntry::removeEntry(MultisigInputEntry * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MultisigInputEntry::updateAmount()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
