#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

void printRGBData(image *img) {
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            printf("(%d, %d, %d) | ", img->tab[y][x].r, img->tab[y][x].g, img->tab[y][x].b);
        }
        printf("\n");
    }
}

void lreturn(FILE * fp) {
    fprintf(fp, "\n");
}

void initTable(image *img, int sizeX, int sizeY) {
    setSizeImage(img, sizeX, sizeY);
    img->tab = (pixel **)malloc(sizeof(pixel *) * img->sizeY);
    for (int y=0; y<img->sizeY; y++) {
        img->tab[y] = (pixel *)malloc(sizeof(pixel) * img->sizeX);
    }
}

void copyTable(image *imgInit, image *imgInput) {
    for (int y=0; y<imgInit->sizeY; y++) {
        for (int x=0; x<imgInit->sizeX; x++) {
            imgInput->tab[y][x].r = imgInit->tab[y][x].r;
            imgInput->tab[y][x].g = imgInit->tab[y][x].g;
            imgInput->tab[y][x].b = imgInit->tab[y][x].b;
        }
    }
}

FILE * makeFile(image *img) {
    char *filename = (char *)malloc(sizeof(char) * LENMAXFILE_TITLE);
    FILE * fp;
    printf("Entrez le nom du fichier (hors extension) : ");
    scanf("%s", filename);
    strcat(filename, ".ppm");
    fp = fopen(filename, "w");
    free(filename);
    fprintf(fp, "P3\n%d %d\n%d\n", img->sizeX, img->sizeY, MAXCOLOR);
    return fp;
}

FILE * openFile() {
    char *filename = (char *)malloc(sizeof(char) * MAXCOLOR);
    printf("Entrer le nom du fichier (avec extension) : ");
    scanf("%s", filename);
    FILE * fp;
    fp = fopen(filename, "r");
    free(filename);
    if (fp == NULL) {
        printf("- Open file error : %s -", filename);
        exit(EXIT_FAILURE);
    } else {
        printf("\n       *** File loaded ! ***\n");
        return fp;
    }
}

void getReadFile(FILE * fp, image *img) {
    char magicNumber[2], sizeX[8], sizeY[8], color[8], r[8], g[8], b[8];
    int red, green, blue;
    int x=0, y=0;
    fscanf(fp, "%s", magicNumber);
    fscanf(fp, "%s %s", sizeX, sizeY);
    fscanf(fp, "%s", color);
    initTable(img, strtol(sizeX, NULL, 10), strtol(sizeY, NULL, 10));
    printf("    *** Header collected ! ***\n\n");
    printf(" !! [ Image Width : %d ] [Image Height : %d ] !!\n", img->sizeX, img->sizeY);
    while (!feof(fp) && (y<img->sizeY)) {
        fscanf(fp, "%s", r);
        fscanf(fp, "%s", g);
        fscanf(fp, "%s", b);
        red = strtol(r, NULL, 10);
        green = strtol(g, NULL, 10);
        blue = strtol(b, NULL, 10);
        setPixel(img, x, y, red, green, blue);
        if (x==img->sizeX-1) {
            x=0;
            y++;
        }
        else x++;
    }
}

void setSizeImage(image *img, int sizeX, int sizeY) {
    img->sizeX = sizeX;
    img->sizeY = sizeY;
}

void setPixel(image *img, int x, int y , int r, int g, int b) {
    img->tab[y][x].r = r;
    img->tab[y][x].g = g;
    img->tab[y][x].b = b;
}

void injectColorImg(FILE * fp, image *img, int x, int y) {
    fprintf(fp, "%d %d %d ", img->tab[y][x].r, img->tab[y][x].g, img->tab[y][x].b);
}

void makeUnicolorImage(FILE * fp, image *img) {
    int r, g, b;
    printf("Entrer la valeur r g b : ");
    scanf("%d %d %d", &r, &g, &b);
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            setPixel(img, x, y, r, g, b);
            injectColorImg(fp, img, x, y);
        }
        lreturn(fp);
    }
}

void fillImg(FILE * fp, image *img) {
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            fprintf(fp, "%d %d %d ", img->tab[y][x].r, img->tab[y][x].g, img->tab[y][x].b);
        }
        lreturn(fp);
    }
}

void putBlackSquare(FILE *fp, image *img) {
    for (int y=img->sizeY/4; y < 3*img->sizeY/4; y++) {
        for (int x=img->sizeX/4; x < 3*img->sizeX/4; x++) {
            setPixel(img, x, y, 0, 0, 0);
        }
    }
    fillImg(fp, img);
}

