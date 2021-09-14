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

#ifndef QMIDI_H
#define QMIDI_H

enum MidiStatus
{
  UNKNOWN = 0x00, // risque de passer pour un byte data...

  // channel voice messages
  NOTE_ON = 0x90,
  NOTE_OFF = 0x80,
  PROG_CHANGE = 0xC0,
  PITCH_BEND = 0xE0,
  AFTERTOUCH = 0xD0,
  POLY_AFTERTOUCH = 0xA0,
  CONTROL_CHANGE = 0xB0, // prend aussi les channel modes messages

  // system real time messages
  MIDI_CLOCK = 0xF8,
  START = 0xFA,
  STOP = 0xFC,
  CONTINUE = 0xFB,
  ACTIVE_SENSING = 0xFE,
  SYSTEM_RESET = 0xFF,

  // system common messages (pour seq asservis)
  SONG_POS_PTR = 0xF2,
  SONG_SELECT = 0xF3,
  TUNE_REQUEST = 0xF6,

  // system exclusive messages
  SYSEX = 0xF0,
  EOX = 0xF7
};

enum ManuID // pour sysex
{
  SEQUENTIAL_CIRCUITS = 0x01,
  BIG_BRIAR = 0x02,
  OCTAVE_PLATEAU = 0x03,
  MOOG = 0x04,
  PASSPORT_DESIGNS = 0x05,
  LEXICON = 0x06,
  KURZWEIL = 0x07,
  FENDER = 0x08,
  GULBRANSEN = 0x09,
  DELTA_LABS = 0x0A,
  SOUND_COMP = 0x0B,
  GENERAL_ELECTRO = 0x0C,
  TECHMAR = 0x0D,
  MATTHEWS_RESEARCH = 0x0E,
  OBERHEIM = 0x10,
  PAIA = 0x11,
  SIMMONS = 0x12,
  DIGIDESIGN = 0x13,
  FAIRLIGHT = 0x14,
  PEAVEY = 0x1B,
  JL_COOPER = 0x15,
  LOWERY = 0x16,
  LIN = 0x17,
  EMU = 0x18,
  BONTEMPI = 0x20,
  SIEL = 0x21,
  SYNTHEAXE = 0x23,
  HOHNER = 0x24,
  CRUMAR = 0x25,
  SOLTON = 0x26,
  JELLINGHAUS_MS = 0x27,
  CTS = 0x28,
  PPG = 0x29,
  ELKA = 0x2F,
  CHEETAH = 0x36,
  KAWAI = 0x40,
  ROLAND = 0x41,
  KORG = 0x42,
  YAMAHA = 0x43,
  CASIO = 0x44,
  AKAI = 0x45
};

// number range defines
// because it's sometimes hard to remember these  ...
#define MIN_BEND       0
#define MAX_BEND       16383
#define MIN_TIMECODE 0
#define MAX_TIMECODE 16383


#define QUEUE_SIZE_LIMIT 100



#endif // QMIDI_H
