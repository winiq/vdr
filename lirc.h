/*
 * lirc.h: LIRC remote control
 *
 * See the main source file 'vdr.c' for copyright information and
 * how to reach the author.
 *
 * $Id: lirc.h 1.1 2002/09/28 14:11:04 kls Exp $
 */

#ifndef __LIRC_H
#define __LIRC_H

#include "remote.h"
#include "thread.h"

class cLircRemote : public cRemote, private cThread {
private:
  enum { LIRC_KEY_BUF = 30, LIRC_BUFFER_SIZE = 128 };
  int f;
  virtual void Action(void);
public:
  cLircRemote(char *DeviceName);
  virtual ~cLircRemote();
  };

#endif //__LIRC_H
