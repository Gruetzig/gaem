#include "scene.h"

C2D_SpriteSheet spritesheet;

void loadSceneAssets() {
    spritesheet = C2D_SpriteSheetLoad("romfs:/sprites.t3x");
}

void freeSceneAssets() {
    C2D_SpriteSheetFree(spritesheet);
}

void drawScene(size_t bg, CharacterList *characters, int characterSize) {
    C2D_DrawImageAt(C2D_SpriteSheetGetImage(spritesheet, bg), 0, 0, 1, NULL, 1.0f, 1.0f); //bg
    for (float i = 1.0f;i<characterSize+1;i++) {
        C2D_DrawImageAt(C2D_SpriteSheetGetImage(spritesheet, characters->characternum), characters->x, 40, i, NULL, characters->scale, characters->scale);
        if (characters->next != NULL) {
            characters = characters->next;
        } else {
            break;
        }
    }
    
    
}