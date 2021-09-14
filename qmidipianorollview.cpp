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

#include "qmidipianorollview.h"
#include <QPainter>
#include <QGraphicsRectItem>

QMidiPianoRollView::QMidiPianoRollView(QWidget *parent) :
  QGraphicsView(parent),
  m_scene(new QGraphicsScene()),
  m_keyWidth(10),
  m_keyHeight(60)
{
  float x = 0;
  for(int i = 0; i < 128; i++)
  {
    int position = i % 12;
    QGraphicsRectItem *rect;
    if(position == 0 || position == 2 || position == 4 || position == 5 || position == 7 || position == 9 || position == 11)
    {
      rect = new QGraphicsRectItem(x,0,m_keyWidth,m_keyHeight);
      m_scene->addItem(rect);
      if(position != 4 && position != 11 )
      {
        x += m_keyWidth/2+1;
      }
      else
      {
        x += m_keyWidth+1;
      }
    }
    else
    {
      rect = new QGraphicsRectItem(x,0,m_keyWidth,m_keyHeight/2);
      rect->setZValue(2);
      QBrush brush;
      QPen pen;
      brush.setStyle(Qt::SolidPattern);
      pen.setColor(Qt::black);
      brush.setColor(Qt::black);
      rect->setBrush(brush);
      rect->setPen(pen);
      m_scene->addItem(rect);
      x += m_keyWidth/2+1;
    }
    m_keys.push_back(rect);

  }

  setScene(m_scene);
}

bool QMidiPianoRollView::isSemiTone(int pitch)
{
  int position = pitch %12;
  if(position == 0 || position == 2 || position == 4 || position == 5 || position == 7 || position == 9 || position == 11)
  {
    return false;
  }
  else
  {
    return true;
  }

}

//void QMidiPianoRoll::paintEvent(QPaintEvent *event)
//{
////    QPainter painter(this);
//}

void QMidiPianoRollView::onMidiReceive(QMidiMessage *message)
{
  switch(message->status())
  {
  case NOTE_ON: {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0,0,200, message->velocity()*2));
    m_keys[message->pitch()]->setBrush(brush);
    break;
  }
  case NOTE_OFF: {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    QColor color;
    if(isSemiTone(message->pitch()))
    {
      color = QColor(Qt::black);
    }
    else
    {
      color = QColor(Qt::white);
    }
    brush.setColor(color);
    m_keys[message->pitch()]->setBrush(brush);
    break;
  }
  default: break;
  }
}
