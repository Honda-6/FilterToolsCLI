#pragma once
#include <iostream>
#include <cstring>

class Image
{
private:
    char name[100]{};
    bool rgb{};
public:
    void set_name();
    char* get_name();
    bool isRGB();
    bool isValid();
};

int loadImage();
int load2ndimgformerge(Image &photo);
void saveImage();
void overwrite_image();
bool overwrite();