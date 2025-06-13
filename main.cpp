constexpr int REQUIRED_FRAMEWORK_API_VERSION = 1;

struct FrameworkAPI
{
    int version;
    void (*Log)(const char* msg);
    void (*Patch)(int address, const char* patch, size_t size);
};

struct PluginAPI
{
    int required_framework_version = REQUIRED_FRAMEWORK_API_VERSION;
    const char* name = "Weapon Unlock";
    const char* author = "maguc";
    const char* description = "Contains small patch to unlock weapons, special thanks to John-Price_BR.";
    const char* version = "1.0";
    bool unload_after_init = true;  // !! EXPERIMENTAL !!
                                    // DO NOT create threads, hooks, or timers in this plugin if unload_after_init = true!
                                    // FreeLibrary() is called immediately after PluginInit(), so the DLL must be fully idle.
                                    // It will most likely cause a crash or other unintended behaviours if code is still running!
};

static PluginAPI pluginAPI;

extern "C" __declspec(dllexport)
PluginAPI* PluginInit(FrameworkAPI* api)
{
    char patch[] = { 0x90, 0x90 }; // NOP, NOP

    api->Patch(0x005028C5, patch, sizeof(patch));

    return &pluginAPI;
}