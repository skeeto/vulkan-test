#include <windows.h>

#define REPORT(code, msg)                                         \
    do {                                                          \
        MessageBoxA(0, msg, code ? "Failure" : "Success", MB_OK); \
        ExitProcess(code);                                        \
    } while (0)

int WINAPI
WinMainCRTStartup(void)
{
    HMODULE vk = LoadLibrary("vulkan-1.dll");
    if (!vk)
        REPORT(-1, "Vulkan drivers not installed.");
    void *(*vkGetInstanceProcAddr)(void *, const char *) =
        (void *)GetProcAddress(vk, "vkGetInstanceProcAddr");
    if (!vkGetInstanceProcAddr)
        REPORT(-1, "Vulkan drivers are malfunctioning "
               "(vkGetInstanceProcAddr).");
    int (*vkCreateInstance)(int *, void *, void **) =
        vkGetInstanceProcAddr(0, "vkCreateInstance");
    if (!vkCreateInstance)
        REPORT(-1, "Vulkan drivers are malfunctioning "
               "(vkCreateInstance)");
    void *instance = 0;
    int result = vkCreateInstance((int[16]){1}, 0, &instance);
    if (!instance || result != 0)
        REPORT(-1, "Vulkan drivers installed and functioning "
               "but are incompatible. An instance could not be created.");
    REPORT(0, "Successfully created a Vulkan instance.");
    return 0;
}
