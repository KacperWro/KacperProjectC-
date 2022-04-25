//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"



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
void Image::greyScale()
{
    for (int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = (this->pixels[i].r * 0.3)  + (this->pixels[i].g * 0.59) +  (this->pixels[i].b * 0.11);
        this->pixels[i].g = (this->pixels[i].r * 0.3)  + (this->pixels[i].g * 0.59) +  (this->pixels[i].b * 0.11);
        this->pixels[i].b = (this->pixels[i].r * 0.3)  + (this->pixels[i].g * 0.59) +  (this->pixels[i].b * 0.11);
    }
}
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
void Image::filterSepia()
{
    double tr;
    double tg;
    double tb;

    for (int i = 0; i < w*h; i++)
    {
        tr = (0.393 * this->pixels[i].r) + (0.769 * this->pixels[i].g) + (0.189 * this->pixels[i].b);
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
void Image::AdditionalFunction3()
{

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