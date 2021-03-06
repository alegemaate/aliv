/*
 * Image Loader
 * Allan Legemaate
 * 21/05/2019
 * Abstract class defining interface to image loaders
 */

#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <allegro.h>

class ImageLoader {
  public:
    ImageLoader();
    virtual ~ImageLoader();

    virtual int Load(const char* filename) = 0;

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    uint8_t* GetRawData() const;

    virtual BITMAP* GetBitmap();
    const char* GetLocation() const;
    float GetHWRatio() const;
    float GetWHRatio() const;

  protected:
    void SetDimensions();

    uint32_t nWidth;
    uint32_t nHeight;
    uint8_t* pData;
    BITMAP* pImage;
    const char* sLocation;
};

#endif // IMAGELOADER_H
