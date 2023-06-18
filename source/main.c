#include <3ds.h>
#include <citro2d.h>
#include "boxes.h"
#include "scene.h"
#include "runner.h"

static inline void init() {
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    prepareNovel();
    
    
}

static inline void deinit() {
    exitNovel();
    C2D_Fini();
    C3D_Fini();
    gfxExit();
}

int main(int argc, char* argv[]) {
    init();
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) {
            break;
        }
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(0xFF, 0x00, 0x00, 0xFF));
        DoStuff(kDown);
        C3D_FrameEnd(0);
    }
    deinit();
    return 0;
}