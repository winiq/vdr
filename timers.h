/*
 * timers.h: Timer handling
 *
 * See the main source file 'vdr.c' for copyright information and
 * how to reach the author.
 *
 * $Id: timers.h 1.8 2004/10/24 14:40:37 kls Exp $
 */

#ifndef __TIMERS_H
#define __TIMERS_H

#include "channels.h"
#include "config.h"
#include "epg.h"
#include "tools.h"

enum eTimerFlags { tfNone      = 0x0000,
                   tfActive    = 0x0001,
                   tfInstant   = 0x0002,
                   tfVps       = 0x0004,
                   tfAll       = 0xFFFF,
                 };
enum eTimerMatch { tmNone, tmPartial, tmFull };

class cTimer : public cListObject {
  friend class cMenuEditTimer;
private:
  time_t startTime, stopTime;
  static char *buffer;
  bool recording, pending, inVpsMargin;
  int flags;
  cChannel *channel;
  int day;
  int start;
  int stop;
  int priority;
  int lifetime;
  char file[MaxFileName];
  time_t firstday;
  char *summary;
  const cEvent *event;
public:
  cTimer(bool Instant = false, bool Pause = false);
  cTimer(const cEvent *Event);
  virtual ~cTimer();
  cTimer& operator= (const cTimer &Timer);
  virtual bool operator< (const cListObject &ListObject);
  bool Recording(void) { return recording; }
  bool Pending(void) { return pending; }
  bool InVpsMargin(void) { return inVpsMargin; }
  int Flags(void) { return flags; }
  const cChannel *Channel(void) { return channel; }
  int Day(void) { return day; }
  int Start(void) { return start; }
  int Stop(void) { return stop; }
  int Priority(void) { return priority; }
  int Lifetime(void) { return lifetime; }
  const char *File(void) { return file; }
  time_t FirstDay(void) { return firstday; }
  const char *Summary(void) { return summary; }
  const char *ToText(bool UseChannelID = false);
  const cEvent *Event(void) { return event; }
  bool Parse(const char *s);
  bool Save(FILE *f);
  bool IsSingleEvent(void);
  int GetMDay(time_t t);
  int GetWDay(time_t t);
  bool DayMatches(time_t t);
  static time_t IncDay(time_t t, int Days);
  static time_t SetTime(time_t t, int SecondsFromMidnight);
  char *SetFile(const char *File);
  bool Matches(time_t t = 0, bool Directly = false);
  int Matches(const cEvent *Event);
  time_t StartTime(void);
  time_t StopTime(void);
  void SetEvent(const cEvent *Event);
  void SetRecording(bool Recording);
  void SetPending(bool Pending);
  void SetInVpsMargin(bool InVpsMargin);
  void SetFlags(int Flags);
  void ClrFlags(int Flags);
  void InvFlags(int Flags);
  bool HasFlags(int Flags);
  void Skip(void);
  void OnOff(void);
  const char *PrintFirstDay(void);
  static int TimeToInt(int t);
  static int ParseDay(const char *s, time_t *FirstDay = NULL);
  static const char *PrintDay(int d, time_t FirstDay = 0);
  };

class cTimers : public cConfig<cTimer> {
private:
  int beingEdited;
  time_t lastSetEvents;
public:
  cTimers(void);
  cTimer *GetTimer(cTimer *Timer);
  cTimer *GetMatch(time_t t);
  cTimer *GetMatch(const cEvent *Event, int *Match = NULL);
  cTimer *GetNextActiveTimer(void);
  int BeingEdited(void) { return beingEdited; }
  void IncBeingEdited(void) { beingEdited++; }
  void DecBeingEdited(void) { if (!--beingEdited) lastSetEvents = 0; }
  void SetEvents(void);
  };

extern cTimers Timers;

#endif //__TIMERS_H
