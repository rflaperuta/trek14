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

void outchar(char c);
void outcharat(uchar x, uchar y, uchar c);
char getkey();
void setcursor(uchar x, uchar y);
void cls();
void setWide(uchar v);
void initModel();
void uninitModel();
void pause();

void outs(const char* s);
void outsWide(const char* s);
uchar getline2(char* buf, uchar nmax);
void lastLine();
uchar* vidaddr(uchar x, uchar y);
uchar ramTest(uchar a, uchar n);

typedef void (*IdleHandler)(uchar);
void setIdleHandler(IdleHandler h, uchar d);

extern uchar TRSModel;
extern uchar TRSMemory;
extern uchar* TRSMemoryFail;
extern uchar cols80;


