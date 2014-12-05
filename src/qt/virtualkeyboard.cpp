#include "virtualkeyboard.h"

KeyboardKey::KeyboardKey(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}

QSize KeyboardKey::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}


VirtualKeyboard::VirtualKeyboard(QWidget *parent) :
    QWidget(parent)
{
    setHidden(true);
    setMinimumHeight(150);
    changeLayout(Lowercase);
}

VirtualKeyboard::~VirtualKeyboard() {
}

QList< QList<QString> > VirtualKeyboard::getScheme(KeyboardType type) {
    QList< QList<QString> > scheme;
    QList<QString> row1;
    QList<QString> row2;
    QList<QString> row3;
    QList<QString> row4;

    switch (type) {
        case Lowercase:
            row1 << "q" << "w" << "e" << "r" << "t" << "y" << "u" << "i" << "o" << "p";
            row2 << "a" << "s" << "d" << "f" << "g" << "h" << "j" << "k" << "l";
            row3 << "\u21E7" <<  "z" << "x" << "c" << "v" << "b" << "n" << "m" << "\u232B";
            row4 << "123?!" <<  "," <<  " " << ".";
        break;
        case Uppercase:
            row1 << "Q" << "W" << "E" << "R" << "T" << "Y" << "U" << "I" << "O" << "P";
            row2 << "A" << "S" << "D" << "F" << "G" << "H" << "J" << "K" << "L";
            row3 << "\u2B06" <<  "Z" << "X" << "C" << "V" << "B" << "N" << "M" << "\u232B";
            row4 << "123?!" <<  "," <<  " " << ".";
        break;
        case Symbols:
            row1 << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "0";
            row2 << "*" << "#" << "+" << "-" << "=" << "(" << ")" << "?" << "!";
            row3 << "\u2B06" <<  "@" << "~" << "/" << "\\" << "'" << ";" << ":" << "\u232B";
            row4 << "abc" <<  "," <<  " " << ".";
        break;
        default:
            row1 << "q" << "w" << "e" << "r" << "t" << "y" << "u" << "i" << "o" << "p";
            row2 << "a" << "s" << "d" << "f" << "g" << "h" << "j" << "k" << "l";
            row3 << "\u21E7" <<  "z" << "x" << "c" << "v" << "b" << "n" << "m" << "\u232B";
            row4 << "123?!" <<  "," <<  " " << ".";
        break;
    }

    scheme << row1 << row2 << row3 << row4;
    return scheme;
}

QVBoxLayout *VirtualKeyboard::buildKeyboard(QList< QList<QString> > scheme) {
    QVBoxLayout *board = new QVBoxLayout();
    for (int i = 0; i < scheme.size(); ++i) {
        QHBoxLayout *tmpRow = new QHBoxLayout();
        for (int k = 0; k < scheme.at(i).size(); ++k) {
            KeyboardKey *tmpKey = createKeyboardKey(scheme.at(i).at(k), SLOT(keyPressed()));
            if (scheme.at(i).at(k) == " ") {
                QSizePolicy tmpPolicy = tmpKey->sizePolicy();
                tmpPolicy.setHorizontalStretch(3);
                tmpKey->setSizePolicy(tmpPolicy);
            }
            tmpRow->addWidget(tmpKey);
        }
        board->addLayout(tmpRow);
    }
    return board;
}

KeyboardKey *VirtualKeyboard::createKeyboardKey(const QString &text, const char *member)
{
    KeyboardKey *key = new KeyboardKey(text);
    connect(key, SIGNAL(clicked()), this, member);
    return key;
}

void VirtualKeyboard::changeLayout(KeyboardType type) {
    qDeleteAll(this->children());
    QVBoxLayout *layout = buildKeyboard(getScheme(type));
    setLayout(layout);
}

void VirtualKeyboard::keyPressed() {
    KeyboardKey *pressedKey = qobject_cast<KeyboardKey *>(sender());
    QString keyValue = pressedKey->text();
    if (keyValue == "\u21E7") {
        changeLayout(Uppercase);
    } else if (keyValue == "\u2B06") {
        changeLayout(Lowercase);
    } else if (keyValue == "123?!") {
        changeLayout(Symbols);
    } else if (keyValue == "abc") {
        changeLayout(Lowercase);
    } else if (keyValue == "\u232B") {
        FocusInput->backspace();
    } else if (keyValue == "\u21B2") {
        //emit Return key press
    } else {
        FocusInput->insert(keyValue);
    }
}

void VirtualKeyboard::setInput(QObject *sender) {
    FocusInput = qobject_cast<QLineEdit *>(sender);
}

void VirtualKeyboard::toggleKeyboard() {
    if (this->isHidden()) {
        this->show();
        QRect parentGeo = this->parent()->property("geometry").toRect();
        parentGeo.setHeight(parentGeo.height() + 150);
        this->parent()->setProperty("geometry", parentGeo);
    } else {
        this->hide();
        QRect parentGeo = this->parent()->property("geometry").toRect();
        parentGeo.setHeight(parentGeo.height() - 150);
        this->parent()->setProperty("geometry", parentGeo);
    }
}
