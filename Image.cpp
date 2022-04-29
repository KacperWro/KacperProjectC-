//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"
#include<cmath>




bool Image::load(string filename)
{
    ifstream ifs(filename, std::ios::binary); // reading the data raw
    string magicNumber;
    ifs >> magicNumber;
    ifs >> this->w;
    ifs >> this->h;
    int p;
    ifs >> p;
    ifs.ignore(256, '\n'); //to ignore all binary data
    if(p==255)
    {
        delete[] pixels;
        pixels = new Rgb[w*h];
        unsigned char pix[3];
        for (int i = 0; i < w*h; i++)
        {
            ifs.read(reinterpret_cast<char *>(pix), 3); // reads 3 bytes of data as a char
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
        }

    }
    return true;

}
bool Image::loadRaw(string filename)
{
    ifstream in(filename);
    if(in)
    {
        in >> w>> h;
        pixels = new Rgb[w*h];
        float r,g , b;
        for(int i = 0; i < w*h;i++)
        {
            in >> r>>g>>b;

//            this->pixels[i].r = (unsigned char)std::max(1.0f, powf(r, 1/2.2)*255);
//            this->pixels[i].g = (unsigned char)std::max(1.0f, powf(g, 1/2.2)*255);
//            this->pixels[i].b = (unsigned char)std::max(1.0f, powf(b, 1/2.2)*255);

            this->pixels[i].r = (unsigned char)(r*255);
            this->pixels[i].g = (unsigned char)(g*255);
            this->pixels[i].b = (unsigned char)(b*255);
        }
        in.close();
        return true;
    }
    return false;
}
bool Image::savePPM(string filename)
{
    ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n";
    ofs << this->w << " ";
    ofs << this->h << "\n";
    ofs << 255 << "\n";

    for (int i = 0; i < this->w * this->h;i++)
    {
        ofs << this->pixels[i].r;
        ofs << this->pixels[i].g;
        ofs << this->pixels[i].b;
    }

    ofs.close();
    return false;
}


void Image::filterRed()
{
    for (int i = 0; i < w*h; i++)
    {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterGreen()
{
    for (int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterBlue()
{
    for (int i = 0; i < w*h; i++)
    {
        this->pixels[i].g = 0;
        this->pixels[i].r = 0;
    }
}

// https://www.baeldung.com/cs/convert-rgb-to-grayscale   3.3. Luminosity Method
void Image::greyScale()
{
    for (int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = (this->pixels[i].r * 0.3)  + (this->pixels[i].g * 0.59) +  (this->pixels[i].b * 0.11);
        this->pixels[i].g = (this->pixels[i].r * 0.3)  + (this->pixels[i].g * 0.59) +  (this->pixels[i].b * 0.11);
        this->pixels[i].b = (this->pixels[i].r * 0.3)  + (this->pixels[i].g * 0.59) +  (this->pixels[i].b * 0.11);
    }
}

// Horizontal and Vertical Flip: https://www.youtube.com/watch?v=Yn_8KXuBXMc&list=PLG5M8QIx5lkzdGkdYQeeCK__As6sI2tOY&index=7
void Image::flipHorizontal()
{
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w/2; x++)
        {
            Rgb temp(this->pixels[x + y * w].r, this->pixels[x + y * w].g, this->pixels[x + y * w].b);

            this->pixels[x + y * w].r = this->pixels[(w-1-x) + y * w].r;
            this->pixels[x + y * w].g = this->pixels[(w-1-x) + y * w].g;
            this->pixels[x + y * w].b = this->pixels[(w-1-x) + y * w].b;

            this->pixels[(w-1-x) + y * w].r = temp.r;
            this->pixels[(w-1-x) + y * w].g = temp.g;
            this->pixels[(w-1-x) + y * w].b = temp.b;

        }
    }

}
void Image::flipVertically()
{
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h/2; y++)
        {
            Rgb temp(this->pixels[x + y * w].r, this->pixels[x + y * w].g, this->pixels[x + y * w].b);

            this->pixels[x + y * w].r = this->pixels[x + (h-1-y) * w].r;
            this->pixels[x + y * w].g = this->pixels[x + (h-1-y) * w].g;
            this->pixels[x + y * w].b = this->pixels[x + (h-1-y) * w].b;

            this->pixels[x + (h-1-y) * w].r = temp.r;
            this->pixels[x + (h-1-y) * w].g = temp.g;
            this->pixels[x + (h-1-y) * w].b = temp.b;

        }
    }

}