void keepRedValue(FILE * fp, image *img) {
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            img->tab[y][x].g = 0;
            img->tab[y][x].b = 0;
        }
    }
    fillImg(fp, img);
}

void keepGreenValue(FILE * fp, image *img) {
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            img->tab[y][x].r = 0;
            img->tab[y][x].b = 0;
        }
    }
    fillImg(fp, img);
}

void keepBlueValue(FILE * fp, image *img) {
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            img->tab[y][x].r = 0;
            img->tab[y][x].g = 0;
        }
    }
    fillImg(fp, img);
}

int getAvgGrey(image *img, int x, int y) {
    return (img->tab[y][x].r + img->tab[y][x].g + img->tab[y][x].b) / 3;
}

void AVGgreyPattern(FILE * fp, image *img) {
    int avg;
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            avg = getAvgGrey(img, x, y);
            img->tab[y][x].r = avg;
            img->tab[y][x].g = avg;
            img->tab[y][x].b = avg;
        }
    }
    fillImg(fp, img);
}

int getMaxGrey(image *img, int x, int y) {
    int max;
    if (img->tab[y][x].g > img->tab[y][x].r) {
        if (img->tab[y][x].b > img->tab[y][x].g) {
            max = img->tab[y][x].b;
        } else {
            max = img->tab[y][x].g;
        }
    } else {
        max = img->tab[y][x].r;
    }
    return max;
}

void MAXgreyPattern(FILE * fp, image *img) {
    int max;
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            max = getMaxGrey(img, x, y);
            img->tab[y][x].r = max;
            img->tab[y][x].g = max;
            img->tab[y][x].b = max;
        }
    }
    fillImg(fp, img);
}

void sepiaPatternTest(FILE * fp, image *img) {
    int RGavg, max;
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            RGavg = (img->tab[y][x].r + img->tab[y][x].g) * 0.4;
            max = getMaxGrey(img, x, y);
            img->tab[y][x].r = max*0.7;
            img->tab[y][x].g = max*0.7;
            img->tab[y][x].b = RGavg*0.4;
        }
    }
    fillImg(fp, img);
}

void sepiaBlueTint(FILE * fp, image *img) {
    int RGavg, max;
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            RGavg = (img->tab[y][x].r + img->tab[y][x].g) / 3;
            max = getMaxGrey(img, x, y);
            img->tab[y][x].r = RGavg;
            img->tab[y][x].g = RGavg;
            img->tab[y][x].b = max;
        }
    }
    fillImg(fp, img);
}

void BlueWhiteEffect(FILE * fp, image *img) {
    int RGavg, max;
    for (int y=0; y<img->sizeY; y++) {
        for (int x=0; x<img->sizeX; x++) {
            RGavg = (img->tab[y][x].r + img->tab[y][x].g) / 2;
            max = getMaxGrey(img, x, y);
            img->tab[y][x].r = RGavg;
            img->tab[y][x].g = RGavg;
            img->tab[y][x].b = max;
        }
    }
    fillImg(fp, img);
}

void windowAvg(image *img, int x, int y, int px) {
    int avgR=0, avgG=0, avgB=0, nbCase=0;
    for (int j=y-px+1; j<y+px; j++) {
        for (int i=x-px+1; i<x+px; i++) {
            if ((i >= 0 && i < img->sizeX) && (j >= 0 && j < img->sizeY)) {
                avgR += img->tab[j][i].r;
                avgG += img->tab[j][i].g;
                avgB += img->tab[j][i].b;
                nbCase++;
            }
        }
    }
    img->tab[y][x].r = avgR / nbCase;
    img->tab[y][x].g = avgG / nbCase;
    img->tab[y][x].b = avgB / nbCase;
}

FILE * blurImage(image *img, int px) {
    printf("! Concernant le fichier a creer (si le nom est identique au dernier il sera ecrase) !\n");
    image *new_img = (image *)malloc(sizeof(image));
    initTable(new_img, img->sizeX, img->sizeY);
    FILE * fp = makeFile(new_img);
    copyTable(img, new_img);
    for (int y=0; y<new_img->sizeY; y++) {
        for (int x=0; x<new_img->sizeX; x++) {
            windowAvg(new_img, x, y, px);
        }
    }
    fillImg(fp, new_img);
    return fp;
}
