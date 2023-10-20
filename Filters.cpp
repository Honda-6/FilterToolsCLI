#include "Filters.h"
#include <tuple>

using namespace std;

Image src;
unsigned char image[SIZE][SIZE];
unsigned char RGBimage[SIZE][SIZE][RGB];
unsigned char rgbimage2[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE];



/*
    This function copies the first half of the image "coloumns" (starting from the middle coloumn till the first coloumn)
    into the remaining half (starting from the coloumn after the middle one till the last coloumn).
*/
void Filters::mirror_left_to_right()
{
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{SIZE / 2 - 1}, j2{SIZE / 2}; j >= 0 && j2 < SIZE; ++j, j2++)
            {
                for (unsigned short k{}; k < 3; ++k)
                {
                    RGBimage[i][j2][k] = RGBimage[i][j][k];
                }
            }
        }
    }
    else
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{SIZE / 2 - 1}, j2{SIZE / 2}; j >= 0 && j2 < SIZE; ++j, j2++)
            {
                image[i][j2] = image[i][j];
            }
        }
    }
}


/*
    This function copies the second half of the image "coloumns" (starting from the middle coloumn till the last coloumn)
    into the first half (starting from the coloumn preceding the middle one till the first coloumn).
*/
void Filters::mirror_right_to_left()
{
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{SIZE / 2 - 1}, j2{SIZE / 2}; j >= 0 && j2 < SIZE; --j, j2++)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    RGBimage[i][j][k] = RGBimage[i][j2][k];
                }
            }
        }
    }
    else
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{SIZE / 2 - 1}, j2{SIZE / 2}; j >= 0 && j2 < SIZE; --j, j2++)
            {
                image[i][j] = image[i][j2];
            }
        }
    }
}


/*
    This function copies the first half of the image "rows" (starting from the middle row till the first row)
    into the remaining half (starting from the row after the middle one till the row).
*/
void Filters::mirror_up_to_down()
{
    if (src.isRGB())
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int i{SIZE / 2 - 1}, i2{SIZE / 2}; i >= 0 && i2 < SIZE; --i, i2++)
            {
                for (unsigned short k{}; k < RGB; ++k)
                    RGBimage[i2][j][k] = RGBimage[i][j][k];
            }
        }
    }
    else
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int i{SIZE / 2 - 1}, i2{SIZE / 2}; i >= 0 && i2 < SIZE; --i, i2++)
            {
                image[i2][j] = image[i][j];
            }
        }
    }
}

/*
    This function copies the second half of the image "rows" (starting from the middle row till the last row)
    into the first half (starting from the row preceding the middle one till the first row).
*/
void Filters::mirror_down_to_up()
{
    if (src.isRGB())
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int i{SIZE / 2 - 1}, i2{SIZE / 2}; i >= 0 && i2 < SIZE; --i, i2++)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    image[i][j] = image[i2][j];
                }
            }
        }
    }
    else
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int i{SIZE / 2 - 1}, i2{SIZE / 2}; i >= 0 && i2 < SIZE; --i, i2++)
            {
                image[i][j] = image[i2][j];
            }
        }
    }
}

void Filters::mirror_half()
{
    cout << "Select an option to mirror half of the image about the central axes:\n"
         << "1: Mirror upper half about the horizontal axis\n"
         << "2: Mirror lower half about the horizontal axis\n"
         << "3: Mirror right half about the vertical axis\n"
         << "4: Mirror left half about the vertical axis\n";
    short s{};
    cin >> s;
    while (s > 4 || s < 1)
    {
        cout << "Enter a valid number specified in the menu!\n\n";
        cout << "1: Mirror upper half about the horizontal axis\n"
             << "2: Mirror lower half about the horizontal axis\n"
             << "3: Mirror right half about the vertical axis\n"
             << "4: Mirror left half about the vertical axis\n";
        cin >> s;
    }
    switch (s)
    {
    case 1:
        mirror_up_to_down();
        break;
    case 2:
        mirror_down_to_up();
        break;
    case 3:
        mirror_right_to_left();
        break;
    case 4:
        mirror_left_to_right();
        break;
    }
}

