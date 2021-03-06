/*
 * Author: Jon Trulson <jtrulson@ics.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>

#include "dfrph.h"

using namespace std;
using namespace upm;

DFRPH::DFRPH(int pin, float aref) :
  m_aio(pin)
{
  m_aRes = (1 << m_aio.getBit());
  m_aref = aref;

  m_offset = 0.0;
}

DFRPH::~DFRPH()
{
}

float DFRPH::volts()
{
  int val = m_aio.read();

  return(val * (m_aref / m_aRes));
}

void DFRPH::setOffset(float offset)
{
  m_offset = offset;
}

float DFRPH::pH(unsigned int samples)
{
  if (!samples)
    samples = 1;

  float sum = 0.0;

  for (int i=0; i<samples; i++)
    {
      sum += volts();
      usleep(20000);
    }

  sum /= samples;

  // 3.5 is a 'magic' DFRobot number. Seems to work though :)
  return (3.5 * sum + m_offset);
}
