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

#include <iostream>
#include <climits>
#include <vector>
#include "polyminos.h"

using namespace std;

int main()
{

    int val1, val2;
    std::cout << "================= LIMITS TESTS =======================" << std::endl;

    std::cout << "-------- {-1, 0, INT_MAX } ---------------------------" << std::endl;
    Domino dominoTest;
    val1 = -1; val2 = 7;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    dominoTest.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 8; val2 = 0;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    dominoTest.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 2; val2 = INT_MAX;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    dominoTest.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;


    std::cout << "================= DOMINO TESTS =======================" << std::endl;

    std::cout << "----------- Domino I ---------------------------------" << std::endl;
    Domino domino;
    val1 = 11; val2 = 7;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    domino.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 7; val2 = 6;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    domino.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 2; val2 = 5;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    domino.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;


    std::cout << "================= TROMINO TESTS ======================" << std::endl;

    std::cout << "---------- Tromino I ---------------------------------" << std::endl;
    TrominoI tromino1;
    val1 = 6; val2 = 11;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tromino1.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 7; val2 = 6;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tromino1.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 3; val2 = 11;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tromino1.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 7; val2 = 3;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tromino1.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 1; val2 = 3;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tromino1.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 0; val2 = 1;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tromino1.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "---------- Tromino L ---------------------------------" << std::endl;
    TrominoL tromino2;
    val1 = 6; val2 = 11;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tromino2.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 7; val2 = 6;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tromino2.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 2; val2 = 6;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tromino2.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = -1; val2 = 6;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tromino2.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;


    std::cout << "================ TETRAMINO TESTS =====================" << std::endl;

    std::cout << "-------- Tetramino I ---------------------------------" << std::endl;
    TetraminoI tetramino1;

    val1 = 2; val2 = 6;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tetramino1.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 2; val2 = 7;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tetramino1.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "-------- Tetramino O ---------------------------------" << std::endl;
    TetraminoO tetramino2;
    val1 = 6; val2 = 6;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tetramino2.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 4; val2 = 11;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tetramino2.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "-------- Tetramino L ---------------------------------" << std::endl;
    TetraminoL tetramino3;
    val1 = 4; val2 = 6;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tetramino3.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "-------- Tetramino J ---------------------------------" << std::endl;
    TetraminoJ tetramino4;
    val1 = 4; val2 = 6;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tetramino4.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "-------- Tetramino Z ---------------------------------" << std::endl;
    TetraminoZ tetramino5;
    val1 = 17; val2 = 3;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tetramino5.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "-------- Tetramino S ---------------------------------" << std::endl;
    TetraminoZ tetramino6;
    val1 = 17; val2 = 3;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tetramino6.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "-------- Tetramino T ---------------------------------" << std::endl;
    TetraminoT tetramino7;
    val1 = 4; val2 = 4;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tetramino7.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 120; val2 = 80;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    tetramino7.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;


    std::cout << "================ PENTOMINO TESTS =====================" << std::endl;

    std::cout << "-------- Pentomino I ---------------------------------" << std::endl;
    PentominoI pentomino1;
    val1 = 24; val2 = 41;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    pentomino1.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;
    val1 = 16; val2 = 20;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    pentomino1.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "-------- Pentomino L ---------------------------------" << std::endl;
    PentominoL pentomino2;
    val1 = 10; val2 = 7;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    pentomino2.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "-------- Pentomino F ---------------------------------" << std::endl;
    PentominoF pentomino3;
    val1 = 10; val2 = 15;
    std::cout << "values " << val1 << "\t" << val2 << std::endl;
    pentomino3.canFill(val1, val2);
    std::cout << "------------------------------------------------------" << std::endl;

}
