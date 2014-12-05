/****************************************************************************
** Meta object code from reading C++ file 'mintingview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/mintingview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mintingview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MintingView[] = {

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
      13,   12,   12,   12, 0x0a,
      33,   29,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MintingView[] = {
    "MintingView\0\0exportClicked()\0idx\0"
    "chooseMintingInterval(int)\0"
};

void MintingView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MintingView *_t = static_cast<MintingView *>(_o);
        switch (_id) {
        case 0: _t->exportClicked(); break;
        case 1: _t->chooseMintingInterval((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MintingView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MintingView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MintingView,
      qt_meta_data_MintingView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MintingView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MintingView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MintingView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MintingView))
        return static_cast<void*>(const_cast< MintingView*>(this));
    return QWidget::qt_metacast(_clname);
}

int MintingView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
