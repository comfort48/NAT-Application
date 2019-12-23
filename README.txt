Network Address Translation:

1) Main Files:

	1) NAT.hpp              -          Defines the main structure of the NAT 
	2) NAT.cpp	            -          Defines the 2 key functions of the NAT 
	3) NAT_Application.cpp	-          Entry function to run the NAT application



2) NAT_Application: 
	
	Input: 2 files named "NAT" and "FLOW" - These names are hardcoded into the application.
	Output: output is written to a file named OUTPUT.txt in the directory of the NAT_Application.

3) How to run: - I tested on a Linux machine (UBUNTU) which has "make" installed. If you don't have make installed, just compile the  NAT_Application.cpp using "g++ NAT_Application.cpp" and run using "./a.out" command  
	
	If "make" command works fine in your PC, Just go into the directory "NAT_Application" then, run the command "make" - This command compiles and runs the nat_application. Once done, check the OUTPUT.txt file for the translated addresses.


4) Checking the output: 
	
	Check the OUTPUT.txt file under the NAT_Application directory for the translated Addresses


5) Testing with other NAT and FLOW files:

	Just replace the "NAT" and "FLOW" files under the NAT_Application directory to new "NAT" and "FLOW" files (which have the inputs to the NAT application)

	If you want the change the input file names of "NAT" and "FLOW",  then change the file names in NAT_Application.cpp @ line 10 and 15 respectively




******************************************* Assumptions *********************************************** 

1) I assumed that the input files names are always NAT and FLOW respectively and that is the reason why I hardcoded the input file names in NAT_Application.cpp file.

2) I assumed that all the input contents in the files NAT and FLOW are valid and not contain any invalid inputs


******************************************* Optimizations & Algorithmic Tradeoffs ************************************

1) Once the IP is populated to NAT mapper, there is a chance that the machine in the network could go down or permanently removed from the network, in that case  we need to erase the machine's ip from the NAT mapper. This feature could bring more dynamics into play, but this could be done as a new feature.

2) Currently, I used an unordered_map for storing the addresses, insertion and lookup in an unordered_map is in constant time. Therefore, performance in terms of time is very optimal. But, if we consider the storage or the space complexity, the space it takes is not optimal. Instead of using unordered_map entry for each of the NAT address we can use a TRIE data structure to optimally save the IP address mapping. This optimization could be done to optimize the space. Using TRIE saves a good amount of space for larger NAT applications.







	

	
	