// Additional Feature 1: Mirroring image horizontally and vertically
void Image::MirrorHorizontal()
{
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w/2; x++)
        {
            Rgb temp(this->pixels[x + y * w].r, this->pixels[x + y * w].g, this->pixels[x + y * w].b);

            this->pixels[(w-1-x) + y * w].r = temp.r;
            this->pixels[(w-1-x) + y * w].g = temp.g;
            this->pixels[(w-1-x) + y * w].b = temp.b;

        }
    }
}

void Image::MirrorVertical()
{
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h/2; y++)
        {
            Rgb temp(this->pixels[x + y * w].r, this->pixels[x + y * w].g, this->pixels[x + y * w].b);

            this->pixels[x + (h-1-y) * w].r = temp.r;
            this->pixels[x + (h-1-y) * w].g = temp.g;
            this->pixels[x + (h-1-y) * w].b = temp.b;

        }
    }
}

// Additional Feature 2: Applying Sepia filter to image
// https://dyclassroom.com/image-processing-project/how-to-convert-a-color-image-into-sepia-image
void Image::filterSepia()
{
    double tr;
    double tg;
    double tb;

    for (int i = 0; i < w*h; i++)
    {
        tr = std::min(255.0, (0.393 * this->pixels[i].r) + (0.769 * this->pixels[i].g) + (0.189 * this->pixels[i].b));
        tg = (0.349 * this->pixels[i].r) + (0.686 * this->pixels[i].g) + (0.168 * this->pixels[i].b);
        tb = (0.272 * this->pixels[i].r) + (0.534 * this->pixels[i].g) + (0.131 * this->pixels[i].b);

        if(tr > 255)
        {
            this->pixels[i].r = 255;
        }
        else
        {
            this->pixels[i].r = tr;
        }

        if(tg > 255)
        {
            this->pixels[i].g = 255;
        }
        else
        {
            this->pixels[i].g = tg;
        }

        if(tb > 255)
        {
            this->pixels[i].b = 255;
        }
        else
        {
            this->pixels[i].b = tb;
        }

    }


}
void Image::bit8()
{
    for (int i = 0; i < w*h; i++)
    {
        pixels[i].r = (pixels[i].r/64)*64;
        pixels[i].g = (pixels[i].g/64)*64;
        pixels[i].b = (pixels[i].b/64)*64;

    }
}
// Additional feature 3: Applying negative filter to image
// https://dyclassroom.com/image-processing-project/how-to-convert-a-color-image-into-negative
void Image::NegativeFilter()
{
    for (int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = 255 - this->pixels[i].r;
        this->pixels[i].g = 255 - this->pixels[i].g;
        this->pixels[i].b = 255 - this->pixels[i].b;
    }
}

void Image::GammaEncoding()
{
    for (int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixels[i].r/255.0f, 1/2.2) * 255 + 0.5f)));
        this->pixels[i].g = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixels[i].g/255.0f, 1/2.2) * 255 + 0.5f)));
        this->pixels[i].b = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixels[i].b/255.0f, 1/2.2) * 255 + 0.5f)));

    }

//    for (int i = 0; i < w*h; i++)
//    {
//        this->pixels[i].r = pow(this->pixels[i].r 2.2;
//        this->pixels[i].g = 2.2;
//        this->pixels[i].b = 2.2;
//    }

//    for (int i = 0; i < w*h; i++)
//    {
//        this->pixels[i].r = (unsigned char)(std::max(0.f, std::min(255.f, powf(this->pixels[i].r, 1/2.2) * 255 + 0.5f)));
//        this->pixels[i].g = (unsigned char)(std::max(0.f, std::min(255.f, powf(this->pixels[i].g, 1/2.2) * 255 + 0.5f)));
//        this->pixels[i].b = (unsigned char)(std::max(0.f, std::min(255.f, powf(this->pixels[i].b, 1/2.2) * 255 + 0.5f)));
//    }



}
void Image::advancedFeature() {


    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w/2; x++)
        {
            this->pixels[(w-1-x) + y * w].r = 0;
            this->pixels[(w-1-x) + y * w].g = 0;
            this->pixels[(w-1-x) + y * w].b = 0;
        }
    }

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h/2; y++)
        {
            this->pixels[x + (h-1-y) * w].r = 0;
            this->pixels[x + (h-1-y) * w].g = 0;
            this->pixels[x + (h-1-y) * w].b = 0;

        }
    }

}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}