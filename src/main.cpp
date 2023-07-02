#include "GPU/GPUInstance.h"
#include "window.h"
#include "GPU/GPUSurface.h"
#include "GPU/GPUAdapter.h"

int main(int, char**){
    GPUInstance g_instance;

    window w("webgpu test", 640, 480, false, true);

    GPUSurface g_surface(g_instance, w);

    GPUAdapter g_adapter(g_instance, g_surface);
    g_adapter.inspect();

    while (!w.Update()){

    }

    return 0;
}