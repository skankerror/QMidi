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

#include "qmidiin.h"
#include <QDebug>

QMidiIn::QMidiIn(QObject *parent,
                 RtMidi::Api t_api,
                 const QString &t_clientName,
                 unsigned int t_queueSizeLimit):
  QObject(parent),
  RtMidiIn(t_api,
           t_clientName.toStdString().c_str(),
           t_queueSizeLimit),
  m_currentID(QMIDIIN_COUNT++)
{}

QMidiIn::~QMidiIn()
{
  RtMidiIn::~RtMidiIn();
}

void QMidiIn::recieveMessage(double t_deltatime,
                             std::vector<unsigned char> *t_unMessage,
                             void *t_userData)
{
  // On caste le void* pour pouvoir le déréférencer.
  auto *aMidiIn = static_cast<QMidiIn*>(t_userData);

  auto aMessage = new QMidiMessage(aMidiIn);
  aMessage->setRawMessage(t_unMessage);
  aMessage->setDeltaTime(t_deltatime);

  emit aMidiIn->sigRecieveMessage(*aMessage);

}

int QMidiIn::portCount()
{
  return getPortCount();
}

QStringList QMidiIn::portNames()
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

void QMidiIn::connectMidiIn(int t_portNumber)
{
  if (RtMidiIn::isPortOpen())
    disconnectMidiIn();

  RtMidiIn::openPort(t_portNumber);

  if (RtMidiIn::isPortOpen())
  {
    m_isPortOpen = true;
    RtMidiIn::setCallback(&recieveMessage, this);
  }
  else qDebug() << "Midi in " << m_currentID << " not opened";

}

void QMidiIn::disconnectMidiIn()
{
  if (RtMidiIn::isPortOpen())
  {
    m_isPortOpen = false;
    RtMidiIn::closePort();
    RtMidiIn::cancelCallback();
  }
  else qDebug() << "Port in was not opened...";
}

