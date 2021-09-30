#include "qmidiconnectwidget.h"
#include <QVBoxLayout>


QMidiConnectInWidget::QMidiConnectInWidget(QMidiIn *t_midiIn,
                                           QWidget *parent) :
  QWidget(parent),
  m_midiIn(t_midiIn)
{
  auto layout = new QVBoxLayout();
}

QMidiConnectOutWidget::QMidiConnectOutWidget(QMidiOut *t_midiOut,
                                             QWidget *parent) :
  QWidget(parent),
  m_midiOut(t_midiOut)
{
  auto layout = new QVBoxLayout();
}
