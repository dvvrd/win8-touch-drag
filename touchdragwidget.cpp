#include "touchdragwidget.h"

#include <QtCore/QDebug>
#include <QtCore/QMimeData>
#include <QtGui/QtEvents>
#include <QtGui/QDrag>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

TouchDragWidget::TouchDragWidget()
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    setAcceptDrops(true);


    QLabel *help = new QLabel("Drag and drop any where in the grey area under the textbox below");
    mDropIndicator = new QLineEdit;
    mDropIndicator->setReadOnly(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(help);
    layout->addWidget(mDropIndicator);
    layout->addStretch();
    setLayout(layout);
}

bool TouchDragWidget::event(QEvent *event)
{
    QTouchEvent *touchEvent = dynamic_cast<QTouchEvent *>(event);
    if (!touchEvent || touchEvent->touchPoints().count() != 1) {
        return QWidget::event(event);
    }

    QPoint const pos(touchEvent->touchPoints()[0].pos().toPoint());

    switch(event->type()) {
    case QEvent::TouchBegin: {
        qDebug() << "touch begin";
        QMouseEvent* mouseEvent = new QMouseEvent(QEvent::MouseButtonPress, pos
                , Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::postEvent(touchEvent->target(), mouseEvent);
        break;
    }
    case QEvent::TouchEnd: {
        qDebug() << "touch end";
        QMouseEvent* mouseEvent = new QMouseEvent(QEvent::MouseButtonRelease, pos
                , Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
        QApplication::postEvent(touchEvent->target(), mouseEvent);
        break;
    }
    case QEvent::TouchUpdate: {
        QCursor::setPos(mapToGlobal(pos));
        break;
    }
    default:
        break;
    }

    event->accept();
    return true;
}

void TouchDragWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent)
    mDropIndicator->setText("");
    // Without this line drop indicator doesn`t have time to redraw itself
    mDropIndicator->repaint();

    QDrag *drag = new QDrag(this);
    drag->setMimeData(new QMimeData());

    qDebug() << "before drag";
    // Next line hangs app out till the first mouse event.
    // In my opinion it happens because of the entering the separate event loop
    // in qdnd_p.h (QDragManager). This event loop filters and processes all app events
    // but for some reason on Windows 8 touch end event is not processed by that event loop
    drag->exec(Qt::CopyAction);
    qDebug() << "after drag";
}

void TouchDragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void TouchDragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

void TouchDragWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void TouchDragWidget::dropEvent(QDropEvent *dropEvent)
{
    Q_UNUSED(dropEvent)
    mDropIndicator->setText("dropped!");
}
