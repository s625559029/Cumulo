#include "Volume.h"
#include "Color.h"

using namespace std;
using namespace lux;

class Union:public Volume<float>
{
    public:
    Union(Volume<float>& v1,Volume<float>& v2):f(v1),g(v2){}
    ~Union() {}

    const float eval(const Vector& P) const{return f.eval(P)>g.eval(P)?f.eval(P):g.eval(P);}

    private:
    Volume<float>& f;
    Volume<float>& g;
};

class UnionList:public Volume<float>
{
    public:
    UnionList(vector<VolumeFloatPtr>& list) : volume_list(list) {}
    ~UnionList() {}

    inline const float eval(const Vector& P) const{
        float tmp_max = 0;
        for(VolumeFloatPtr v : volume_list)
        {
            if(v->eval(P) > tmp_max) tmp_max = v -> eval(P);
        }
        return tmp_max;
    }
    private:
        vector<VolumeFloatPtr>& volume_list;
};

class Intersection:public Volume<float>
{
    public:
    Intersection(Volume<float>& v1,Volume<float>& v2):f(v1),g(v2){}
    ~Intersection() {}

    const float eval(const Vector& P) const{return f.eval(P)<g.eval(P)?f.eval(P):g.eval(P);}

    private:
    Volume<float>& f;
    Volume<float>& g;
};

class CutOut:public Volume<float>
{
    public:
    CutOut(Volume<float>& v1,Volume<float>& v2):f(v1),g(v2){}
    ~CutOut() {}

    const float eval(const Vector& P) const{return f.eval(P)<-g.eval(P)?f.eval(P):-g.eval(P);}

    private:
    Volume<float>& f;
    Volume<float>& g;
};

class Mask:public Volume<float>
{
    public:
    Mask(Volume<float>& v):volume(v){}
    ~Mask() {}

    const float eval(const Vector& P) const{return volume.eval(P)>0 ? 1 : 0;}

    private:
    Volume<float>& volume;
};

class Clamp:public Volume<float>
{
    public:
    Clamp(Volume<float>& v, float f):volume(v), rho(f){}
    ~Clamp() {}

    const float eval(const Vector& P) const
    {
      if(volume.eval(P)<0) return 0; 
      else if(volume.eval(P)>1) return 1; 
      else return rho * volume.eval(P);
    }

    private:
    Volume<float>& volume;
    float rho;
};

class VolumeDensity:public Volume<float>
{
    public:
    VolumeDensity(Volume<float>& v):volume(v),density(1){}
    VolumeDensity(Volume<float>& v,const float d):volume(v),density(d){}
    ~VolumeDensity() {}

    const float eval(const Vector& P) const{return density*volume.eval(P);}
    private:
    Volume<float>& volume;
    const float density;
};

class VolumeColor:public Volume<Color>
{
    public:
    VolumeColor(Volume<float>& v,Color c):volume(v),color(c),BGC(Color(0,0,0,0)){}
    ~VolumeColor() {}

    const Color eval(const Vector& P) const{return volume.eval(P)>0 ? color : BGC;}
    const Volume<float>& getVolume(){return volume;}
    private:
    Volume<float>& volume;
    const Color color;
    const Color BGC;
};

class ColorUnion:public Volume<Color>
{
    public:
    ColorUnion(Volume<Color>& v1,Volume<Color>& v2):f(v1),g(v2){}
    ~ColorUnion() {}

    const Color eval(const Vector& P) const{return f.eval(P)+g.eval(P);}

    private:
    Volume<Color>& f;
    Volume<Color>& g;
};


class UnionColorList:public Volume<Color>
{
    public:
    UnionColorList(vector<VolumeColorPtr>& list) : color_list(list) {}
    ~UnionColorList() {}

    inline const Color eval(const Vector& P) const{
        Color sum = Color(0,0,0,0);
        int count = 0;
        for(VolumeColorPtr v : color_list)
        {
            Color temp_c = v -> eval(P);
            if(temp_c != Color(0,0,0,0))  count++;
            sum += v -> eval(P);
        }
        return sum;
    }
private:
    vector<VolumeColorPtr >& color_list;
};

class Translate:public Volume<float>
{
    public:
    Translate(Volume& volume, const Vector x):v(volume),xt(x){}
    ~Translate(){}

    const float eval(const Vector& P) const{return v.eval(P-xt);}
    
    private:
    Volume<float>& v;
    const Vector xt;
};

class Scale:public Volume<float>
{
    public:
    Scale(Volume& volume, const float l):v(volume),L(l){}
    ~Scale(){}

    const float eval(const Vector& P) const{return v.eval(P/L);}
    
    private:
    Volume<float>& v;
    const float L;
};

class Rotate:public Volume<float>
{
    public:
    Rotate(Volume<float>& volume, const Vector axis, float theta):v(volume), a(axis),t(-theta){}
    ~Rotate(){}

    const float eval(const Vector& P) const
    {
      Vector temp1 = P*cos(t);
      Vector temp2 = a*(a*P)*(1-cos(t));
      Vector temp3 = a^P*sin(t);
      return v.eval(temp1+temp2+temp3);
    }
    
    private:
    Volume<float>& v;
    const Vector a;
    const float t;
};

class BlinnBlend:public Volume<float>
{
    public:
    BlinnBlend(Volume<float>& v1, Volume<float>& v2):f(v1), g(v2), beta(){s1=1.5;s2=1;beta=2;}
    ~BlinnBlend(){}

    const float eval(const Vector& P) const
    {
      float e1 = f.eval(P)/s1;
      float e2 = g.eval(P)/s2;
      return exp(e1)+exp(e2)-beta;
    }
    
    private:
    Volume<float>& f;
    Volume<float>& g;
    float s1,s2,beta;
};

class TurnTable
{
    public:
    TurnTable(){}
    ~TurnTable(){}

    Vector eval(const Vector& P, Vector axis, float theta)
    {
      a=axis;
      t=theta;
      Vector temp1 = P*cos(t);
      Vector temp2 = a*(a*P)*(1-cos(t));
      Vector temp3 = a^P*sin(t);
      return temp1+temp2+temp3;
    }
    
    private:
    Vector a;
    float t;
};
