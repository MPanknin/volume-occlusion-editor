//#include <vector>
//#include <map>
//
//#include "osgDB/WriteFile"
//
//#include "osg/Image"
//#include "osg/TransferFunction"
//#include "osg/Vec4"
//
//using namespace std;
//using namespace osg;
//
//// split string 
//vector<string> split(const string& s, const string& delim, const bool keep_empty = true)
//{
//  vector<string> result;
//  if (delim.empty()) 
//  {
//    result.push_back(s);
//    return result;
//  }
//  string::const_iterator substart = s.begin(), subend;
//  while (true) 
//  {
//    subend = search(substart, s.end(), delim.begin(), delim.end());
//    string temp(substart, subend);
//    if (keep_empty || !temp.empty()) 
//    {
//      result.push_back(temp);
//    }
//    if (subend == s.end()) 
//    {
//      break;
//    }
//    substart = subend + delim.size();
//  }
//  return result;
//}
//
//inline string trim_right(const string &source , const string& t = " ")
//{
//  string str = source;
//  return str.erase(str.find_last_not_of(t) + 1);
//}
//
//inline string trim_left( const string& source, const string& t = " ")
//{
//  string str = source;
//  return str.erase(0 , source.find_first_not_of(t) );
//}
//
//inline string trim(const string& source, const string& t = " ")
//{
//  string str = source;
//  return trim_left(trim_right( str , t) , t );
//} 
//
//int main()
//{
//  // container for colortables
//  map<string, TransferFunction1D*> functions;
//  map<string, TransferFunction1D*>::iterator it;
//
//  // line buffer
//  string line;
//
//  // name of current color table
//  string name;
//
//  // where to put results?
//  string outPath = "colorTables/";
//  string fileSuffix = ".bmp";
//
//  // open od color tables
//  ifstream infile ("ColTabs");
//  if (infile.is_open())
//  {
//    while (infile.good())
//    {
//      getline (infile, line);
//
//      if(line.find("Name") != -1)
//      {
//        // parse name
//        int nameStart = line.find(":") + 1;
//        int nameEnd = line.find("\n", nameStart + 1);
//        name = line.substr(nameStart, nameEnd);
//        
//        // trim whitespaces and tabs
//        name = trim(name, " ");
//        name = trim(name, "\t");
//
//        // add color table / transfer function with current name
//        functions.insert(pair<string, TransferFunction1D*>(name, new TransferFunction1D()));
//      }
//      else if(line.find("Value-Color.") != -1)
//      {
//        // parse color
//        int colorStart = line.find(":") + 1;
//        int colorEnd = line.find("\n", colorStart);
//        string vals = line.substr(colorStart, colorEnd);
//
//        // split idx and color values
//        vector<string> items = split(vals, "`", false);
//
//        // first item is position of control point
//        float idx = atof(items[0].c_str()) * 255;
//        
//        // remaining items are color values
//        Vec4 color;
//        color.x() = atoi(items[1].c_str());
//        color.y() = atoi(items[2].c_str());
//        color.z() = atoi(items[3].c_str());
//
//        // set opaque
//        color.w() = 255;
//
//        // get color table with current name
//        it = functions.find(name);
//        TransferFunction1D* trans = it->second;
//
//        // set control point and color
//        trans->setColor(idx, color);
//      }
//    }
//    infile.close();
//  }
//
//  // reconstruct images
//  for( it = functions.begin(); it != functions.end(); it++)
//  {
//    Image* image = new Image;
//
//    image->allocateImage(256, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE);
//    
//    for(int x = 0; x < 256; x++)
//    {
//      Vec4 color = it->second->getColor(x);
//      image->data(x)[0] = color.x();
//      image->data(x)[1] = color.y();
//      image->data(x)[2] = color.z();
//      image->data(x)[3] = color.w();
//
//    }
//    // build target path
//    string outFile = outPath;
//    // get name 
//    outFile.append(it->first);
//    outFile.append(fileSuffix);
//
//    // write 
//    osgDB::writeImageFile(*image, outFile);   
//  }
//
//  printf("converted %i color tables \n", functions.size());
//  system("pause");
//}