/*
    if the value of the pixel is greater than 127 (closer to 255) then it will be white otherwise it will be black
*/
void Filters::Black_White()
{
    if (src.isRGB())
    {
        To_grey();
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

void Filters::invertImage()
{
    /* By subtracting the pixel color from 255, we get the complement which is the opposite shade of the current color. If it’s a light shade, we will get a dark one and vice versa. */
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; i++)
        {
            for (int j{}; j < SIZE; j++)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    RGBimage[i][j][k] = 255 - RGBimage[i][j][k];
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = 255 - image[i][j];
            }
        }
    }
    cout << "Invert filter has been applied!\n";
}

/* It takes the average of the three colors and store it in a gray scaled 2d matrix */
void Filters::To_grey()
{
    for (int i{}; i < SIZE; ++i)
    {
        for (int j{}; j < SIZE; ++j)
        {
            int avg{};
            for (unsigned short k{}; k < RGB; ++k)
            {
                avg += RGBimage[i][j][k];
            }
            image[i][j] = avg / 3;
        }
    }
}

void Filters::mirror_horizontally()
{
    // simply swap each opposite pixel (about the middle coloumn) in a row
    if (src.isRGB())
    {
        for (int r{}; r < SIZE; ++r)
        {
            int i{}, j{SIZE - 1};
            while (i < j)
            {
                swap(RGBimage[r][i++], RGBimage[r][j--]);
            }
        }
    }
    else
    {
        for (int r{}; r < SIZE; ++r)
        {
            int i{}, j{SIZE - 1};
            while (i < j)
            {
                swap(image[r][i++], image[r][j--]);
            }
        }
    }
}
void Filters::mirror_vertically()
{
    // simply swap each opposite pixel (about the middle row) in a coloumn
    if (src.isRGB())
    {
        for (int c{}; c < SIZE; ++c)
        {
            int i{}, j{SIZE - 1};
            while (i < j)
            {
                swap(RGBimage[i++][c], RGBimage[j--][c]);
            }
        }
    }
    else
    {
        for (int c{}; c < SIZE; ++c)
        {
            int i{}, j{SIZE - 1};
            while (i < j)
            {
                swap(image[i++][c], image[j--][c]);
            }
        }
    }
}
void Filters::flip()
{
    char selection{};
    cout << "Flip (H/h)orizontally or (V/v)ertically? ";
    cin >> selection;
    selection = toupper(selection);
    while (selection != 'H' && selection != 'V')
    {
        cout << "Please enter a valid character! ";
        cin >> selection;
    }
    if (selection == 'H')
    {
        mirror_horizontally();
        cout << "Image has been flipped horizontally!\n";
    }
    else
    {
        mirror_vertically();
        cout << "Image has been flipped vertically!\n";
    }
}
void Filters::rotate()
{
    int degree{}, n{};
    cout << "Rotate (90), (180), (270) or (360) degrees? ";
    cin >> degree;
    while (degree != 90 && degree != 180 && degree != 270 && degree != 360)
    {
        cout << "\nInvalide input";
        cout << "\nPlease Select from the given degrees (90), (180), (270), (360): ";
        cin >> degree;
    }
    if (degree == 90){
        n = 1;
    }
    else if (degree == 180){
        n = 2;
    }else if (degree == 270){
        n = 3;
    }
    if (src.isRGB()){
        for (int s = 0; s < n; s++)
        {
            for (int i = 0; i < SIZE-i-1; i++){
                for (int j = i; j < SIZE-i-1; j++){
                    for (int k = 0; k < 3; k++)
                    {
                        swap(RGBimage[i][j][k], RGBimage[j][SIZE-1-i][k]);
                        swap(RGBimage[i][j][k], RGBimage[SIZE-1-i][SIZE-1-j][k]);
                        swap(RGBimage[i][j][k], RGBimage[SIZE-1-j][i][k]);
                    }
                }
            }
        }
    }else{
        for (int s = 0; s < n; s++){
            for (int i = 0; i < SIZE-i-1; i++){
                for (int j = i; j < SIZE-i-1; j++){
                    swap(image[i][j], image[j][SIZE-1-i]);
                    swap(image[i][j], image[SIZE-1-i][SIZE-1-j]);
                    swap(image[i][j], image[SIZE-1-j][i]);
                }
            }
        }
    }
}
/*
    This Function detects the  objects' edges by comparing values of the pixels, if a certain pixel exceeds a certain value (45)
    then then such pixel must belong to another object in the image thus the pixel before it will be blacked representing an edge

    Firstly we store the value of the first pixel in a row then we compare the next pixels with that value if one pixel differs from
    the initial pixel value by 45 otherwise the pixel will be white.
    If there exists a pixel differs from the stored value by 45, we store the value of that pixel then the pixel before it will be colored in black.
    such image will be stored in a matrix denoted as horizontal -as the algorith move horizontally- so far, we only detected non-horizontal edges.

    So, we repeat the same process but coloumn by coloumn storing the val of the first pixel in the coloumn then we compare it with the rest and so on.
    That process will be stored in another matrix named vertical; as the algorithm moved vertically and detects any non vertical edges

    finally we compare both horizontal matrix and vertical matrix and store the minimum value of each corresponding pixel which indicates an edge
    in the original image
    by such method we made sure to detect both vertical and horizontal edges
*/

