#include <3ds.h>
#include <citro2d.h>
#include "boxes.h"
#include "scene.h"

static inline void init() {
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    
    
}

static inline void deinit() {
    C2D_Fini();
    C3D_Fini();
    gfxExit();
}

int main(int argc, char* argv[]) {
    init();
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    char retstring[11];
    double cnt = -10;
    int ret = 0;
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) {
            break;
        }
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(0xFF, 0x00, 0x00, 0xFF));
        C2D_SceneBegin(top);
        if (cnt > 0 && cnt < 30) {
            ret = drawTextBox("Hello I love food\nSussy\nb\naaa", cnt);
        }
        cnt += 0.05f;
        sprintf(retstring, "%f", cnt);
        drawText(0,0,0,1,C2D_Color32(0x00, 0x00, 0x00, 0xFF), retstring);
        C3D_FrameEnd(0);
    }
    deinit();
    return 0;
}