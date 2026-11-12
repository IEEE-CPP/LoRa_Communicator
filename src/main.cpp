#include "Rylar_998_Manager.hpp"
#include <zephyr/drivers/lora.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main);

#define LORA_NODE DT_ALIAS(lora0)
const struct device *lora_dev = DEVICE_DT_GET(LORA_NODE);

int main() {
    struct lora_modem_config config{};

    config.frequency = 915000000;      // 915 MHz (or 868000000 for EU) 
    config.bandwidth = BW_125_KHZ;     // BW_125_KHZ, BW_250_KHZ, or BW_500_KHZ 
    config.datarate = SF_9;            // 7 to 12 
    config.coding_rate = CR_4_5;       // CR_4_5 (1) to CR_4_8 (4) 
    config.preamble_len = 6;           // Driver requires 4 to 7 
    config.tx_power = 14;              // Driver requires <= 15 
    config.tx = true;                  // true for TX mode, false for RX mode 

    Rylar_998_Manager manager;
    manager.configure(lora_dev, config);
}