void Filters::Lining()
{
    unsigned char hori[SIZE][SIZE];
    unsigned char verti[SIZE][SIZE];
    if (src.isRGB())
    {
        To_grey();
    }
    // Black_White();
    for (int i{}; i < SIZE; ++i)
    {
        for (int j{}; j < SIZE; ++j)
        {
            hori[i][j] = verti[i][j] = image[i][j];
        }
    }
    for (int r{}; r < SIZE; ++r)
    {
        int initial{}, j{};
        initial = hori[r][j++];
        while (j < SIZE)
        {
            if (abs(hori[r][j] - initial) > 45) //&& abs(hori[r][j] - image[r][j - 1]) > 40)
            {
                hori[r][j - 1] = 0;
                initial = hori[r][j];
            }
            else
            {
                hori[r][j] = 255;
            }
            j++;
        }
    }
    for (int c{}; c < SIZE; ++c)
    {
        int initial{}, i{};
        initial = verti[i++][c];
        while (i < SIZE)
        {
            if (abs(verti[i][c] - initial) > 45) // && abs(verti[i][c] - image[i - 1][c]) > 40)
            {
                verti[i - 1][c] = 0;
                initial = verti[i][c];
            }
            else
            {
                verti[i][c] = 255;
            }
            i++;
        }
    }
    for (int i{}; i < SIZE; ++i)
    {
        for (int j{}; j < SIZE; ++j)
        {
            image[i][j] = min(hori[i][j], verti[i][j]);
        }
    }
    for (int i{}; i < SIZE; ++i)
    {
        bool first_row{i == 0}, last_row{i == SIZE - 1};
        for (int j{}; j < SIZE; ++j)
        {
            if (image[i][j] != 255)
            {
                if (!(last_row || first_row))
                {
                    if (j == 0)
                    {
                        if ((image[i - 1][j] + image[i - 1][j + 1] + image[i][j + 1] + image[i + 1][j] + image[i + 1][j + 1]) / 5 >= (255 * 4) / 5)
                            image[i][j] = 255;
                    }
                    else if (j == SIZE - 1)
                    {
                        if ((image[i - 1][j] + image[i - 1][j - 1] + image[i][j - 1] + image[i + 1][j] + image[i + 1][j - 1]) / 5 >= (255 * 4) / 5)
                            image[i][j] = 255;
                    }
                    else
                    {
                        if ((image[i][j + 1] + image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1] + image[i - 1][j + 1] + image[i + 1][j] + image[i + 1][j - 1] + image[i + 1][j + 1]) / 8 >= (7 * 255) / 8)
                            image[i][j] = 255;
                    }
                }
                else
                {
                    if (j == 0)
                    {
                        if ((image[i][j + 1] + image[i - last_row + first_row][j] + image[i - last_row + first_row][j + 1]) / 3 == (2 * 255) / 3)
                            image[i][j] = 255;
                    }
                    else if (j == SIZE - 1)
                    {
                        if ((image[i][j - 1] + image[i - last_row + first_row][j] + image[i - last_row + first_row][j - 1]) / 3 == (2 * 255) / 3)
                            image[i][j] = 255;
                    }
                    else
                    {
                        if ((image[i][j + 1] + image[i][j - 1] + image[i - last_row + first_row][j] + image[i - last_row + first_row][j - 1] + image[i - last_row + first_row][j + 1]) / 5 == (4 * 255) / 5)
                            image[i][j] = 255;
                    }
                }
            }
        }
    }
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    if (image[i][j] == 255)
                    {
                        RGBimage[i][j][k] = 255;
                    }
                }
            }
        }
    }
    printf("Egde detection has been applied\n");
}



