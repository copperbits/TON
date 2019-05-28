# Web Server

Alongside with the main client binary (test-lite-client), you may also build an executable `test-lite-client-with-webserver` by running:

```cmake --build . --target test-lite-client-with-webserver```

*Boost 1.69 required*

Web server uses port `8000` and listens requests to such endpoints:

* `/time` - ton server time
* `/getaccount/<account_address>` - address information

**Some Notes**

1. A separate thread launched for auto-updating the chain data by sending a `last` command periodically

1. If you have issues with locating Boost lib in your system during a compile process, just modify the line with `get_target_property` instruction in file **CMakeLists.txt** by adding the location of boost:

```get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)target_include_directories(${target} SYSTEM PUBLIC ${lib_include_dirs} /usr/local/Cellar/boost/1.69.0_2/include)```


## TODO

1. Refactor a huge amount of nested async calls
1. Make an ability to specify a port in command-line at program startup
1. JSON format for i/o data
1. API versioning
1. Tests