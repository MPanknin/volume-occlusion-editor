#ifndef RawLoader_h__
#define RawLoader_h__

namespace osg
{
  class Image;
}

class RawManager
{
public:
	RawManager();
	~RawManager();
  
  static osg::Image* LoadRawFile(const char* path, int skip, int numBytes, 
                            int inX, int inY, int inZ,
                            int outX, int outY, int outZ,
                            int offX = 0, int offY = 0, int offZ = 0);

  static void Save(osg::Image* resImg, const char* path);

protected:
private:
};

#endif // RawLoader_h__