/*
    The user inputs the coordinates of the starting position of the part s/he wishes to crop then the user will enter lenght and width of such part
    Having known the coordinates and the dimensions this function whites out any pixel beyond the boundaries of the given dimensions and positions 
*/
void Filters::crop()
{
    int x{}, y{}, l{}, w{};
    cout << "Specify the starting position of the cropped photo: ";
    cin >> x >> y;
    while (abs(x) > 256 || !x || abs(y) > 256 || !y)
    {
        cout << "\nSorry! You must enter a valid position not exceeding (256,256) and not less than (1,1): ";
        cin >> x >> y;
    }
    cout << "Enter the length and the width of the cropped photo: ";
    cin >> l >> w;
    while (x + l > 256 || y + w > 256)
    {
        cout << "\nSorry! The Dimensions given are off bounds of the original photo!\n";
        cout << "Max Length: " << 256 - x << "  Max Width: " << 256 - y << endl;
        cin >> l >> w;
    }
    x--, y--, l--, w--;
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                if (!(i >= x && j <= y + l && j >= y && i <= x + w))
                {
                    for (unsigned short k{}; k < 3; ++k)
                    {
                        RGBimage[i][j][k] = 255;
                    }
                }
            }
        }
    }
    else
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                if (!(i >= x && j <= y + l && j >= y && i <= x + w))
                    image[i][j] = 255;
            }
        }
    }
}

/*
    average of surrounding pixels gives us the blurred pixel
*/
void Filters::blur()
{
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            bool first_row{i == 0}, last_row{i == SIZE - 1};
            for (int j{}; j < SIZE; ++j)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    if (!(last_row || first_row))
                    {
                        if (j == 0)
                        {
                            rgbimage2[i][j][k] = (RGBimage[i][j][k] + RGBimage[i][j + 1][k] + RGBimage[i - 1][j][k] + RGBimage[i - 1][j + 1][k] + RGBimage[i + 1][j][k] + RGBimage[i + 1][j + 1][k]) / 6;
                        }
                        else if (j == SIZE - 1)
                        {
                            rgbimage2[i][j][k] = (RGBimage[i][j][k] + RGBimage[i][j - 1][k] + RGBimage[i - 1][j][k] + RGBimage[i - 1][j - 1][k] + RGBimage[i + 1][j][k] + RGBimage[i + 1][j - 1][k]) / 6;
                        }
                        else
                        {
                            rgbimage2[i][j][k] = (RGBimage[i][j][k] + RGBimage[i][j + 1][k] + RGBimage[i][j - 1][k] + RGBimage[i - 1][j][k] + RGBimage[i - 1][j - 1][k] + RGBimage[i - 1][j + 1][k] + RGBimage[i + 1][j][k] + RGBimage[i + 1][j - 1][k] + RGBimage[i + 1][j + 1][k]) / 9;
                        }
                    }
                    else
                    {
                        if (j == 0)
                        {
                            rgbimage2[i][j][k] = (RGBimage[i][j][k] + RGBimage[i][j + 1][k] + RGBimage[i - last_row + first_row][j][k] + RGBimage[i - last_row + first_row][j + 1][k]) / 4;
                        }
                        else if (j == SIZE - 1)
                        {
                            rgbimage2[i][j][k] = (RGBimage[i][j][k] + RGBimage[i][j - 1][k] + RGBimage[i - last_row + first_row][j][k] + RGBimage[i - last_row + first_row][j - 1][k]) / 4;
                        }
                        else
                        {
                            rgbimage2[i][j][k] = (RGBimage[i][j][k] + RGBimage[i][j + 1][k] + RGBimage[i][j - 1][k] + RGBimage[i - last_row + first_row][j][k] + RGBimage[i - last_row + first_row][j - 1][k] + RGBimage[i - last_row + first_row][j + 1][k]) / 6;
                        }
                    }
                }
            }
        }
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    RGBimage[i][j][k] = rgbimage2[i][j][k];
                }
            }
        }
    }
    else
    {
        for (int i{}; i < SIZE; ++i)
        {
            bool first_row{i == 0}, last_row{i == SIZE - 1};
            for (int j{}; j < SIZE; ++j)
            {
                if (!(last_row || first_row))
                {
                    if (j == 0)
                    {
                        image2[i][j] = (image[i][j] + image[i][j + 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i + 1][j] + image[i + 1][j + 1]) / 6;
                    }
                    else if (j == SIZE - 1)
                    {
                        image2[i][j] = (image[i][j] + image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1] + image[i + 1][j] + image[i + 1][j - 1]) / 6;
                    }
                    else
                    {
                        image2[i][j] = (image[i][j] + image[i][j + 1] + image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1] + image[i - 1][j + 1] + image[i + 1][j] + image[i + 1][j - 1] + image[i + 1][j + 1]) / 9;
                    }
                }
                else
                {
                    if (j == 0)
                    {
                        image2[i][j] = (image[i][j] + image[i][j + 1] + image[i - last_row + first_row][j] + image[i - last_row + first_row][j + 1]) / 4;
                    }
                    else if (j == SIZE - 1)
                    {
                        image2[i][j] = (image[i][j] + image[i][j - 1] + image[i - last_row + first_row][j] + image[i - last_row + first_row][j - 1]) / 4;
                    }
                    else
                    {
                        image2[i][j] = (image[i][j] + image[i][j + 1] + image[i][j - 1] + image[i - last_row + first_row][j] + image[i - last_row + first_row][j - 1] + image[i - last_row + first_row][j + 1]) / 6;
                    }
                }
            }
        }
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                image[i][j] = image2[i][j];
            }
        }
    }
}


