#ifndef QABSTRACTMIDICONTROLERWIDGET_H
#define QABSTRACTMIDICONTROLERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVector>

class QAbstractMidiControlerWidget :
    public QWidget
{

  Q_OBJECT

public:

  explicit QAbstractMidiControlerWidget(QWidget *parent = nullptr);

signals:

protected:

  QVector<QPushButton *> m_v_pushButtons;
};

#endif // QABSTRACTMIDICONTROLERWIDGET_H
