#ifndef NAT_HPP
#define NAT_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

class NetworkAddressTranslation {

public:

    NetworkAddressTranslation() {
        exact_ip_port_pairMapper = {};
        any_ip_specific_port_pairMapper = {};
        specific_ip_any_port_pairMapper = {};
    }

    void populateNatMapper(string natFile);                             // Function which populates the 3 mappers of the NAT application

    void natFlowMapper(string flowFile);                            // Function which translates the incoming addresses to the respective network address by using the NAT application's 3 mappers.

private:

    unordered_map<string, string> exact_ip_port_pairMapper;         // Translates addresses of the form -> 10.0.1.1:8080 -> 192.168.0.1:80

    unordered_map<string, string> any_ip_specific_port_pairMapper;  // Translates addresses of the form -> *:8081        -> 192.168.0.1:80

    unordered_map<string, string> specific_ip_any_port_pairMapper;  // Translates addresses of the form -> 10.0.1.2:*    -> 192.168.0.1:80

};

#endif // NAT_HPP
