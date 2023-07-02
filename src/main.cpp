#include <iostream>
#include "window.h"

int main(int, char**){
    window w("webgpu test", 640, 480, false, true);

    while (!w.Update()){

    }
    return 0;
}