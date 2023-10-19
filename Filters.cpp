#include "Filters.h"

using namespace std;

Image src;
unsigned char image[SIZE][SIZE];
unsigned char RGBimage[SIZE][SIZE][RGB];
unsigned char rgbimage2[SIZE][SIZE][3];
unsigned char image2[SIZE][SIZE];

void Filters::mirror_l_r()
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

void Filters::mirror_r_l()
{
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; ++i)
        {
            for (int j{SIZE / 2 - 1}, j2{SIZE / 2}; j >= 0 && j2 < SIZE; --j, j2++)
            {
                for (unsigned short k{}; k < 3; ++k)
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

void Filters::mirror_u_d()
{
    if (src.isRGB())
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int i{SIZE / 2 - 1}, i2{SIZE / 2}; i >= 0 && i2 < SIZE; --i, i2++)
            {
                for (unsigned short k{}; k < 3; ++k)
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

void Filters::mirror_d_u()
{
    if (src.isRGB())
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int i{SIZE / 2 - 1}, i2{SIZE / 2}; i >= 0 && i2 < SIZE; --i, i2++)
            {
                for (unsigned short k{}; k < 3; ++k)
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
        mirror_u_d();
        break;
    case 2:
        mirror_d_u();
        break;
    case 3:
        mirror_r_l();
        break;
    case 4:
        mirror_l_r();
        break;
    }
}

void Filters::rotate_90_deg()
{
    int i{}, j{SIZE - 1};
    while (i < j)
    {
        for (int x = i; x < j; ++x)
        {
            swap(image[i][x], image[x][j]);
            swap(image[i][x], image[j][j - x + i]);
            swap(image[i][x], image[j - x + i][i]);
        }
        i++, j--;
    }
}
void Filters::rotate_180_deg()
{
    int rows{};
    while (rows < SIZE / 2)
    {
        int coloumns{};
        while (coloumns < SIZE)
        {
            swap(image[rows][coloumns], image[SIZE - 1 - rows][SIZE - 1 - coloumns]);
            coloumns++;
        }
        rows++;
    }
}
void Filters::rotate_270_deg()
{
    int i{}, j{SIZE - 1};
    while (i < j)
    {
        for (int x = j; x > i; --x)
        {
            swap(image[i][x], image[j - x + i][i]);
            swap(image[i][x], image[j][j - x + i]);
            swap(image[i][x], image[x][j]);
        }
        i++, j--;
    }
}
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
    if (src.isRGB())
    {
        for (int i{}; i < SIZE; i++)
        {
            for (int j{}; j < SIZE; j++)
            {
                for (unsigned short k{}; k < 3; ++k)
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
    int degree{};
    cout << "Rotate (90), (180), (270) or (360) degrees? ";
    cin >> degree;
    while (degree != 90 && degree != 180 && degree != 270 && degree != 360)
    {
        cout << "\nInvalide input";
        cout << "\nPlease Select from the given degrees (90), (180), (270), (360): ";
        cin >> degree;
    }
    switch (degree)
    {
    case 90:
        rotate_90_deg();
        cout << "Image rotated 90 degrees clockwise!\n";
        break;
    case 180:
        rotate_180_deg();
        cout << "Image rotated 180 degrees clockwise!\n";
        break;
    case 270:
        rotate_270_deg();
        cout << "Image rotated 270 degrees clockwise!\n";
        break;
    default:
        cout << "Image rotated 360 degrees clockwise!\n";
        break;
    }
}
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
                for (unsigned short k{}; k < 3; ++k)
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
void Filters::blur()
{
    unsigned char copy[SIZE][SIZE];
    for (int i{}; i < SIZE; ++i)
    {
        bool first_row{i == 0}, last_row{i == SIZE - 1};
        for (int j{}; j < SIZE; ++j)
        {
            if (!(last_row || first_row))
            {
                if (j == 0)
                {
                    copy[i][j] = (image[i][j] + image[i][j + 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i + 1][j] + image[i + 1][j + 1]) / 6;
                }
                else if (j == SIZE - 1)
                {
                    copy[i][j] = (image[i][j] + image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1] + image[i + 1][j] + image[i + 1][j - 1]) / 6;
                }
                else
                {
                    copy[i][j] = (image[i][j] + image[i][j + 1] + image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1] + image[i - 1][j + 1] + image[i + 1][j] + image[i + 1][j - 1] + image[i + 1][j + 1]) / 9;
                }
            }
            else
            {
                if (j == 0)
                {
                    copy[i][j] = (image[i][j] + image[i][j + 1] + image[i - last_row + first_row][j] + image[i - last_row + first_row][j + 1]) / 4;
                }
                else if (j == SIZE - 1)
                {
                    copy[i][j] = (image[i][j] + image[i][j - 1] + image[i - last_row + first_row][j] + image[i - last_row + first_row][j - 1]) / 4;
                }
                else
                {
                    copy[i][j] = (image[i][j] + image[i][j + 1] + image[i][j - 1] + image[i - last_row + first_row][j] + image[i - last_row + first_row][j - 1] + image[i - last_row + first_row][j + 1]) / 6;
                }
            }
        }
    }
    for (int i{}; i < SIZE; ++i)
    {
        for (int j{}; j < SIZE; ++j)
        {
            image[i][j] = copy[i][j];
        }
    }
}
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
void Filters::shrink_half()
{
    if (src.isRGB())
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (unsigned k = 0; k < RGB; k++)
                {
                    RGBimage[i / 2][j / 2][k] = RGBimage[i][j][k];
                }
            }
        }
    }
    else
    {
    }
}
void Filters::shrink_one_third()
{
    if (src.isRGB())
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (unsigned short k = 0; k < RGB; k++)
                {
                    RGBimage[i / 3][j / 3][k / 3] = RGBimage[i][j][k];
                }
            }
        }
    }
    else
    {
        // for (int i = 0; i < SIZE; i++)
        // {
        //     for (int j = 0; j < SIZE; j++)
        //     {
        //         image[i / 3][j / 3][k / 3] = RGBimage[i][j][k];
        //     }
        // }
    }
}
void Filters::shrink_one_fourth()
{
    if (src.isRGB())
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (unsigned short k = 0; k < RGB; k++)
                {
                    RGBimage[i / 4][j / 4][k / 4] = RGBimage[i][j][k];
                }
            }
        }
    }
    else
    {
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
                    for (unsigned short k{}; k < 3; ++k)
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
                    for (unsigned short k{}; k < 3; ++k)
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
                    for (unsigned short k{}; k < 3; ++k)
                    {
                        RGBimage[i][j][k] = (rgbimage2[i][j][k] + image[i][j]) / 2;
                    }
                }
            }
            src = img; // since the second image is rgb and first image is gray-scaled then we have to assign properties of second image to source for it save it in rgb matrix
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
    if(src.isRGB())
    {

    }
    else
    {

    }
}
void Filters::skewV()
{
    if(src.isRGB())
    {

    }
    else
    {

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
         << "S/s- To save and exit\n"
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
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case '9':
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case 'A':
            mirror_half();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case 'B':
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
            skewV();
            filters_menu("Select another filter you wish to apply to the same modified image");
            break;
        case 'F':
            skewH();
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
void open_image(char *file)
{

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
