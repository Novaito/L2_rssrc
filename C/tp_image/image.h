#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#define LENMAXFILE_TITLE 20
#define MAXCOLOR 255


typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} pixel;

typedef struct {
    pixel **tab;
    int sizeX;
    int sizeY;
} image;

FILE * openFile();
FILE * makeFile(image *img);
void initTable(image *img, int sizeX, int sizeY);
void copyTable(image *imgInit, image *imgInput);
void initBlurTable(image *img, image *imgB, int px);
void setSizeImage(image *img, int sizeX, int sizeY);
void setPixel(image *img, int x, int y, int r, int g, int b);
void injectColorImg(FILE * fp, image *img, int x, int y);
void makeUnicolorImage(FILE * fp, image *img);
void lreturn(FILE * fp);
void putBlackSquare(FILE * fp, image *img);
void getReadFile(FILE * fp, image *img);
void printRGBData(image *img);
void fillImg(FILE * fp, image *img);
void keepRedValue(FILE * fp, image *img);
void keepGreenValue(FILE * fp, image *img);
void keepBlueValue(FILE * fp, image *img);
int getAvgGrey(image *img, int x, int y);
void AVGgreyPattern(FILE * fp, image *img);
int getMaxGrey(image *img, int x, int y);
void MAXgreyPattern(FILE * fp, image *img);
void sepiaPatternTest(FILE * fp, image *img);
void sepiaBlueTint(FILE * fp, image *img);
void BlueWhiteEffect(FILE * fp, image *img);
FILE * blurImage(image *img, int px);
void windowAvg(image *img, int x, int y, int px);

#endif // IMAGE_H_INCLUDED
