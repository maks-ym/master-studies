/*
 *  Program for to check filling of rectangle
 *  with different types of polyominoes
 *
 *  PW - WEiTI - PROI - Lab2
 *
 *  Maksym Bakhmut
 *
 *  2016-12-15
 */

#include <iostream>
#include <climits>
#include <vector>
#include "polyminos.h"

using namespace std;

int main()
{
//    Domino domino1 = new Domino();
//    std::cout << domino1.canFill(2, 7) << std::endl;
//    std::cout << "--------------------" << std::endl;

//    PentominoF testmino;
//    vector<int> tests = {-1, 0, INT_MAX };
//    vector<int> tests = { 1,2,3,5,4,6,11};
//    for(int i = 0; i < tests.size(); ++i) {
//        for(int j = i; j < tests.size(); ++j) {
//            std::cout << "test # " << i << j << std::endl;
//            std::cout << "values " << tests[i] << "\t" << tests[j] << std::endl;
//            testmino.canFill(tests[i], tests[j]);
//            std::cout << "------------------------------------------------------" << std::endl << std::endl;
//        }
//    }

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
