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

/*
 *  - Monomino is the abstract class used for creation of other
 *    polyominoes and can not be used to create instances of itself
 *  - tile is a part/piece which is used in filling the rectangle
 *  - for appropriate work of program child classes should
 *    be created in an appropriate way:
 *    -- tileHeight <= tileWidth
 *    -- unitsInTile - number of polyominoes in the tile
 *    -- polyomino that can not be user to create rectangle tile
 *       must have these parameters
 *       "tileHeight = -1; tileWidth = -1; unitsInTile = 0;"
 *    -- picture of the tile should be provided ( in showTile() )
 */

#ifndef POLYMINOS_H_INCLUDED
#define POLYMINOS_H_INCLUDED

#include <iostream>

class Monomino {
protected:
    int tileHeight;
    int tileWidth;
    int unitsInTile;
public:
    virtual void showTile() = 0;
    void canFill(int n, int m);
};

class Domino : public Monomino {
public:
    Domino() {
        tileHeight = 1;
        tileWidth = 2;
        unitsInTile = 1;
    }
    void showTile() {
        std::cout << " ___ " << std::endl;
        std::cout << "|_|_|" << std::endl;
    }
};

class TrominoL : public Monomino {
public:
    TrominoL() {
        tileHeight = 2;
        tileWidth = 3;
        unitsInTile = 2;
    }
    void showTile() {
        std::cout << " _____ " << std::endl;
        std::cout << "|  _| |" << std::endl;
        std::cout << "|_|___|" << std::endl;
    }
};

class TrominoI : public Monomino {
public:
    TrominoI() {
        tileHeight = 1;
        tileWidth = 3;
        unitsInTile = 1;
    }
    void showTile() {
        std::cout << " _____ " << std::endl;
        std::cout << "|_|_|_|" << std::endl;
    }
};

class TetraminoI : public Monomino {
public:
    TetraminoI() {
        tileHeight = 1;
        tileWidth = 4;
        unitsInTile = 1;
    }
    void showTile() {
        std::cout << " _______ " << std::endl;
        std::cout << "|_|_|_|_|" << std::endl;
    }
};

class TetraminoO : public Monomino {
public:
    TetraminoO() {
        tileHeight = 2;
        tileWidth = 2;
        unitsInTile = 1;
    }
    void showTile() {
        std::cout << " ___ " << std::endl;
        std::cout << "|   |" << std::endl;
        std::cout << "|___|" << std::endl;
    }
};

class TetraminoZ : public Monomino {
    //does not fill rectangles
public:
    TetraminoZ() {
        tileHeight = -1;
        tileWidth = -1;
        unitsInTile = 0;
    }
    void showTile() {
        std::cout << " _____ " << std::endl;
        std::cout << "|_  |_|" << std::endl;
        std::cout << "|_|___|" << std::endl;
    }
};

class TetraminoS : public Monomino {
    //does not fill rectangles
public:
    TetraminoS() {
        tileHeight = -1;
        tileWidth = -1;
        unitsInTile = 0;
    }
    void showTile() {
        std::cout << " _____ " << std::endl;
        std::cout << "|_|  _|" << std::endl;
        std::cout << "|___|_|" << std::endl;
    }
};

class TetraminoL : public Monomino {
public:
    TetraminoL() {
        tileHeight = 2;
        tileWidth = 4;
        unitsInTile = 2;
    }
    void showTile() {
        std::cout << " ______ " << std::endl;
        std::cout << "|  __| |" << std::endl;
        std::cout << "|_|____|" << std::endl;
    }
};

class TetraminoJ : public Monomino {
public:
    TetraminoJ() {
        tileHeight = 2;
        tileWidth = 4;
        unitsInTile = 2;
    }
    void showTile() {
        std::cout << " ______ " << std::endl;
        std::cout << "| |__  |" << std::endl;
        std::cout << "|____|_|" << std::endl;
    }
};

class TetraminoT : public Monomino {
public:
    TetraminoT() {
        tileHeight = 4;
        tileWidth = 4;
        unitsInTile = 4;
    }
    void showTile() {
        std::cout << " _______ " << std::endl;
        std::cout << "| |_   _|" << std::endl;
        std::cout << "|  _|_| |" << std::endl;
        std::cout << "|_| |_  |" << std::endl;
        std::cout << "|_____|_|" << std::endl;
    }
};

class PentominoI : public Monomino {
public:
    PentominoI() {
        tileHeight = 1;
        tileWidth = 5;
        unitsInTile = 1;
    }
    void showTile() {
        std::cout << " _________ " << std::endl;
        std::cout << "|_|_|_|_|_|" << std::endl;
    }
};

class PentominoL : public Monomino {
public:
    PentominoL() {
        tileHeight = 2;
        tileWidth = 4;
        unitsInTile = 2;
    }
    void showTile() {
        std::cout << " _________ " << std::endl;
        std::cout << "|  _____| |" << std::endl;
        std::cout << "|_|_______|" << std::endl;
    }
};

class PentominoF : public Monomino {
        //does not fill rectangles
public:
    PentominoF() {
        tileHeight = -1;
        tileWidth = -1;
        unitsInTile = 0;
    }
    void showTile() {
        std::cout << " _____ " << std::endl;
        std::cout << "|_|  _|" << std::endl;
        std::cout << "|_  | |" << std::endl;
        std::cout << "|_|_|_|" << std::endl;
    }
};

#endif // POLYMINOS_H_INCLUDED
