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
        /*
            In the header of the bitmap file 2 bytes are allocated to specify the number of bits used by each pixel
            these 2 bytes are located right after byte number 28 from the beginning of the file
            Every bitmap file has a constant 54 byte allocated for the header which stores the info and properties of the image
            in terms of dimensions, pixel per meter, size of the entire file, size of the pixel data only and etc.
        */
        fseek(img,28,SEEK_SET);
        fread(&bitsPpixel,2,1,img);
        fclose(img);
        rgb = (bitsPpixel == 24);
    }
    return img != NULL;
}