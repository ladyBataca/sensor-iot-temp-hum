#include <string.h>
#include <stdlib.h>

#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"

#include "esp_wifi.h"
#include "nvs_flash.h"

#include <netdb.h>
esp_err_t init_interface();