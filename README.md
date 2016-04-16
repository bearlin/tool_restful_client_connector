# tool_restful_client_connector
A small RESTful C++ client tool with very limit RESTful Client APIs functions. 
The develop environment is Ubuntu 14.04 64bit.

#Environment setup
Install cmake, OpenSSL
sudo apt-get install libssl-dev cmake 

#Build
```sh
./build.sh         (normal build)
./build.sh clean   (clean build)
```

#Run the demo
```sh
./Build/RESTfulClientAPIs/Test/Unittest/CHttpURLConnectionTest/RESTfulClientAPIs_Test_Unittest_CHttpURLConnectionTest
./Build/RESTfulClientAPIs/Test/Unittest/CServerResponseTest/RESTfulClientAPIs_Test_Unittest_CServerResponseTest
./Build/RESTfulClientAPIs/Test/Unittest/CRestClientTest/RESTfulClientAPIs_Test_Unittest_CRestClientTest
```

#Troubleshooting
If facing this error:
```sh
/usr/bin/ld: skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/4.6/libstdc++.so when searching for -lstdc++
/usr/bin/ld: skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/4.6/libstdc++.a when searching for -lstdc++
/usr/bin/ld: cannot find -lstdc++
collect2: ld returned 1 exit status
```

Use following command to install libstdc++:
```sh
sudo apt-get install g++-multilib
```

#Other Infomation
  None.
  
