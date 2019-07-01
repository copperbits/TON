# Web Server

Alongside with the main client binary (test-lite-client), you may also build an executable `test-lite-client-with-webserver` by running:

```cd ton-test-liteclient-full```
```mkdir lite-client-with-webserver-build```
```cd lite-client-with-webserver-build```

```cmake ../lite-client-with-webserver && cmake --build . --target test-lite-client-with-webserver```

*Boost 1.69 required*

Web server uses port `8000` and listens requests to such endpoints:

* `/time` - ton server time
* `/getaccount/<account_address>` - address information
* `/getblock/<block_id>` - block information

**Some Notes**

1. A separate thread launched for auto-updating the chain data by sending a `last` command periodically

1. If you have issues with locating Boost lib in your system during a compile process, just modify the line with `target_include_directories` instruction in file **CMakeLists.txt** by adding the location of boost:

```target_include_directories(${target} SYSTEM PUBLIC ${lib_include_dirs} /usr/local/Cellar/boost/1.69.0_2/include)```


## TODO

1. Refactor a huge amount of nested async calls
1. Make an ability to specify a port in command-line at program startup
1. JSON format for i/o data
1. API versioning
1. Tests