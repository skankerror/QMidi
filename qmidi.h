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

/*! \file qmidi.h
 *  \brief enum, define, global var file
 *
 *  In this file stand all the QMidi enum, define and global variables
 */

/*! \enum QMidiApi
 *  \brief a simple wrapper for RtMidi::Api
 */
enum QMidiApi
{
  Q_UNSPECIFIED,    /*!< Search for a working compiled API. */
  Q_MACOSX_CORE,    /*!< Macintosh OS-X CoreMIDI API. */
  Q_LINUX_ALSA,     /*!< The Advanced Linux Sound Architecture API. */
  Q_UNIX_JACK,      /*!< The JACK Low-Latency MIDI Server API. */
  Q_WINDOWS_MM,     /*!< The Microsoft Multimedia MIDI API. */
  Q_RTMIDI_DUMMY,   /*!< A compilable but non-functional API. */
  Q_NUM_APIS        /*!< Number of values in this enum. */
};

/*! \enum MidiStatus
 *  \brief exhaustive midi status enum
 *
 *  This enum holds all midi status
 */
enum MidiStatus
{
  UNKNOWN = 0x00,

  // channel voice messages
  NOTE_ON = 0x90, /*!< plus 2 data bytes, pitch and velocity */
  NOTE_OFF = 0x80, /*!< plus 2 data bytes, pitch and velocity ( = 0) */
  PROG_CHANGE = 0xC0, /*!< plus 1 data byte, program ID */
  PITCH_BEND = 0xE0, /*!< plus 2 data bytes (MSB, LSB) */
  AFTERTOUCH = 0xD0, /*!< 1 data byte, pressure */
  POLY_AFTERTOUCH = 0xA0, /*!< 2 data bytes, pitch, pressure */
  CONTROL_CHANGE = 0xB0, /*!< this handles channel mode message too */

  // system real time messages
  MIDI_CLOCK = 0xF8, /*!< system real time message for sequencer */
  START = 0xFA, /*!< system real time message for sequencer */
  STOP = 0xFC, /*!< system real time message for sequencer */
  CONTINUE = 0xFB, /*!< system real time message for sequencer */
  ACTIVE_SENSING = 0xFE, /*!< system real time message for sequencer */
  SYSTEM_RESET = 0xFF, /*!< system real time message for sequencer */

  // system common messages (for slaved seq)
  MIDI_TIMING_CODE = 0xF1, /*!< system common message for slaved sequencer */
  SONG_POS_PTR = 0xF2, /*!< system common message for slaved sequencer plus 2 data bytes */
  SONG_SELECT = 0xF3, /*!< system common message for slaved sequencer plus 1 data byte */
  TUNE_REQUEST = 0xF6, /*!< system common message for slaved sequencer */

  // system exclusive messages
  SYSEX = 0xF0, /*!< system exclusive message status */
  EOX = 0xF7 /*!< end of sysex */
};

/*! \enum ChannelModeStatus
 *  \brief first byte of data for CONTROL_CHANGE status
 *
 *  if byte < 121 first byte will be controler ID and second one, value
 *  else it's channel mode message with these following status.
 */
enum ChannelModeStatus
{
  UNKNOWN_CH_MOD_MESSAGE = 0x00, /*!< null default value */
  RESET = 0x79, /*!< 2nd byte means nothing (set to 0) */
  LOCAL_CONTROL = 0x7A, /*!< 2nd byte 0 = off, 127 = on */
  ALL_NOTES_OFF = 0x7B, /*!< 2nd byte means nothing (set to 0) */
  OMNI_OFF = 0x7C, /*!< 2nd byte means nothing (set to 0) */
  OMNI_ON = 0x7D, /*!< 2nd byte means nothing (set to 0) */
  MONO_ON = 0x7E,  /*!< if 2nd byte = 0 then the number of
                    * channels used is determined by the receiver;
                    * all other values set a specific number of channels,
                    * beginning with the current basic channel.
                    */
  POLY_ON = 0x7F /*!< 2nd byte means nothing (set to 0) */
};

/*! \def LOCAL_CONTROL_ON
 *  \brief 2nd byte of data for local control channel mode status
 */
#define LOCAL_CONTROL_ON  127

/*! \def LOCAL_CONTROL_OFF
 *  \brief 2nd byte of data for local control channel mode status
 */
#define LOCAL_CONTROL_OFF  0

/*! \enum ManuID
 *  \brief Manufactor ID for sysex messages
 */
enum ManuID // for sysex
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
// TODO: replace this with a method in QMidiMessage ?
//#define MIN_BEND       0
//#define MAX_BEND       16383
//#define MIN_TIMECODE 0
//#define MAX_TIMECODE 16383

/*! \cond */
#define QUEUE_SIZE_LIMIT 1024
#define MIDI_IN_CLIENT_DEFAULT_NAME "QMidiIn Client"
#define MIDI_OUT_CLIENT_DEFAULT_NAME "QMidiOut Client"

#define DEFAULT_VELOCITY 64
// higher status byte value with channel info
#define CHANNEL_VOICE_INFORMATION_LIMIT 239
// higher control change controler id
#define CONTROL_CHANGE_CONTROLER_ID_LIMIT 120
// masks to deal with channel in byte
#define STATUS_MASK 0xF0 // 11110000 mask
#define CHANNEL_MASK 0x0F // 00001111 mask

// to have id for objects QMidiIn et QMidiOut
static int QMIDIIN_COUNT;
static int QMIDIOUT_COUNT;

// for QMidiPianoRoll
#define KEY_WIDTH 14
#define KEY_HEIGHT 60
/*! \endcond */

#endif // QMIDI_H
