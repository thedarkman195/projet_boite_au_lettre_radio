
/*
 * lcd-adafruit.c:
 *
 * Copyright (c) 2012-2013 Gordon Henderson.
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <mcp23017.h>
#include <lcd.h>
#include "lcd-adafruit.h"

/*
 * scrollMessage:
 *********************************************************************************
 */
/* VARIABLES GLOBALES*/
/* Handle du LCD-ADAFRUIT */
int lcdHandle ;
/* Contenu du message à faire défiler */
char *message;

/*
 * setBacklightColour:
 *	The colour outputs are inverted.
 *********************************************************************************
 */
void setBacklightColour (int colour)
{
  colour &= 7 ;
  digitalWrite (AF_RED,   !(colour & 1)) ;
  digitalWrite (AF_GREEN, !(colour & 2)) ;
  digitalWrite (AF_BLUE,  !(colour & 4)) ;
}

/*
 * adafruitLCDSetup:
 *	Setup the Adafruit board by making sure the additional pins are
 *	set to the correct modes, etc.
 *********************************************************************************
 */
void adafruitLCDSetup (int colour)
{
  int i ;
/*Backlight LEDs*/
  pinMode (AF_RED,   OUTPUT) ;
  pinMode (AF_GREEN, OUTPUT) ;
  pinMode (AF_BLUE,  OUTPUT) ;
  setBacklightColour (colour) ;
/*Input buttons*/
  for (i = 0 ; i <= 4 ; ++i)
  {
    pinMode (AF_BASE + i, INPUT) ;
    pullUpDnControl (AF_BASE + i, PUD_UP) ;	// Enable pull-ups, switches close to 0v
  }
/*Control signals*/
/*Not used with wiringPi - always in write mode*/
  pinMode (AF_RW, OUTPUT) ; digitalWrite (AF_RW, LOW) ;
/*The other control pins are initialised with lcdInit ()*/
  lcdHandle = lcdInit (2, 16, 4, AF_RS, AF_E, AF_DB4,AF_DB5,AF_DB6,AF_DB7, 0,0,0,0) ;
  if (lcdHandle < 0)
  {
    fprintf (stderr, "lcdInit failed\n") ;
    exit (EXIT_FAILURE) ;
  }
}

/*
 * waitForEnter:
 *	On the Adafruit display, wait for the select button
 *********************************************************************************
 */
void waitForEnter (void)
{
  printf ("Press SELECT to continue: ") ; fflush (stdout) ;
  /* Wait for push */
  while (digitalRead (AF_SELECT) == HIGH)
    delay (1) ;
    /* Wait for release */
  while (digitalRead (AF_SELECT) == LOW)
    delay (1) ;
  printf ("OK\n") ;
}

/*
 * speedTest:
 *	Test the update speed of the display
 *********************************************************************************
 */
void speedTest (void)
{
  unsigned int start, fin, taken ;
  int times ;
  lcdClear (lcdHandle) ;
  start = millis () ;
  for (times = 0 ; times < 10 ; ++times)
  {
    lcdPuts (lcdHandle, "0123456789ABCDEF") ;
    lcdPuts (lcdHandle, "0123456789ABCDEF") ;
  }
  fin   = millis () ;
  taken = (fin - start) / 10;
  lcdClear (lcdHandle) ;
  lcdPosition (lcdHandle, 0, 0) ; lcdPrintf (lcdHandle, "Speed: %dmS", taken) ;
  lcdPosition (lcdHandle, 0, 1) ; lcdPrintf (lcdHandle, "For full update") ;
  waitForEnter () ;
  lcdClear (lcdHandle) ;
  lcdPosition (lcdHandle, 0, 0) ; lcdPrintf (lcdHandle, "Time: %dmS", taken / 32) ;
  lcdPosition (lcdHandle, 0, 1) ; lcdPrintf (lcdHandle, "Per character") ;
  waitForEnter () ;
  lcdClear (lcdHandle) ;
  lcdPosition (lcdHandle, 0, 0) ; lcdPrintf (lcdHandle, "%d cps...", 32000 / taken) ;
  waitForEnter () ;
}
