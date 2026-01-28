#ifndef UIControlPointInterface_h__
#define UIControlPointInterface_h__

class UIControlPoint;

class UIControlPointInterface
{
public:
  virtual void RemoveControlPoint(UIControlPoint* point) = 0;
  virtual void RefreshControlPoint(UIControlPoint* point) = 0;
protected:
private:
};
#endif // UIControlPointInterface_h__
