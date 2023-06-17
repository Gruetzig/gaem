#include "boxes.h"

#define SCREEN_WIDTH_TOP 400
#define SCREEN_WIDTH_BOTTOM 320
#define SCREEN_HEIGHT_TOP 240
#define SCREEN_HEIGHT_BOTTOM 240

char textstr[4][100];


int fillTextIntoString(char* text) {
    int cnt = 0;
    char* pch;
    const char* delim = "\n";
    pch = strtok(text, delim);
    while (pch != NULL) {
        memset(textstr[cnt], 0x00, 100);
        snprintf(textstr[cnt], 100, "%s", pch);
        if (cnt > 4) {
            return -1; //too many lines for message, max 4
        } else {
            cnt++;
        }
        pch = strtok(NULL, delim);
    }
    return cnt;

}

//box will take up 1/4th of the screen
int drawTextBox(char *_text, int progress) {
    //draw box and outline
    C2D_DrawRectSolid(
        0,
        SCREEN_HEIGHT_TOP*3/4, 
        0,
        SCREEN_WIDTH_TOP,
        SCREEN_HEIGHT_TOP*1/4,
        C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF)
    );
    C2D_DrawRectSolid(
        0+1,
        SCREEN_HEIGHT_TOP*3/4+1, 
        0,
        SCREEN_WIDTH_TOP-2,
        SCREEN_HEIGHT_TOP*1/4-2,
        C2D_Color32(0x00, 0xFF, 0xFF, 0xFF)
    );
    char text[strlen(_text)+1];
    strncpy(text, _text, progress);
    int len = fillTextIntoString(text);
    if (len > 0) {
        for (int i=0;i<len;i++) {
            drawText(
                20,
                SCREEN_HEIGHT_TOP*3/4+(i*15), 
                0.0f, 0.5f, 
                C2D_Color32(0x00, 0x00, 0x00, 0xFF), 
                textstr[i]
            );
        }
        return len;
    } else {
        return len;
    }

    return 0;//will never happen
}