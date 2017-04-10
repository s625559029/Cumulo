#include "Image.h"
#include <iostream>
#include <OpenImageIO/imageio.h> 
OIIO_NAMESPACE_USING

using namespace std;
using namespace lux;

const float Image::interpolatedValue( float x, float y, int c ) const
{
   int ix, iy, iix, iiy;
   float wx, wy, wwx, wwy;
   interpolationCoefficients( x, y, wx, wwx, wy, wwy, ix, iix, iy, iiy );
   float v = value(  ix,  iy, c ) *  wx *  wy
           + value( iix,  iy, c ) * wwx *  wy
	   + value(  ix, iiy, c ) *  wx * wwy
	   + value( iix, iiy, c ) * wwx * wwy;
   return v;
}


std::vector<float> Image::interpolatedPixel( float x, float y ) const
{
   int ix, iy, iix, iiy;
   float wx, wy, wwx, wwy;
   interpolationCoefficients( x, y, wx, wwx, wy, wwy, ix, iix, iy, iiy );
   std::vector<float> pix;
   for( size_t c=0;c<Depth();c++ )
   {
      float v = value(  ix,  iy, c ) *  wx *  wy
              + value( iix,  iy, c ) * wwx *  wy
	      + value(  ix, iiy, c ) *  wx * wwy
	      + value( iix, iiy, c ) * wwx * wwy;
      pix.push_back( v );
   }
   return pix;
}

void imageLinearInterpolation( float x, float dx, int nx, int& i, int& ii, float& w, float& ww, bool isperiodic )
{
    float r = x/dx;
    i  =  r;
    if( !isperiodic )
    {
    if( i >= 0 && i < nx )
    {
       ii = i + 1;
       w = r-i;
       ww = 1.0 - w;
       if(  ii >= nx )
       {
	  ii = nx-1;
       }
    }
    else
    {
       i = ii = 0;
       w = ww = 0;
    }
    }
    else
    {
       w = r-i;
       while( i < 0 ){ i += nx; }
       while( i >= nx ){ i -= nx; }

       ii = i+1;
       ww = 1.0 - w;
       if( ii >= nx ){ ii -= nx; }
    }
}




void Image::interpolationCoefficients( float x, float y, 
                                      float& wx, float& wwx,
				      float& wy, float& wwy,
				      int& ix, int& iix,
				      int& iy, int& iiy 
			  	    ) const
{
   imageLinearInterpolation( x, 1.0/Width(), Width(), ix, iix, wx, wwx, false );
   imageLinearInterpolation( y, 1.0/Height(), Height(), iy, iiy, wy, wwy, false );
}


void lux::setPixel( Image& img, int x, int y, std::vector<float>& value )
{
   size_t nb = ( value.size() < img.Depth() ) ? value.size() : img.Depth();
   for( size_t i=0;i<nb;i++ )
   {
      img.value( x, y, i ) = value[i];
   }
}

/*float imagePlaneValue( float v, float dG, float dB )
{
   if( v == 0.0 ){ return 0.0; }
   return pow(v, dG) * dB;
}

void Image::saveAsEXR(const char *filepath)
{
    float* imagedata = new float[ this->Width()* this->Height() * this->Depth() ];
    float displayGamma=1, displayBrightness=1;
   // fill image with the contents of img

   long index = 0;
   for( int j=0;j<this->Height();j++ )
   {
      for( int i=0;i<this->Width();i++ )
      {
         vector<float> pix = this->pixel(i,this->Height() - j - 1);
	 for( size_t c=0;c<(size_t)this->Depth();c++ )
         {
            if(c<3){ pix[c] = imagePlaneValue( pix[c], displayGamma, displayBrightness ); }
	    imagedata[index++] = pix[c];
         }
      }
   }
      ImageOutput *out = ImageOutput::create(filepath);
      ImageSpec spec(this->width, this->height, this->depth, TypeDesc::FLOAT);
      out->open(filepath, spec);
      out->write_image(TypeDesc::FLOAT, imagedata);

      delete out;
}*/
