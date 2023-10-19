#include "Image.h"

void Image::set_name()
{
    std::cin >> name;
    strcat(name,".bmp");
}
char* Image::get_name()
{
    return name;
}
bool Image::isRGB()
{
    return rgb;
}
bool Image::isValid()
{
    FILE* img {};
    unsigned bitsPpixel{};
    img = fopen(name,"rb");
    if(img)
    {
        fseek(img,28,SEEK_SET);
        fread(&bitsPpixel,2,1,img);
        fclose(img);
        rgb = (bitsPpixel == 24);
    }
    return img != NULL;
}