//to lighten image add to it half its value
//if the result is more than 255 (white) just make it white

void Filters::lighten()
{
    if (src.isRGB())
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    if ((RGBimage[i][j][k]) * 1.5 < 256)
                    {
                        RGBimage[i][j][k] = (RGBimage[i][j][k]) * 1.5;
                    }
                    else
                    {
                        RGBimage[i][j][k] = 255;
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if ((image[i][j]) * 1.5 < 256)
                {
                    image[i][j] = (image[i][j]) * 1.5; 
                }
                else
                {
                    image[i][j] = 255;
                }
            }
        }
    }
}

//to darken image decrease the pixel value to half its original value
void Filters::darken()
{
    if (src.isRGB())
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    RGBimage[i][j][k] = (RGBimage[i][j][k]) / 2;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = (image[i][j]) / 2; 
            }
        }
    }
}

void Filters::Darken_or_Lighten()
{
    char selection{};
    cout << "Do you want to (D/d)arken or (L/l)ighten the image? ";
    cin >> selection;
    selection = toupper(selection);
    while (selection != 'D' && selection != 'L')
    {
        cout << "\nInvalid selections!!\nPlease enter [D/d] to darken or [L/l] to lighten the image: ";
        cin >> selection;
    }
    (selection == 'L') ? lighten() : darken();
}


// to shrink an image to half of its original size, fit each pixel to half the final image's index
void Filters::shrink_half()
{
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    rgbimage2[i][j][k] = RGBimage[i][j][k];
                    RGBimage[i][j][k] = 255;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (unsigned short k = 0; k < RGB; k++)
                {
                    RGBimage[i / 2][j / 2][k] = rgbimage2[i][j][k];
                }
            }
        }
    }
    else
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                image2[i][j] = image[i][j];
                image[i][j] = 255;
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i / 2][j / 2] = image2[i][j];
            }
        }
    }
}

// to shrink an image to a third of its original size, fit each pixel to third the final image's index
void Filters::shrink_one_third()
{
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    rgbimage2[i][j][k] = RGBimage[i][j][k];
                    RGBimage[i][j][k] = 255;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (unsigned short k = 0; k < RGB; k++)
                {
                    RGBimage[i / 3][j / 3][k] = rgbimage2[i][j][k]; 
                }
            }
        }
    }
    else
    {

        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                image2[i][j] = image[i][j];
                image[i][j] = 255;
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i / 3][j / 3] = image2[i][j];
            }
        }
    }
}

// to shrink an image to a fourth of its original size, fit each pixel to quarter the final image's index
void Filters::shrink_one_fourth()
{
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    rgbimage2[i][j][k] = RGBimage[i][j][k];
                    RGBimage[i][j][k] = 255;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (unsigned short k = 0; k < RGB; k++)
                {
                    RGBimage[i / 4][j / 4][k] = rgbimage2[i][j][k];
                }
            }
        }
    }
    else
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                image2[i][j] = image[i][j];
                image[i][j] = 255;
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i / 4][j / 4] = image2[i][j];
            }
        }
    }
}
void Filters::shrink()
{
    cout << "Shrink to (1/2), (1/3) or (1/4): ";
    string choice{};
    cin >> choice;
    while (choice != "1/2" && choice != "1/3" && choice != "1/4")
    {
        cout << "Please select from the given ratios (1/2), (1/3) or (1/4)!\n";
        cin >> choice;
    }
    if (choice == "1/2")
    {
        shrink_half();
        cout << "Image Shrinked to half!\n";
    }
    else if (choice == "1/3")
    {
        shrink_one_third();
        cout << "Image Shrinked to one third!\n";
    }
    else
    {
        shrink_one_fourth();
        cout << "Image Shrinked to its quarter!\n";
    }
}


