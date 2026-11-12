#ifndef RYLAR_998_MANAGER_HPP
#define RYLAR_998_MANAGER_HPP

#include <memory>
#include <string>

struct device;
struct lora_modem_config;

class Rylar_998_Manager {

public:
    Rylar_998_Manager();

    void configure(const device* lora_dev, const lora_modem_config& config);
    
    void transmit(std::string message);

    void receive();

    ~Rylar_998_Manager();
    
    private:
        const device *m_lora_dev = nullptr;
        std::unique_ptr<lora_modem_config> m_lora_config;
};

#endif // RYLAR_998_MANAGER_HPP
