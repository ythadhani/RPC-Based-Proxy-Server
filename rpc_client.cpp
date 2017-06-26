#include <iostream>
#include <string.h>
#include "rpc.h"  
#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h> 
#include <fstream>
   
using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace tutorial;


int main(int argc, char **argv) 
{
	boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
 	
	string url,result;
	//url represents the actual URL to be fetched
 	//result represents the HTML webpage corresponding to url
	rpcClient client(protocol);
	transport->open();
	ifstream myfile ("Workload1.txt");
	
	if(myfile.is_open())
  	{
    		while(getline(myfile,url))
    		{

    			client.get_data(result,url);  //client requesting URLs
    		}
    		myfile.close();
  	}
  	else 
	{	
		cout << "Unable to open file"<<endl;
	} 

	//Stats is a data structure which stores Hit Ratio and Average time per access
	Stats s;
	client.print_statistics(s);

	transport->close();

    	//printing statistics
	cout<<"Statistics"<<endl;
	cout<<"Hit Ratio: "<<s.hit_ratio<<endl;
	cout<<"Average time per access: "<<s.time_taken<<endl;

	return 0;
}
