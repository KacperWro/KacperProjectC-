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


}
void Image::flipVertically()
{


}
void Image::AdditionalFunction2()
{

}
void Image::AdditionalFunction3()
{

}
void Image::AdditionalFunction1()
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