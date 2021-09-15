/*
 * (c) 2021 Michaël Creusy -- creusy(.)michael(@)gmail(.)com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QMIDIIN_H
#define QMIDIIN_H

#include <QObject>
#include <QStringList>
#include "RtMidi/RtMidi.h"
#include "qmidi.h"
#include "qmidimessage.h"


class QMidiIn :
    public QObject,
    private RtMidiIn
{

  Q_OBJECT

public:

  QMidiIn(QObject *parent = nullptr,
          RtMidi::Api t_api = UNSPECIFIED,
          const QString &t_clientName = "QMidiIn client",
          unsigned int t_queueSizeLimit = QUEUE_SIZE_LIMIT);

  ~QMidiIn();

  // static method for rtmidiin callback fonction.
  // it's static but can access to method of instancied objects.
  // we'll send 'this' ptr as last arg, so it can emit signal on object
  static void recieveMessage(double t_deltatime,
                            std::vector<unsigned char> *t_unMessage,
                            void *t_userData); // TODO: make it private ?

  int portCount();
  QStringList portNames();


signals:

  void sigRecieveMessage(QMidiMessage);

public slots:

  void connectMidiIn(int t_portNumber);
  void disconnectMidiIn();

private:

  const int m_currentID;

  bool m_isPortOpen;
  bool m_ignoreSysex;
  bool m_ignoreTime;
  bool m_ignoreSense;

};

#endif // QMIDIIN_H
