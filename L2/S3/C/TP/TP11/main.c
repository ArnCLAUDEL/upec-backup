#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "image.h"
    
    // Description du type

int main () {
 image* img2 = load_image_P2("im_P2"); ascii_print(img2,G," .*&&#");
 crop(img2,1,1,4,21);ascii_print(img2,G," .*&&#");
//	image* img3 = load_image_P3("im_P3"); ascii_print(img3,G," .-+=*&#");free(img3);
//	image* img1 = load_image_P1("im_P1"); ascii_print(img1,G," .-+=*&#");
//	image* img4 = load_image_P4("im_P4"); //ascii_print(img4,G," .-+=*&#");free(img4);
  return EXIT_SUCCESS;
}
