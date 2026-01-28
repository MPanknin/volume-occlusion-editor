//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include "Helper.h"
//#include "osg\Image"
//#include "osgDB\WriteFile"
//#include <math.h>
//
//void main()
//{
//  //osg::Image* resImg = new osg::Image;
//  //resImg->allocateImage(348, 458, 500, GL_LUMINANCE, GL_UNSIGNED_BYTE);
//
//  std::ifstream infile ("uh_8bit_ascii.dat");
//  if (!infile.is_open())
//  {
//    return;
//  }
//
//  int numLines = 0;
//  int numSlices = 0;
//  std::string line;
//  while (infile.good())
//  {
//    getline(infile, line);
//    numLines++;
//    if(numLines == 100)
//    {
//      numLines = 0;
//      numSlices++;
//    }
//
//    std::vector<std::string> tokens;
//    Helper::SplitString(line, "\t", tokens);
//
//    std::cout << tokens.size() << std::endl;
//
//    //for (int x = 0; x < tokens.size(); x++)
//    //{
//    //  resImg->data(numLines, numSlices, x)[0] = atoi(tokens[x].c_str());
//    //}
//  }
//  std::cout << numSlices << std::endl;
//
//  //osgDB::writeImageFile(*resImg, "temp/vol.dds");
//
//  system("pause");
//}