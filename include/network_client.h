#pragma once

#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <string>

#include "network_interface.h"

class NetworkClient {
public:
    explicit NetworkClient(NetworkInterface* network) : network_(network) {}

    bool send(const std::string& data) {
        if (network_ == nullptr) {
            return false;
        }

        return network_->send_data(data);
    }

private:
    NetworkInterface* network_;
};

#endif // NETWORK_CLIENT_H
