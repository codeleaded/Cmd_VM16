#if defined(__linux__)
#include "/home/codeleaded/System/Static/Library/VM16.h"
#include "/home/codeleaded/System/Static/Library/VM16_Assembler.h"
#include "/home/codeleaded/System/Static/Library/VM16_Linker.h"
#include "/home/codeleaded/System/Static/Library/VM16_Devices.h"
#elif defined(_WINE)
#include "/home/codeleaded/System/Static/Library/VM16.h"
#include "/home/codeleaded/System/Static/Library/VM16_Assembler.h"
#include "/home/codeleaded/System/Static/Library/VM16_Linker.h"
#include "/home/codeleaded/System/Static/Library/VM16_Devices.h"
#elif defined(_WIN32)
#include "F:/home/codeleaded/System/Static/Library/VM16.h"
#include "F:/home/codeleaded/System/Static/Library/VM16_Assembler.h"
#include "F:/home/codeleaded/System/Static/Library/VM16_Linker.h"
#include "F:/home/codeleaded/System/Static/Library/VM16_Devices.h"
#elif defined(__APPLE__)
#error "Apple not supported!"
#else
#error "Platform not supported!"
#endif

int main(){
    VM16 vm = VM16_New();
    VM16_ConnectDevice(&vm,(VM16_Ram[]){    VM16_Ram_New(VM16_MEMORY_LOW,   VM16_MEMORY_HIGH)   });
    VM16_ConnectDevice(&vm,(VM16_Kernel[]){ VM16_Kernel_New(VM16_KERNEL_LOW,VM16_KERNEL_HIGH)   });
    VM16_ConnectDevice(&vm,(VM16_TTY[]){    VM16_TTY_New(VM16_TTY_LOW,      VM16_TTY_HIGH)      });
    //VM16_ConnectDevice(&vm,(VM16_MPU[]){    VM16_MPU_New(VM16_MPU_LOW,      VM16_MPU_HIGH)      });
    //VM16_ConnectDevice(&vm,(VM16_DSP[]){    VM16_DSP_New(VM16_DSP_LOW,      VM16_DSP_HIGH)      });
    //VM16_ConnectDevice(&vm,(VM16_GPU[]){    VM16_GPU_New(VM16_GPU_LOW,      VM16_GPU_HIGH)      });
    VM16_ConnectDevice(&vm,(VM16_SSD[]){    VM16_SSD_New(VM16_SSD_LOW,      VM16_SSD_HIGH)      });
    
    VM16_Comp(&vm,"./code/Main.svm16","./asm/Main.lvm16");
    VM16_Comp(&vm,"./code/Lib.svm16","./asm/Lib.lvm16");
    VM16_Link(&vm,VM16_MEMORY_LOW,"_start",(CStr[]){ "./asm/Main.lvm16","./asm/Lib.lvm16",NULL },"./asm/Main.vm16");
    VM16_Load(&vm,VM16_MEMORY_LOW,"./asm/Main.vm16");
    //VM16_Disassemble(&vm,VM16_GetRam(&vm)->data,100);
    VM16_Run(&vm,VM16_MEMORY_LOW);

    printf("Exitcode: %d\n",vm.exitcode);

    VM16_Free(&vm);
    return 0;
}