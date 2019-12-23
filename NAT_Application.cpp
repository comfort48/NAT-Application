#include "NAT.cpp"

int main(int argc, char *argv[]) {

    NetworkAddressTranslation nat; // nat object which does the work of reading the NAT and FLOW file and to output the result in OUTPUT file.

    // Hard-coded the input file names -> NAT and FLOW
    nat.populateNatMapper("NAT"); // Reads the NAT file and feeds the respective mapper (there are 3 mappers
                                                                    //                   Examples: 1) maps 10.0.1.1:8080 -> 192.168.0.1:80. This kind uses "exact_ip_port_pairMapper" member variable
                                                                    //                             2) maps *:8081        -> 192.168.0.1:80  This kind uses "any_ip_specific_port_pairMapper" member variable
                                                                    //                             3) maps 10.0.1.2:*    -> 192.168.0.1:80) This kind uses "specific_ip_any_port_pairMapper" member variable

    nat.natFlowMapper("FLOW"); // Reads the incoming address and maps it to the exact flow as per the respective mappers.

    cout<<"Nat mapping done...."<<endl<<"Output of Nat mappings is present in OUTPUT.txt file"<<endl;

    return 0;
}
