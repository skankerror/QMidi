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

#ifndef QMIDIOUT_H
#define QMIDIOUT_H

#include <QObject>
#include <QStringList>
#include "RtMidi/RtMidi.h"
#include "qmidi.h"
#include "qmidimessage.h"


class QMidiOut :
    public QObject,
    private RtMidiOut
{

  Q_OBJECT

public:

  QMidiOut(QObject *parent = nullptr,
           RtMidi::Api t_api = UNSPECIFIED,
           const QString &t_clientName = "QMidiOut client");

  ~QMidiOut();

  int portCount();
  QStringList portNames();
  bool isPortOpen(){ return m_isPortOpen; };

  // send unknown messages
  void sendQMidiMessage(QMidiMessage *t_message);
  void sendRawMessage(std::vector<unsigned char> *t_rawMessage);

  // send Channel Voice messages
  void sendNoteOn(unsigned int t_channel,
                  unsigned int t_pitch,
                  unsigned int t_velocity = 64);
  void sendNoteOff(unsigned int t_channel,
                   unsigned int t_pitch,
                   unsigned int t_velocity = 0);
  void sendProgChange(unsigned int t_channel,
                      unsigned int t_progID);
  void sendPitchBend(unsigned int t_channel,
                     QPair<unsigned int, unsigned int> t_pitchBend);
  void sendAftertouch(unsigned int t_channel,
                      unsigned int t_pitch,
                      unsigned int t_pressure);
  void sendPolyAftertouch(unsigned int t_channel,
                          unsigned int t_pressure);
  // TODO: implement Channel mode messages
  void sendControlChange(unsigned int t_channel,
                         unsigned int t_control,
                         unsigned int t_value);

  // send System real time messages
  void sendMidiClock();
  void sendStart();
  void sendStop();
  void sendContinue();
  void sendActiveSensing();
  void sendSystemReset();

  // send system common messages
  void sendSongPosPointer(QPair<unsigned int, unsigned int> t_songPos);
  void sendSongSelect(unsigned int t_seqID);
  void sendTuneRequest();

  // send system exclusive messages
  void sendSysEx(std::vector<unsigned char> *t_sysExData);



public slots:

  void connectMidiOut(int t_portNumber);
  void disconnectMidiOut();

private:

  const int m_currentID;

  bool m_isPortOpen;

};

#endif // QMIDIOUT_H
