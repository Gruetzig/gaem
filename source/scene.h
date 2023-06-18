#include <citro2d.h>
#include "ui.h"

typedef struct CharacterList {
    int characternum;
    int x;
    float scale;
    struct CharacterList *next;
} CharacterList;

void loadSceneAssets();
void freeSceneAssets();
void drawScene(size_t bg, CharacterList *characters, int characterSize);