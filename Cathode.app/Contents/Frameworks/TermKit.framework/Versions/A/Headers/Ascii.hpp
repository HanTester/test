//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_ASCII_HPP
#define TERMKIT_ASCII_HPP

//
// Names for all ASCII control characters.
// Everything less than 32 (space) is a "control character."
//

//          Name    Value       Hex     Char    Description
//=============================================================
                            
#define     NUL     0       //  0x00    '\0'    NULL
#define     SOH     1       //  0x01    -       -
#define     STX     2       //  0x02    -       -
#define     ETX     3       //  0x03    -       -
#define     EOT     4       //  0x04    -       -
#define     ENQ     5       //  0x05    -       -
#define     ACK     6       //  0x06    -       Acknowledge
#define     BEL     7       //  0x07    '\a'    Bell
#define     BS      8       //  0x08    '\b'    Backspace
#define     HT      9       //  0x09    '\t'    Horizontal Tab
#define     NL      10      //  0x0a    '\n'    New Line
#define     VT      11      //  0x0b    -       Vertical Tab
#define     NP      12      //  0x0c    '\f'    Form Feed
#define     CR      13      //  0x0d    '\r'    Carriage Return
#define     SO      14      //  0x0e    -       -
#define     SI      15      //  0x0f    -       -
#define     DLE     16      //  0x10    -       -
#define     DC1     17      //  0x11    -       -
#define     DC2     18      //  0x12    -       -
#define     DC3     19      //  0x13    -       -
#define     DC4     20      //  0x14    -       -
#define     NAK     21      //  0x15    -       -
#define     SYN     22      //  0x16    -       -
#define     ETB     23      //  0x17    -       -
#define     CAN     24      //  0x18    -       -
#define     EM      25      //  0x19    -       -
#define     SUB     26      //  0x1a    -       -
#define     ESC     27      //  0x1b    -       Escape
#define     FS      28      //  0x1c    -       -
#define     GS      29      //  0x1d    -       -
#define     RS      30      //  0x1e    -       -
#define     US      31      //  0x1f    -       -
#define     SP      32      //  0x20    ' '     Space
#define     DEL     127     //  0x7f    -       Delete

#endif
