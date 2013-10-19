#ifndef TOUCHDRAGWIDGET_H
#define TOUCHDRAGWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>

class TouchDragWidget : public QWidget
{
    Q_OBJECT

public:
    TouchDragWidget();

protected:
    virtual bool event(QEvent *);
    virtual void mousePressEvent(QMouseEvent *);

    virtual void dragEnterEvent(QDragEnterEvent *);
    virtual void dragMoveEvent(QDragMoveEvent *);
    virtual void dragLeaveEvent(QDragLeaveEvent *);
    virtual void dropEvent(QDropEvent *dropEvent);

private:
    QLineEdit *mDropIndicator;
};

#endif // TOUCHDRAGWIDGET_H
