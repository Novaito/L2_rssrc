#include <stdio.h>
#include <stdlib.h>

#include "image.h"

int main() {
    image *img = (image *)malloc(sizeof(image));
    /*
    int sizeX, sizeY;
    printf("** Entrer taille image\nWidth : ");
    scanf("%d", &sizeX);
    printf("Height : ");
    scanf("%d", &sizeY);
    initTable(img, sizeX, sizeY);
    FILE * fp = makeFile(MAXCOLOR, img);
    makeUnicolorImage(fp, img);
    fclose(fp);
    printf(" - saved file ! - ");
    */
    FILE * fp = openFile();
    getReadFile(fp, img);
    int pxBlur = 0;
    printf("Entrer le format en px a flouter : ");
    scanf("%d", &pxBlur);
    FILE * nf = blurImage(img, pxBlur);
    //putBlackSquare(nf, img);
    //keepRedValue(nf, img);
    //keepGreenValue(nf, img);
    //keepBlueValue(nf, img);
    //AVGgreyPattern(nf, img);
    //MAXgreyPattern(nf, img);
    //sepiaPatternTest(nf, img);
    //sepiaBlueTint(nf, img);
    //BlueWhiteEffect(nf, img);
    fclose(fp);
    fclose(nf);
    free(img);
    return EXIT_SUCCESS;
}
