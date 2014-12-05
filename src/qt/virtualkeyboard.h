#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>
#include <QLineEdit>

class KeyboardKey : public QToolButton
{
    Q_OBJECT

public:
    KeyboardKey(const QString &text, QWidget *parent = 0);

    QSize sizeHint() const;
};

class VirtualKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit VirtualKeyboard(QWidget *parent = 0);
    ~VirtualKeyboard();

    enum KeyboardType {
        Lowercase = 0,
        Uppercase = 1,
        Symbols = 2
    };

    QLineEdit *FocusInput;

private:
    QList< QList<QString> > getScheme(KeyboardType type);
    QVBoxLayout *buildKeyboard(QList< QList<QString> > scheme);
    KeyboardKey *createKeyboardKey(const QString &text, const char *member);
    void changeLayout(KeyboardType type);

private slots:
    void keyPressed();

public slots:
    void setInput(QObject *sender);
    void toggleKeyboard();

};

#endif // VIRTUALKEYBOARD_H
