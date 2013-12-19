/**
 * Copyright (c) 2013 Voidware Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "defs.h"
#include "os.h"

// ---- OS FUNCTIONS -----------------------------------------------------

void outchar(char c)
{
    // print `c' at current cursor position
    // uses AF, DE, IY

    __asm
    ld	iy,#2
    add	iy,sp
    ld	a,0(iy)
    call #0x33
    __endasm;
}

char inkey()
{
    // uses AF, DE
    __asm
     call #0x2b
     ld l,a
    __endasm;
}

char getkey()
{
    // wait for a key
    // uses AF, DE
    __asm
     call #0x49
     ld l,a
    __endasm;
}

uchar getline(char* buf, uchar nmax)
{
    // get whole line
    // uses AF, DE
    // return number of chars including terminator
    
    __asm
     pop bc
     pop hl
     push hl
     push bc
     ld iy,#4
     add iy,sp
     ld b,0(iy)
     call #0x40
     ld l,b
    __endasm;
}

void setCursor(uchar x, uchar y)
{
    // 0x4020
    int* p = (int*)0x4020;
    int v = (y<<6) + x + (int)VIDRAM;
    *p = v;
}

void cls()
{
    // uses AF
    __asm
    call #0x1c9
    __endasm;
}


// ---- LIB FUNCTIONS -----------------------------------------------------

void outs(const char* s)
{
    while (*s)
        outchar(*s++);
}

void memset(uchar* p, uchar v, unsigned int n)
{
    while (n)
    {
        --n;
        *p++ = v;
    }
}
