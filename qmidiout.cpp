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

#include "qmidiout.h"
#include <QDebug>

QMidiOut::QMidiOut(QObject *parent,
                   RtMidi::Api t_api,
                   const QString &t_clientName) :
  QObject(parent),
  RtMidiOut(t_api, t_clientName.toStdString().c_str()),
  m_currentID(QMIDIOUT_COUNT++)
{}

QMidiOut::~QMidiOut()
{
  RtMidiOut::~RtMidiOut();
}

int QMidiOut::portCount()
{
  return getPortCount();
}

QStringList QMidiOut::portNames()
{
  int aPortCount = portCount();
  QStringList stringList;
  for(int i = 0; i < aPortCount; i++)
  {
    QString string = QString::fromStdString(getPortName(i));
    stringList.append(string);
  }
  return stringList;
}

void QMidiOut::sendQMidiMessage(QMidiMessage *t_message)
{
  sendRawMessage(t_message->rawMessage());
}

void QMidiOut::sendRawMessage(std::vector<unsigned char> *t_rawMessage)
{
  RtMidiOut::sendMessage(t_rawMessage);
}

void QMidiOut::sendNoteOn(unsigned int t_channel,
                          unsigned int t_pitch,
                          unsigned int t_velocity)
{
  // must check before
  auto message = new QMidiMessage(this);
  message->setStatus(NOTE_ON);
  message->setChannel(t_channel);
  message->setPitch(t_pitch);
  message->setVelocity(t_velocity);
  sendQMidiMessage(message);
}

void QMidiOut::sendNoteOff(unsigned int t_channel,
                           unsigned int t_pitch,
                           unsigned int t_velocity)
{
  // must check before
  auto message = new QMidiMessage(this);
  message->setStatus(NOTE_OFF);
  message->setChannel(t_channel);
  message->setPitch(t_pitch);
  message->setVelocity(t_velocity);
  sendQMidiMessage(message);
}

void QMidiOut::sendProgChange(unsigned int t_channel,
                              unsigned int t_progID)
{
  auto message = new QMidiMessage(this);
  message->setStatus(PROG_CHANGE);
  message->setChannel(t_channel);
  message->setProgID(t_progID);
  sendQMidiMessage(message);
}

void QMidiOut::sendPitchBend(unsigned int t_channel,
                             QPair<unsigned int, unsigned int> t_pitchBend)
{
  auto message = new QMidiMessage(this);
  message->setStatus(PITCH_BEND);
  message->setChannel(t_channel);
  message->setPitchBend(t_pitchBend);
  sendQMidiMessage(message);
}

void QMidiOut::sendAftertouch(unsigned int t_channel,
                              unsigned int t_pitch,
                              unsigned int t_pressure)
{
  auto message = new QMidiMessage(this);
  message->setStatus(AFTERTOUCH);
  message->setChannel(t_channel);
  message->setPitch(t_pitch);
  message->setPressure(t_pressure);
  sendQMidiMessage(message);
}

void QMidiOut::sendPolyAftertouch(unsigned int t_channel,
                                  unsigned int t_pressure)
{
  auto message = new QMidiMessage(this);
  message->setStatus(POLY_AFTERTOUCH);
  message->setChannel(t_channel);
  message->setPressure(t_pressure);
  sendQMidiMessage(message);
}

void QMidiOut::sendControlChange(unsigned int t_channel,
                                 unsigned int t_control,
                                 unsigned int t_value)
{
  auto message = new QMidiMessage(this);
  message->setStatus(CONTROL_CHANGE);
  message->setChannel(t_channel);
  message->setControl(t_control);
  message->setValue(t_value);
  sendQMidiMessage(message);
}

void QMidiOut::sendMidiClock()
{
  auto message = new QMidiMessage(this);
  message->setStatus(MIDI_CLOCK);
  sendQMidiMessage(message);
}

void QMidiOut::sendStart()
{
  auto message = new QMidiMessage(this);
  message->setStatus(START);
  sendQMidiMessage(message);
}

void QMidiOut::sendStop()
{
  auto message = new QMidiMessage(this);
  message->setStatus(STOP);
  sendQMidiMessage(message);
}

void QMidiOut::sendContinue()
{
  auto message = new QMidiMessage(this);
  message->setStatus(CONTINUE);
  sendQMidiMessage(message);
}

void QMidiOut::sendActiveSensing()
{
  auto message = new QMidiMessage(this);
  message->setStatus(ACTIVE_SENSING);
  sendQMidiMessage(message);
}

void QMidiOut::sendSystemReset()
{
  auto message = new QMidiMessage(this);
  message->setStatus(SYSTEM_RESET);
  sendQMidiMessage(message);
}

void QMidiOut::sendSongPosPointer(QPair<unsigned int, unsigned int> t_songPos)
{
  auto message = new QMidiMessage(this);
  message->setStatus(SONG_POS_PTR);
  message->setSongPos(t_songPos);
  sendQMidiMessage(message);
}

void QMidiOut::sendSongSelect(unsigned int t_seqID)
{
  auto message = new QMidiMessage(this);
  message->setStatus(SONG_SELECT);
  message->setSeqID(t_seqID);
  sendQMidiMessage(message);
}

void QMidiOut::sendTuneRequest()
{
  auto message = new QMidiMessage(this);
  message->setStatus(TUNE_REQUEST);
  sendQMidiMessage(message);
}

void QMidiOut::sendSysEx(std::vector<unsigned char> *t_sysExData)
{
  auto message = new QMidiMessage(this);
  message->setStatus(SYSEX);
  message->setSysExData(t_sysExData);
  sendQMidiMessage(message);
}


void QMidiOut::connectMidiOut(int t_portNumber)
{
  if (RtMidiOut::isPortOpen())
    disconnectMidiOut();

  RtMidiOut::openPort(t_portNumber);

  if (RtMidiOut::isPortOpen())
  {
    m_isPortOpen = true;
  }
  else qDebug() << "Midi out " << m_currentID << " not opened";


}

void QMidiOut::disconnectMidiOut()
{
  if (RtMidiOut::isPortOpen())
  {
    m_isPortOpen = false;
    RtMidiOut::closePort();
  }
  else qDebug() << "Port out was not opened...";


}
