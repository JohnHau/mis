# Coap server example for STM32f407 Discovery using LAN8720

I started this example using my example for [STM32f407 Discovery with LWIP socket](https://github.com/the-diy-life/HTTP_server_on_STM32f407-STM32F4Discovery_with_STM32F4DIS-BB-LAN8720) then to create coap server i imported [libcoap library](https://github.com/obgm/libcoap/tree/98954eb30a2e728e172a6cd29430ae5bc999b585) to the project with the help of  porting used in [espressif esp-idf](https://github.com/espressif/esp-idf/tree/master/components/coap).

## Steps to import Libcoap Llibrary to our STM32f407 Discovery
* Download the [libcoap library](https://github.com/obgm/libcoap/tree/98954eb30a2e728e172a6cd29430ae5bc999b585) then unzip the downloaded folder to folder named libcoap and copy that folder into project in path `LwIP_HTTP_Server_Socket_RTOS\Middlewares\Third_Party\libcoap`

    > Note that according to [espressif esp-idf](https://github.com/espressif/esp-idf/tree/master/components/coap) we are using version 2 for libcoap library and not the latest version of libcoap

* As IPv6 is included in libcoap so we need to download [LWIP IPv6](https://github.com/espressif/esp-idf/tree/master/components/coap) folder and add it in our project in path `LwIP_HTTP_Server_Socket_RTOS\Middlewares\Third_Party\LwIP\src\core`
* Add the downloaded sources files in STM32Cube IDE
    * in project explorer tab in STM32Cube IDE add new folder named libcoap to Middlewares and also folder named IPv6  and construct that structure
        ```
        ├── Middlewares
        │   ├── libcoap
        │       ├── libcoap_minimal
        │       └── src
        │   ├── FreeRtos
        │   ├── LwIP
        │       ├── Api
        │       ├── apps
        │       ├── Core
        │           ├── IPv4
        │           └── Ipv6
        │       └── Neif
        ```
    * right click on libcoap_minmal then choose import to import file `server.c` from path `\LwIP_HTTP_Server_Socket_RTOS\Middlewares\Third_Party\libcoap\examples\libcoap-minimal` with refrence to project location 
    * repeat previos step to add source files of libcoap library in src sufolder and also for IPv6 source files
* For compiling in STM32Cube IDE include the following paths 
    * ../../../Middlewares/Third_Party/LwIP/src/include/compat/posix
    * ../../../Middlewares/Third_Party/libcoap/include/coap2
    * ../../../Middlewares/Third_Party/libcoap/port/include
    * ../../../Middlewares/Third_Party/libcoap/port/include/coap
    * ../../../Middlewares/Third_Party/libcoap/examples/libcoap-minimal

## Modifications to use with STM32

* In `lwipopts.h ` add the following 
    ```
    #define LWIP_IPV6                       1
    #define LWIP_DNS                        1
    #define LWIP_TCPIP_CORE_LOCKING         0
    #define LWIP_DNS_SUPPORT_MDNS_QUERIES 1
    #define DNS_SERVER_ADDRESS(ipaddr) ip_addr_set_ip4_u32(ipaddr,ipaddr_addr("8.8.8.8"))
    #define DNS_MAX_SERVERS                 3
    #define DNS_FALLBACK_SERVER_INDEX        (DNS_MAX_SERVERS - 1)
    ```
* In coap_mutex.h add the following

    > #define PTHREAD_MUTEX_INITIALIZER  ((pthread_mutex_t) 0xFFFFFFFF)

* For files coap_io.c,address.c,libcoap.h and net.c 
    > replace # include <netinet/in.h> with :
    >
    > #include "lwip/inet.h"

* In file `\LwIP_HTTP_Server_Socket_RTOS\Middlewares\Third_Party\LwIP\src\include\lwiplwip\inet.h` add the following 
    > #define IN6_IS_ADDR_MULTICAST(a)    IN_MULTICAST(a)

* In file `LwIP_HTTP_Server_Socket_RTOS\Middlewares\Third_Party\libcoap\port\include` define the following:

    > #define COAP_CONSTRAINED_STACK 0
    >
    > #define _POSIX_TIMERS 1

* Add two files time.c in `LwIP_HTTP_Server_Socket_RTOS\Src` and time.h in `LwIP_HTTP_Server_Socket_RTOS\Inc`to give coap ticks time and import that soorce file time.c in STM32Cube IDE under LwIP_HTTP_Server_Socket_RTOS\Application\User subfolder.

## Code explanation 
I created task for CoAP server which can receive requests / data from CoAP client and transmit data to CoAP client , in our coap server i create only one resource /hello with initial data "Hello World!" and that resource will support coap methods get , put and delete while client can query or change that resource data as well as our created resource is observable to allow coap clients to observe our resource data 

## How to test the code
We can use [coap-cli](https://www.npmjs.com/package/coap-cli) tool to test all coap client methods supported by our server such as:
```
* coap get coap://[STM board IP]/hello
* echo 'data to send' | coap put coap://[STM board IP]/hello
* coap delete coap://[STM board IP]/hello 
* coap get -o coap://[STM board IP]/hello 
```