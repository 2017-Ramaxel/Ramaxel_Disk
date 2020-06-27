/****************************************************************************
** Meta object code from reading C++ file 'buttongroup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "buttongroup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buttongroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ButtonGroup_t {
    QByteArrayData data[11];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ButtonGroup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ButtonGroup_t qt_meta_stringdata_ButtonGroup = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ButtonGroup"
QT_MOC_LITERAL(1, 12, 9), // "sigMyFile"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "sigShareList"
QT_MOC_LITERAL(4, 36, 11), // "sigDownload"
QT_MOC_LITERAL(5, 48, 12), // "sigTransform"
QT_MOC_LITERAL(6, 61, 13), // "sigSwitchUser"
QT_MOC_LITERAL(7, 75, 15), // "slotButtonClick"
QT_MOC_LITERAL(8, 91, 4), // "Page"
QT_MOC_LITERAL(9, 96, 3), // "cur"
QT_MOC_LITERAL(10, 100, 4) // "text"

    },
    "ButtonGroup\0sigMyFile\0\0sigShareList\0"
    "sigDownload\0sigTransform\0sigSwitchUser\0"
    "slotButtonClick\0Page\0cur\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ButtonGroup[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,
       6,    0,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   54,    2, 0x0a /* Public */,
       7,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void ButtonGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ButtonGroup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigMyFile(); break;
        case 1: _t->sigShareList(); break;
        case 2: _t->sigDownload(); break;
        case 3: _t->sigTransform(); break;
        case 4: _t->sigSwitchUser(); break;
        case 5: _t->slotButtonClick((*reinterpret_cast< Page(*)>(_a[1]))); break;
        case 6: _t->slotButtonClick((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ButtonGroup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ButtonGroup::sigMyFile)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ButtonGroup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ButtonGroup::sigShareList)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ButtonGroup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ButtonGroup::sigDownload)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ButtonGroup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ButtonGroup::sigTransform)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ButtonGroup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ButtonGroup::sigSwitchUser)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ButtonGroup::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ButtonGroup.data,
    qt_meta_data_ButtonGroup,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ButtonGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ButtonGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ButtonGroup.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ButtonGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ButtonGroup::sigMyFile()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ButtonGroup::sigShareList()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ButtonGroup::sigDownload()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ButtonGroup::sigTransform()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ButtonGroup::sigSwitchUser()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
