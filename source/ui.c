#include "ui.h"

void drawText(float x, float y, float z, float scale, u32 color, const char* value) //ty mechanicaldragon0687
{
    C2D_TextBuf buf=C2D_TextBufNew(4096);
    C2D_Text text;
    C2D_TextParse(&text, buf, value);
    C2D_TextOptimize(&text);
    C2D_DrawText(&text, C2D_WithColor, x, y, z, scale, scale, color);
    C2D_TextBufDelete(buf);
}