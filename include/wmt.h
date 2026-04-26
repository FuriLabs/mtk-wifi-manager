/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 MediaTek
 * Copyright (C) 2025 Bardia Moshiri <bardia@furilabs.com>
 */

#ifndef WMT_H
#define WMT_H

#include <sys/inotify.h>
#include <gio/gio.h>

typedef enum {
    WIFI_STATE_AP = 1,
    WIFI_STATE_P2P = 2,
    WIFI_STATE_DUAL_AP = 3,
    WIFI_STATE_DUAL_P2P = 4,
    WIFI_STATE_ON = 5,
    WIFI_STATE_OFF = 6
} WiFiState;

#define MAX_WAIT_SECOND              0xefffffff
#define MAX_RETRY_COUNT              5
#define NVRAM_MAC_ADDRESS_OFFSET     4
#define BUF_SIZE                     1024

#define WIFI_LOADER_DEV              "/dev/wmtWifi"
#define WIFI_NVRAM_PATH              "/mnt/vendor/nvdata/APCFG/APRDEB"
#define WIFI_MACADDR_FILE            "/usr/lib/furios/device/wifimac"

#define FILE_REMOVE_MASK (IN_DELETE_SELF | IN_MOVE_SELF)
#define FILE_MODIFY_MASK IN_MODIFY
#define WATCH_FILE_MASK (FILE_REMOVE_MASK | FILE_MODIFY_MASK)
#define WATCH_PATH_MASK (IN_MOVED_TO | IN_CREATE)

#define NVRAM_CHANGED    4

/* Global variable to signal shutdown */
extern volatile gint wmt_shutdown_flag;

/**
 * Set WiFi state by writing to the driver.
 *
 * @param state  WiFi state to set (WIFI_STATE_AP or WIFI_STATE_P2P).
 * @return       0 on success, -1 on failure.
 */
int
wmt_set_state(WiFiState state);

/**
 * Start the WMT monitoring loop.
 * This function monitors the WiFi device and NVRAM files for changes
 * using GLib's event loop system.
 */
void
wmt_start_monitor(void);

/**
 * Signal the monitor thread to shut down gracefully.
 * This uses GLib's context system to safely signal the monitor thread.
 */
void
wmt_signal_monitor_shutdown(void);

#endif /* WMT_H */
