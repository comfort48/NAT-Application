#ifndef NAT_CPP
#define NAT_CPP

#include "NAT.hpp"

void NetworkAddressTranslation::populateNatMapper(string natFileName) {

    ifstream natInputFile(natFileName);                // Input filestream for NAT file

    if(!natInputFile.good())
        cout<<"Error in populateNatMapper"<<endl;                                        // return if the input file is not good

    string line;

    while(getline(natInputFile, line)) {              // read line by line and map it to corresponding mapper based on the rules

        if(!line.empty()) {
            istringstream iss(line);                   // stringstream is used to make life easier while performing operations on strings

            string from_IP_pair;                       // From address
            if(getline(iss, from_IP_pair, ',')) {
                string to_IP_pair;                     // To address

                getline(iss, to_IP_pair, ',');

                string fromIP = from_IP_pair.substr(0, from_IP_pair.find(":"));                                // extracting the from-IP address
                string fromPort = from_IP_pair.substr(from_IP_pair.find(":") + 1, from_IP_pair.size());        // extracting the from-Port number

                if(fromIP == "*")                                                                              // If the input IP can be anything then map based on input port number
                    any_ip_specific_port_pairMapper[fromPort] = to_IP_pair;
                else if(fromPort == "*")                                                                       // If the input port number can be anything then map based on input IP
                    specific_ip_any_port_pairMapper[fromIP] = to_IP_pair;
                else                                                                                           // Else map based on perfect <ip, port> pair
                    exact_ip_port_pairMapper[from_IP_pair] = to_IP_pair;
            }

        }
    }
    natInputFile.close();
    return;
}

void NetworkAddressTranslation::natFlowMapper(string flowFileName) {

    ifstream flowInputFile(flowFileName);              // input filestream for FLOW file

    if(!flowInputFile.good())                          // return if the FLOW file is not good
        cout<<"Error in natFlowMapper"<<endl;

    ofstream outputFile;
    outputFile.open("OUTPUT.txt");                     // outputstream for writing the mapped <ip, port> pair to an OUTPUT file
    string line;

    while(getline(flowInputFile, line)) {             // Read line by line to translate the incoming address to a specific network address

        if(!line.empty()) {

            string incoming_address_pair = line;

            string ip = incoming_address_pair.substr(0, incoming_address_pair.find(":"));                                  // extracting the incoming ip address
            string port = incoming_address_pair.substr(incoming_address_pair.find(":") + 1, incoming_address_pair.size()); // extracting the incoming port number

            if(exact_ip_port_pairMapper.find(incoming_address_pair) != exact_ip_port_pairMapper.end())                     // If there is a perfect entry translated from incoming address (will be present in "exact_ip_port_pairMapper")
                outputFile<<incoming_address_pair<<" "<<"->"<<" "<<exact_ip_port_pairMapper[incoming_address_pair]<<endl;

            else if(specific_ip_any_port_pairMapper.find(ip) != specific_ip_any_port_pairMapper.end())                     // If the ip is specific and port varies (will be present in "specific_ip_any_port_pairMapper")
                outputFile<<incoming_address_pair<<" "<<"->"<<" "<<specific_ip_any_port_pairMapper[ip]<<endl;

            else if(any_ip_specific_port_pairMapper.find(port) != any_ip_specific_port_pairMapper.end())                  // If the ip varies and port is specific (will be present in "any_ip_specific_port_pairMapper")
                outputFile<<incoming_address_pair<<" "<<"->"<<" "<<any_ip_specific_port_pairMapper[port]<<endl;

            else                                                                                                          // If there is no translation present in the 3 mappers of the NAT application
                outputFile<<"No nat match for "<<incoming_address_pair<<endl;
        }
    }
    outputFile.close();
    return;
}
#endif // NAT_CPP
