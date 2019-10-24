/*
10/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 4 - Inclusion of lighting effects to the game
Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira
*/

#pragma once

#include "constants.h"

class Texture
{
    public:
        void ReadJPEG(char *filename, unsigned char **image, int *width, int *height);
        void LoadTexture(char *filename, int dim);  

};
