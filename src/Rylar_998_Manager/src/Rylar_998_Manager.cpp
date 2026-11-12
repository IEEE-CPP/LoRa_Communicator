#include "Rylar_998_Manager.hpp"
#include <pw_assert/check.h>
#include <zephyr/drivers/lora.h>
#include <zephyr/logging/log.h>


LOG_MODULE_REGISTER(Rylar_998_Manager);

Rylar_998_Manager::Rylar_998_Manager()
    : m_lora_config(std::make_unique<lora_modem_config>()) {}

Rylar_998_Manager::~Rylar_998_Manager() = default;

void Rylar_998_Manager::configure(const device* lora_dev, const lora_modem_config& config) {
    PW_CHECK(lora_dev != nullptr, "LoRa Dev Configured Incorrectly");
    PW_CHECK(device_is_ready(lora_dev), "LoRa Dev Not Ready");
    
    this->m_lora_dev = lora_dev;
    *this->m_lora_config = config;

    int response = lora_config(m_lora_dev, m_lora_config.get());
    PW_CHECK(response == 0, "LoRa Configuration Failed");
}

void Rylar_998_Manager::transmit(std::string message) {
    PW_CHECK(m_lora_dev != nullptr, "LoRa Dev Not Configured");

    int response = lora_send(m_lora_dev, reinterpret_cast<uint8_t*>(message.data()), message.size());

    if (response < 0) {
        LOG_ERR("Failed to transmit message: %s", message.c_str());
    } else {
        LOG_INF("Transmitted message: %s", message.c_str());
    }
}

void Rylar_998_Manager::receive() {
    PW_CHECK(m_lora_dev != nullptr, "LoRa Dev Not Configured");
}



