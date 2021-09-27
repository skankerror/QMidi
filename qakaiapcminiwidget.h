#ifndef QAKAIAPCMINIWIDGET_H
#define QAKAIAPCMINIWIDGET_H

#include "qabstractmidicontrolerwidget.h"

class QAkaiAPCMiniWidget :
    public QAbstractMidiControlerWidget
{

  Q_OBJECT

public:

  explicit QAkaiAPCMiniWidget(QWidget *parent = nullptr);

};

#endif // QAKAIAPCMINIWIDGET_H
