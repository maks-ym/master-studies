/**
 * Copyright (C) 2016-12-15 Maks-ym (hereafter "Author")
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Author shall not be used in advertising or
 * otherwise to promote the sale, use or other dealings in this Software without prior written
 * authorization from the Author.
 */

/**
 *  Program is to check filling of rectangle with different types of polyominos
 */

#include "polyminos.h"
#include <iostream>

void Monomino::canFill(int n, int m) {
    if( tileHeight <=0 ||  tileWidth <= 0 ) {
        std::cout << "Nothing can't be filled by this n-mino." << std::endl;
        return;
    }
    if(m <= 0 || n <= 0) {
        std::cout << "Nothing to fill." << std::endl;
        return;
    }
    //check if the area is not too big
    if(m + n < 1) {
        std::cout << "Too big, can't fill." << std::endl;
        return;
    }
    //check ratio
    if(m < n) {
        //swap
        int tmp = n; n = m; m = tmp;
        std::cout << "Area to fill is rotated 90deg." << std::endl;
    }
    //check whether area is big enough
    if ( ( (m * n) %  ( tileHeight * tileWidth) != 0 ) ||
         ( n < tileHeight && (n < tileWidth || m < tileHeight) ) ||
         ( m < tileWidth && ( m < tileHeight || n < tileWidth) ) ){
            std::cout << "Area can't be filled" << std::endl;
            return;
    }
    //if OK, check how it can be filled
    int fillArea = n * m;//an area to be filled with tiles
    int vPieceNum = -1;  //number of vertically placed pieces
    int hPieceNum = -1;  //number of horizontally placed pieces

    //print tile that will be used
    std::cout << "Going to fill area with such tiles" << std::endl;
    showTile();
    //check a special case when tile is square
    if(tileHeight == tileWidth) {
        if( (n%tileHeight == 0) && ( m % tileWidth == 0 )) {
            hPieceNum = (n/tileHeight) * (m/tileWidth);
            std::cout << "Can be filled with " << hPieceNum << "  tiles." << std::endl;
            std::cout << "Number of units: " << hPieceNum * unitsInTile << std::endl;
            return;
        }
    }
    //check whether tiles fit vertically
    if( n%tileHeight == 0 ) {
        //check whether tiles fit horizontally
        if( m % tileWidth == 0 ) {
            hPieceNum = (n/tileHeight) * (m/tileWidth);
            vPieceNum = 0;
        }
        else if ( m > tileWidth ) {
            //check whether it is possible to fill the rest area with rotated tiles
            if( n % tileWidth == 0 ) {
                if(m % tileWidth == tileHeight ) {
                    hPieceNum = (n/tileHeight) * (m/tileWidth);
                }
                else {
                    for ( int i = 0; tileWidth < (m - i*tileWidth); ++i ) {
                        if( (m % tileWidth + i * tileWidth) % tileHeight == 0 ) {
                            hPieceNum = (n/tileHeight) * (m/tileWidth - i);
                            break;
                        }
                    }
                }
                vPieceNum = ( fillArea - hPieceNum*tileHeight*tileWidth ) / ( tileHeight*tileWidth );
            }
        }
    }
    //otherwise check beginning with vertical tiles
    //check whether tiles fit vertically
    else if ( n != m && n % tileWidth == 0 ) {
        //check whether tiles fit horizontally
        if( m % tileHeight == 0 ) {
            vPieceNum = (n/tileWidth) * (m/tileHeight);
            hPieceNum = 0;
        }
        else if ( m > tileHeight ) {
            //check whether it is possible to fill the rest area with rotated tiles
            if( n % tileHeight == 0 ) {
                if(m % tileHeight == tileWidth ) {
                    vPieceNum = (n/tileWidth) * (m/tileHeight);
                }
                else {
                    for ( int i = 0; tileHeight < (m - i*tileHeight); ++i ) {
                        if( (m % tileHeight + i * tileHeight) % tileWidth == 0 ) {
                            vPieceNum = (n/tileWidth) * (m/tileHeight - i);
                            break;
                        }
                    }
                }
                hPieceNum = ( fillArea - vPieceNum*tileHeight*tileWidth ) / ( tileHeight*tileWidth );
            }
        }
    }
    if(hPieceNum == -1 || vPieceNum == -1) {
        std::cout << "Area can't be filled completely" << std::endl;
        return;
    }
    std::cout << "Can be filled with " << hPieceNum << " horizontal tiles and " << vPieceNum << " vertical tiles." << std::endl;
    std::cout << "Number of units: " << (hPieceNum + vPieceNum) * unitsInTile << std::endl;
    return;
}
