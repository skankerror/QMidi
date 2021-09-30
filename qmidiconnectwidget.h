#ifndef QMIDICONNECTWIDGET_H
#define QMIDICONNECTWIDGET_H

#include <QWidget>
#include "qmidiin.h"
#include "qmidiout.h"


class QMidiConnectInWidget :
    public QWidget
{

  Q_OBJECT

public :

  explicit QMidiConnectInWidget(QMidiIn *t_midiIn,
                                QWidget *parent = nullptr);

signals :

private :

  QMidiIn *m_midiIn;
};



class QMidiConnectOutWidget :
    public QWidget
{

  Q_OBJECT

public :

  explicit QMidiConnectOutWidget(QWidget *parent = nullptr);

signals :

private :

  QMidiOut *m_midiOut;

};

#endif // QMIDICONNECTWIDGET_H
