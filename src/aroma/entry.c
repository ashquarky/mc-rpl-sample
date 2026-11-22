#include "main.h"
#include "syscalls.h"

#include <coreinit/dynload.h>
#include <coreinit/title.h>
#include <wups.h>

WUPS_PLUGIN_NAME("mc-sample");
WUPS_PLUGIN_AUTHOR("ashquarky");

// wups entrypoint
ON_APPLICATION_START() {
    const uint64_t title_id = OSGetTitleID();
    if (title_id != 0x00050000'101D9D00 && title_id != 0x00050000'101D7500 && title_id != 0x00050000'101DBE00)
        return;
    if (OSGetTitleVersion() != 688)
        return;

    app_main(Aroma);
}
