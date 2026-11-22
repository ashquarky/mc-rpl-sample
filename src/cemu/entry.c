#include <coreinit/dynload.h>
#include "main.h"

// cemu entrypoint
extern int rpl_entry([[maybe_unused]] OSDynLoad_Module module, const OSDynLoad_EntryReason reason) {
    if (reason != OS_DYNLOAD_LOADED)
        return 0;

    app_main(Cemu);
    return 0;
}
