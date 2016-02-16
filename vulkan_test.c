__declspec(dllimport) void *LoadLibraryA(char *);
__declspec(dllimport) void *GetProcAddress(void *, char *);
__declspec(dllimport) int   MessageBoxA(void *, char *, char *, unsigned);

#define REPORT(code, msg)                                         \
    do {                                                          \
        MessageBoxA(0, msg, code ? "Failure" : "Success", 0);     \
        return code;                                              \
    } while (0)

int
WinMainCRTStartup(void)
{
    void *vk = LoadLibraryA("vulkan-1.dll");
    if (!vk)
        REPORT(-1, "Vulkan drivers not installed.");
    void *(*vkGetInstanceProcAddr)(void *, const char *) =
        GetProcAddress(vk, "vkGetInstanceProcAddr");
    if (!vkGetInstanceProcAddr)
        REPORT(-1, "Vulkan is malfunctioning (vkGetInstanceProcAddr).");
    int (*vkCreateInstance)(int *, void *, void **) =
        vkGetInstanceProcAddr(0, "vkCreateInstance");
    if (!vkCreateInstance)
        REPORT(-1, "Vulkan is malfunctioning (vkCreateInstance)");
    void *instance = 0;
    int result = vkCreateInstance((int[16]){1}, 0, &instance);
    if (!instance || result != 0)
        REPORT(-1, "Vulkan drivers installed and functioning "
               "but are incompatible. An instance could not be created.");
    REPORT(0, "Successfully created a Vulkan instance.");
}
