#pragma once
#include <fstream>
#include <cstdlib>
#include <utility>
#include "bmplib.cpp"
#include "Image.cpp"

class Filters
{
private:
    static void mirror_r_l();
    static void mirror_l_r();
    static void mirror_u_d();
    static void mirror_d_u();
    static void mirror_vertically();
    static void mirror_horizontally();
    static void rotate_90_deg();
    static void rotate_180_deg();
    static void rotate_270_deg();
    static void rotate();
    static void merge();
    static void Black_White();
    static void invertImage();
    static void flip();
    static void To_grey();
    static void Lining();
    static void mirror_half();
    static void crop();
    static void blur();
    static void darken();
    static void lighten();
    static void shrink_half();
    static void shrink_one_third();
    static void shrink_one_fourth();
    static void shrink();
    static void Darken_or_Lighten();
    static void skewV();
    static void skewH();
    static void filters_menu(string s);
public:
    static void filters_program();
};
