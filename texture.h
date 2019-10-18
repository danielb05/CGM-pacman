/*
10/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 3 - Pacman 3D graphics and texture implementation
Students:
Daniel Vieira Cordeiro
Rafael C�mara Pereira
*/

#pragma once

#include "constants.h"

class Texture
{
    public:
        void ReadJPEG(char *filename, unsigned char **image, int *width, int *height);
        void LoadTexture(char *filename, int dim);  

};
