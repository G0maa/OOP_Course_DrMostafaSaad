#include <bits/stdc++.h>
using namespace std;

class ConfigurationManger {
private:
	string configuration_path;
	vector<string> servers_ips;
	string aws_service_url;
	// Other heavy data
    // this bool can be static, and the constructor checks it first,
    // but it will still allow users to create instances of the same class.
    // so I want with just privateizing the constructor.
	bool is_loaded = false;

    ConfigurationManger(string configuration_path) :
			configuration_path(configuration_path) {

	}
public:
	
	void Load() {
		if (is_loaded)
			return;
		// some heavy load
		cout << "Lazy loading\n";
		servers_ips.push_back("10.20.30.40");
		servers_ips.push_back("10.20.30.41");
		servers_ips.push_back("10.20.30.42");
		aws_service_url = "https://dynamodb.us-west-2.amazonaws.com";
		is_loaded = true;
	}
	string GetAwsServiceUrl() {	
		Load();
		return aws_service_url;
	}

    friend ConfigurationManger* fstart();

};

// Probably not the right way, but I tried my best. 
ConfigurationManger *pointer = nullptr;
ConfigurationManger* fstart() {
    if(!pointer) {
        static ConfigurationManger mgr("/home/moustafa/conf_info.txt");
        pointer = &mgr;
        return pointer;
    } else
        return pointer;
}



void f1() {
    // can't create instnace of object cuz constructor is private.
	// ConfigurationManger mgr("/home/moustafa/conf_info.txt");
    ConfigurationManger *test = fstart();
	cout<<test->GetAwsServiceUrl()<<"\n";
}

void f2() {
	// ConfigurationManger mgr("/home/moustafa/conf_info.txt");
    ConfigurationManger *test = fstart();
	cout<<test->GetAwsServiceUrl()<<"\n";
}

int main() {

	f1();
	f2();

	return 0;
}