/*
    To merge two photos we simply take the average of each corresponding pixel in both images
*/
void Filters::merge()
{
    Image img;
    load2ndimgformerge(img);
    if (img.isRGB() || src.isRGB())
    {
        if (src.isRGB() && img.isRGB())
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    for (unsigned short k{}; k < RGB; ++k)
                    {
                        RGBimage[i][j][k] = (RGBimage[i][j][k] + rgbimage2[i][j][k]) / 2;
                    }
                }
            }
        }
        else if (src.isRGB())
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    for (unsigned short k{}; k < RGB; ++k)
                    {
                        RGBimage[i][j][k] = (RGBimage[i][j][k] + image2[i][j]) / 2;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    for (unsigned short k{}; k < RGB; ++k)
                    {
                        RGBimage[i][j][k] = (rgbimage2[i][j][k] + image[i][j]) / 2;
                    }
                }
            }
            src = img; // since the second image is rgb and source image is gray-scaled then we have to assign properties of the second image to source 
                       //for it to be saved in the rgb matrix
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = (image[i][j] + image2[i][j]) / 2;
            }
        }
    }
}


void Filters::skewH()
{
    double theta;
    cout << "enter angle: ";
    cin >> theta;
    int angle = theta;
    double xtan = ::tan((theta * 22) / (7 * 180));
    double x;
    x = SIZE / (1 + xtan);
    double step = SIZE - x;
    double move = step / SIZE;
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    rgbimage2[i][j][k] = RGBimage[i][j][k];
                    RGBimage[i][j][k] = 255;
                }
            }
        }
        for(int i{}; i < SIZE; ++i)
        {
            for(int j{}; j < SIZE && int(j * (x/SIZE))+(int)step < SIZE; ++j)
            {
                for(unsigned int k{}; k < RGB; ++k)
                {
                    RGBimage[i][int(j * (x/SIZE))+(int)step][k] = rgbimage2[i][j][k];
                }
            }
            step -= move;
        }
    }
    else
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                image2[i][j] = image[i][j];
                image[i][j] = 255;
            }
        }
        for(int i{}; i < SIZE; ++i)
        {
            for(int j{}; j < SIZE && int(j * (x/SIZE))+(int)step < SIZE; ++j)
            {
                image[i][int(j * (x/SIZE))+(int)step] = image2[i][j];
            }
            step -= move;
        }
    }
    cout << "Image skewed " << angle<< " degrees to the right!" << endl;
}
void Filters::skewV()
{
    double theta;
    cout << "enter angle: ";
    cin >> theta;
    int angle = 90 - theta;
    theta = 90 - theta;
    theta= theta*22/(7*180);//convert skew angle to radians
    double xtan = ::tan(theta); //get tan
    double x;
    x = SIZE / (1 + 1/xtan); //the new base for the shrunk image
    double step = SIZE - x; //the step lost due to the new base
    double move = step / SIZE; //how much we need to move for each pixel to fit the entire skewed image
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                for (unsigned short k{}; k < RGB; ++k)
                {
                    rgbimage2[i][j][k] = RGBimage[i][j][k];
                    RGBimage[i][j][k] = 255;
                }
            }
        }
        for(int j{}; j < SIZE; ++j)
        {
            for(int i{}; i < SIZE && int(i * (x/SIZE))+(int)step < SIZE; ++i)
            {
                for(unsigned short k{}; k < RGB; ++k)
                {
                    RGBimage[int(i * (x/SIZE))+(int)step][j][k] = rgbimage2[i][j][k];
                }
            }
            step -= move;
        }
    }
    else
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{}; j < SIZE; ++j)
            {
                image2[i][j] = image[i][j];
                image[i][j] = 255;
            }
        }
        // shrink and shift
        // for (int i = 0; i < SIZE; i++)
        // {
        //     step = ceil(SIZE - x);
        //     for (int j = 0; j < SIZE; j++)
        //     {
        //         image[(i / int(SIZE / x)) + int(step)][j] = image2[i][j];
        //         step -= move;
        //     }
        // }
        for(int j{}; j < SIZE; ++j)
        {
            for(int i{}; i < SIZE && int(i * (x/SIZE))+(int)step < SIZE; ++i)
            {
                image[int(i * (x/SIZE))+(int)step][j] = image2[i][j];
            }
            step -= move;
        }
    }
    cout << "Image skewed " << angle << " degrees upwards!" << endl;
}

