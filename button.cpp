#include "button.h"

button::button(const QString &text, QWidget *parent) : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);

    QFont buttonFont = font();
    buttonFont.setPointSize(buttonFont.pointSize() + 6);
    setFont(buttonFont);
}

QSize button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 30;
    size.rwidth() = qMax(size.width(), size.height());

    return size;
}

