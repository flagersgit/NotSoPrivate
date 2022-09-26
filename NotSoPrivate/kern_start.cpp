//
//  kern_start.cpp
//  NotSoPrivate
//
//  Copyright © 2022 flagers. All rights reserved.
//

// Lilu headers
#include <Headers/plugin_start.hpp>
#include <Headers/kern_api.hpp>

#define MODULE_SHORT "nsp"

#define ATM_ENABLE_PRIVATE_DATA (1 << 24)

static uint32_t (*_atm_get_diagnostic_config)(void) {nullptr};
static kern_return_t *(*_atm_set_diagnostic_config)(uint32_t) {nullptr};

#pragma mark - Plugin start
static void pluginStart() {
    DBGLOG(MODULE_SHORT, "start");
    lilu.onPatcherLoadForce(
    [](void *user, KernelPatcher &patcher) {
        _atm_get_diagnostic_config = reinterpret_cast<decltype(_atm_get_diagnostic_config)>(patcher.solveSymbol(KernelPatcher::KernelID, "_atm_get_diagnostic_config"));
        _atm_set_diagnostic_config = reinterpret_cast<decltype(_atm_set_diagnostic_config)>(patcher.solveSymbol(KernelPatcher::KernelID, "_atm_set_diagnostic_config"));
        
        if (!(_atm_get_diagnostic_config && _atm_set_diagnostic_config)) {
            SYSLOG(MODULE_SHORT, "failed to solve required symbols");
        } else {
            _atm_set_diagnostic_config(_atm_get_diagnostic_config() | ATM_ENABLE_PRIVATE_DATA);
        }
    });
};

// Boot args.
static const char *bootargOff[] {
    "-nspoff"
};
static const char *bootargDebug[] {
    "-nspdbg"
};
static const char *bootargBeta[] {
    "-nspbeta"
};

// Plugin configuration.
PluginConfiguration ADDPR(config) {
    xStringify(PRODUCT_NAME),
    parseModuleVersion(xStringify(MODULE_VERSION)),
    LiluAPI::AllowNormal,
    bootargOff,
    arrsize(bootargOff),
    bootargDebug,
    arrsize(bootargDebug),
    bootargBeta,
    arrsize(bootargBeta),
    KernelVersion::ElCapitan,
    KernelVersion::Ventura,
    pluginStart
};