bool isValid(int &num)
{
    // checks if the user entered a valid quadrant
    while (num < 1 || num > 4)
    {
        cout << "Invalid Number\n";
        cout << "Please enter a number between 1 and 4\n";
        cin >> num;
    }
    return true;
}

tuple<int, int> quadrantIndices(int n)
{
    // returns two indices s and t which represent the starting index of row and column of the desired quarter
    int s{}, k{};
    if (n == 1)
    {
        s = k = 0;
    }
    else if (n == 2)
    {
        s = 0, k = 127;
    }
    else if (n == 3)
    {
        s = 127, k = 0;
    }
    else
    {
        s = k = 127;
    }
    return make_tuple(s, k);
}

void Filters::shuffle()
{
    int i1{}, i2{}, i3{}, i4{};
    cout << "New order of quarters?\n";
    cin >> i1;
    isValid(i1);
    cin >> i2;
    isValid(i2);
    cin >> i3;
    isValid(i3);
    cin >> i4;
    isValid(i4);

    int s{}, t{};
    if (src.isRGB())
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    rgbimage2[i][j][k] = RGBimage[i][j][k];
                }
            }
        }

        tie(s, t) = quadrantIndices(i1);
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    RGBimage[i][j][k] = rgbimage2[i + s][j + t][k];
                }
            }
        }
        tie(s, t) = quadrantIndices(i2);
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = SIZE / 2; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    RGBimage[i][j][k] = rgbimage2[i + s][j - (SIZE / 2) + t][k];
                }
            }
        }
        tie(s, t) = quadrantIndices(i3);
        for (int i = SIZE / 2; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    RGBimage[i][j][k] = rgbimage2[i - (SIZE / 2) + s][j + t][k];
                }
            }
        }
        tie(s, t) = quadrantIndices(i4);
        for (int i = SIZE / 2; i < SIZE; i++)
        {
            for (int j = SIZE / 2; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    RGBimage[i][j][k] = rgbimage2[i - (SIZE / 2) + s][j - (SIZE / 2) + t][k];
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image2[i][j] = image[i][j];
            }
        }

        int s{}, k{};
        tie(s, k) = quadrantIndices(i1);
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                image[i][j] = image2[i + s][j + k];
            }
        }
        tie(s, k) = quadrantIndices(i2);
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = SIZE / 2; j < SIZE; j++)
            {
                image[i][j] = image2[i + s][j - (SIZE / 2) + k];
            }
        }
        tie(s, k) = quadrantIndices(i3);
        for (int i = SIZE / 2; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                image[i][j] = image2[i - (SIZE / 2) + s][j + k];
            }
        }
        tie(s, k) = quadrantIndices(i4);
        for (int i = SIZE / 2; i < SIZE; i++)
        {
            for (int j = SIZE / 2; j < SIZE; j++)
            {
                image[i][j] = image2[i - (SIZE / 2) + s][j - (SIZE / 2) + k];
            }
        }
    }
}
void Filters::enlarge()
{
    int n{}, s{}, t{};
    while (n != 1 && n != 2 && n != 3 && n != 4)
    {
        cout << "Which quarter to enlarge 1, 2, 3 or 4?\n";
        cin >> n;
    }
    if (n == 1) // checks for desired quadrant to get s and t which represent the starting index of row and column 
    {
        s = t = 0;
    }
    else if (n == 2)
    {
        s = 0, t = 127;
    }
    else if (n == 3)
    {
        s = 127, t = 0;
    }
    else
    {
        s = t = 127;
    }
    if (src.isRGB())
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    rgbimage2[i][j][k] = RGBimage[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE - 1; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    RGBimage[i][j][k] = rgbimage2[(i / 2) + s][(j / 2) + t][k]; // dividing by 2 in order to repeat the previous pixel 
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image2[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE - 1; j++)
            {
                image[i][j] = image2[(i / 2) + s][(j / 2) + t];
            }
        }
    }
}
void Filters::filters_menu(string s)
{
    cout << s + " or select 0 to exit:\n"
         << "1- Black & White Filter \n"
         << "2- Invert Filter\n"
         << "3- Merge Filter \n"
         << "4- Flip Image\n"
         << "5- Darken and Lighten Image \n"
         << "6- Rotate Image \n"
         << "7- Detect edges \n"
         << "8- Enlarge Image\n"
         << "9- Shrink Image\n"
         << "A/a- Mirror half the image\n"
         << "B/b Shuffle Image\n"
         << "C/c- Blur Image\n"
         << "D/d- Crop Image\n"
         << "E/e- Skew Image to the right\n"
         << "F/f- Skew Image upwards\n"
         << "S/s- Save and exit\n"
         << "0- Exit without saving\n";
}

