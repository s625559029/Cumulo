/*
 * wedges.C
 *
 *  Created on: Mar 8, 2017
 *      Author: ysun3
 */

#include "WedgeFunc.h"
#include "CumuloFunc.h"

int main(int argc, char** argv)
{
    string type = argv[1];
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);
    string output_path = argv[4];

    if(start < 0 || start > 500) exit(-1);
    if(end < 0 || end > 500) exit(-1);

    //printPara();

    if(type == "-pyro") {
        cout << "Drawing pyro sphere..." << endl;
        string _type = "pyro";
        drawPyrosphere(start, end, output_path, _type);
    }
    if(type == "-noise") {
        cout << "Drawing noise..." << endl;
        string _type = "noise";
        drawNoise(start, end, output_path, _type);
    }
    if(type == "-wisps") {
        cout << "Drawing wisps wedge..." << endl;
        string _type = "wisp";
        drawWisps(start, end, output_path, _type);
    }
    if(type == "-pipe") {
        cout << "Drawing pipe..." << endl;
        string _type = "hw4";
        drawPipe(start, end, output_path, _type);
    }
    if(type == "-cumulo") {
        cout << "Drawing cumulo..." << endl;
        string _type = "hw5";
        drawCumulo(start, end, output_path, _type);
    }
    if(type == "-vgrids") {
        cout << "Writing vector grids..." << endl;
        WriteVectorGrid(0, 1, output_path);
    }
    return 0;
}