/*
 * Author: Yevgeniy Kiveisha <yevgeniy.kiveisha@intel.com>
 * Copyright (c) 2014 Intel Corporation.
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

#include <string.h>
#include <unistd.h>
#include <iostream>
#include "step_motor.h"
#include <signal.h>

int doWork = 0;
upm::StepMotor *sensor = NULL;

void
sig_handler(int signo)
{
    printf("got signal\n");
    if (signo == SIGINT) {
        printf("exiting application\n");
        doWork = 1;
    }
}

int
main(int argc, char **argv)
{
//! [Interesting]
    sensor = new upm::StepMotor(4, 6);

    while (!doWork) {
        sensor->setSpeed (500);
        sensor->stepForward (500);
        usleep (10000);
        sensor->stepBackwards (500);
        usleep (10000);

        sensor->setSpeed (750);
        sensor->stepForward (500);
        usleep (10000);
        sensor->stepBackwards (500);
        usleep (10000);

        sensor->setSpeed (1000);
        sensor->stepForward (500);
        usleep (10000);
        sensor->stepBackwards (500);
        usleep (10000);
    }

    delete sensor;
//! [Interesting]
    return 0;
}