void Filters::filters_program()
{
    cout << "Ahlan ya user ya habibi :)\n";
    Image src;
    while (loadImage())
    {
        cerr << "Such file doesn't exist in the current directory, please make sure to enter an existing image file!\n";
    }
    filters_menu("Please select a filter to apply");
    char choice{};
    while (choice != 'S' && choice != '0')
    {
        cin >> choice;
        choice = toupper(choice);
        switch (choice)
        {
        case '1':
            Black_White();
            cout << "Black and White filter has been applied!\n";
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case '2':
            invertImage();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case '3':
            merge();
            cout << "Merge filter has been applied!\n";
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case '4':
            flip();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case '5':
            Darken_or_Lighten();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case '6':
            rotate();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case '7':
            Lining();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case '8':
            enlarge();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case '9':
            shrink();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case 'A':
            mirror_half();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case 'B':
            shuffle();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case 'C':
            blur();
            cout << "Image has been blurred!\n";
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case 'D':
            crop();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case 'E':
            skewH();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case 'F':
            skewV();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case 'S':
            if (overwrite())
                overwrite_image();
            else
                saveImage();
        case '0':
            cout << "\nProgram Exited!\n";
            break;
        default:
            cout << "\nInvalid input" << endl;
            filters_menu("Please select a filter to apply");
            break;
        }
    }
}

/*
    this function excutes a command on the system's shell/bash to open up the edited photo right before the program terminates
*/
void open_image(char *file)
{
    //checks if the current system is linux or windows as each OS has its own commands
#ifdef __linux__ 
    char command[300]{"xdg-open "};
    strcat(command, get_current_dir_name());
    strcat(command, "/");
    strcat(command, file);
    system(command);
#elif _Win32
    char command[300]{"start "};
    strcat(command, get_current_dir_name());
    strcat(command, "/");
    strcat(command, file);
    system(command);
#endif
}
bool overwrite()
{
    char selection{};
    cout << "Would you like to overwrite the image [Y/n]? ";
    cin >> selection;
    selection = toupper(selection);
    while (selection != 'Y' && selection != 'N')
    {
        cout << "\nplease enter y/Y or n/N: ";
        cin >> selection;
        selection = toupper(selection);
        cout << '\n';
    }
    return selection == 'y' || selection == 'Y';
}
void overwrite_image()
{
    if (src.isRGB())
    {
        writeRGBBMP(src.get_name(), RGBimage);
    }
    else
    {
        writeGSBMP(src.get_name(), image);
    }
    open_image(src.get_name());
}

int loadImage()
{
    cout << "Enter the source image file name: ";
    src.set_name();
    if (!src.isValid())
    {
        return 1;
    }
    if (src.isRGB())
        return readRGBBMP(src.get_name(), RGBimage);
    else
        return readGSBMP(src.get_name(), image);
}

int load2ndimgformerge(Image &photo)
{
    cout << "Enter the second image file name: ";
    photo.set_name();
    if (!photo.isValid())
    {
        return 1;
    }
    if (photo.isRGB())
        return readRGBBMP(photo.get_name(), rgbimage2);
    else
        return readGSBMP(photo.get_name(), image2);
}

void saveImage()
{
    Image target_image;
    cout << "Enter the target image file name: ";
    target_image.set_name();
    if (src.isRGB())
        writeRGBBMP(target_image.get_name(), RGBimage);
    else
        writeGSBMP(target_image.get_name(), image);

    open_image(target_image.get_name());
}
