#include <fxcg/display.h>
#include <fxcg/keyboard.h>

int main()
{
    Bdisp_AllClr_VRAM();
    Print_OS("Press EXE to exit", 0, 0);

    while (true)
    {
        int key;
        GetKey(&key);

        if (key == KEY_CTRL_EXE) {
            break;
        }
    }

    return 0;
}
