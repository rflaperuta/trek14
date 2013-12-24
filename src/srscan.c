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

// quadrant view

#include "defs.h"
#include "os.h"
#include "libc.h"
#include "utils.h"
#include "ent.h"
#include "plot.h"
#include "srscan.h"
#include "enemy.h"
#include "command.h"

static void fillbg(uchar x, uchar y)
{
    outcharat(x, y, (x & 1) ? ' ' : '.');
}

void moveEnt(uchar* ep, char dx, char dy)
{
    uchar sx, sy;
    ENT_SXY(ep, sx, sy);
    if (!setSector(ep, sx+dx, sy+dy))
    {
        uchar x, y;
        const EntObj* obj = objTable + ENT_TYPE(ep);
        uchar w2 = obj->_w;
        sx -= w2>>1;
            
        if (dy)
        {
            drawRLE((sx+dx)<<1, (sy + dy)*3, obj->_data, 1);
            while (w2)
            {
                --w2;
                fillbg(sx++, sy);
            }
        }
        else if (dx)
        {
            x = sx<<1;
            y = sy*3;
            moveRLE(x, y, obj->_data, (dx < 0));            
            moveRLE(x+dx, y, obj->_data, (dx < 0));            
            if (dx < 0)
                fillbg(sx + w2 - 1, sy);                
            else
                fillbg(sx, sy);
        }
    }
}

char srScan()
{
    uchar** epp;
    int i;
    char c;
    uchar sx, sy;
    
    cls();
    printf("Short Range Scan, Quadrant %d %d %d\n", (int)QX, (int)QY, (int)QZ);

    for (i = 64*7; i > 0; --i) { outchar('.'); outchar(' '); }

    // use the current quadrant info

    epp = quadrant;
    while (*epp)
    {
        const EntObj* eo = objTable + ENT_TYPE(*epp);
        ENT_SXY(*epp, sx, sy);

        // convert sector position to pixel
        drawRLE((sx - (eo->_w>>1))<<1, sy*3, eo->_data, 1);

        ++epp;
    }    

    for (;;)
    {
        char dx, dy;
        
        c = inkey();
        if (!c) continue;

        dx = 0;
        dy = 0;
        if (c == KEY_ARROW_LEFT)
            dx = -1;
        else if (c == KEY_ARROW_RIGHT)
            dx = 1;
        else if (c == KEY_ARROW_UP)
            dy = -1;
        else if (c == KEY_ARROW_DOWN)
            dy = 1;
        else if (c == ' ')
        {
            // dummy move!
        }
        else break;

        moveEnt(galaxyEnd - ENT_SIZE, dx, dy);
        enemyMove();
    }

    return c;
}
