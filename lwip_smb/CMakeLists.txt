# This is a template cmake skript that creates a library from
# some sources in a honeycomb mbsp folder or subfolder. Copy
# this file into the folder that is the root for all the sources
# of your library.
#
# You must also adjust the list of source files in add_library(..)
# statement below. The sources can even reside in a subfolder. In
# that case you have to provide the path to the source file 
# relative to the location where this cmake skript is stored.
#
# You must adjust the library-name in the add_library(..) statement
# to whatever name you want to assign to your library. The library
# name must be unique across all libraries being used for the product
# (including the honeycomb libraries).
#
# You can skip the library to be parsed for doxygen documentation
# by commenting out the line with the register_doxygen_input_dir(..)
# statement.
#
# In your product cmake script you need to add the following line:
# add_subdirectory(<path to this cmake script relative to the product cmake script> ${LIBRARY_BUILD_DIR}/<library name>)
#
# Optionally you can declare a search path to the header files that belong
# the library by adding the following line:
# 	include_directories(<path to the header files relative to the product cmake script>)
# The following search path alternative reduces number of search paths
# and allows identical header file names in different libraries):
#   If you have multiple libraries in a parent folder you can rather set
#   a single search path to this parent folder and use an relative path
#   to the parent folder in your #include directive. E.g. if you have
#   library a, b and c in a parent folder and a search path set to it the
#   required includes look like this.
#     #include "lib-a-folder/headerfile.h"
#     #include "lib-b-folder/headerfile.h"
#     #include "lib-c-folder/headerfile.h"
#

cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0011 NEW)
cmake_policy(SET CMP0053 OLD)
bsp_subprj_dir_2_subprj_name(_PROJECT_NAME_ "${CMAKE_CURRENT_SOURCE_DIR}" lwip REPLACE)
set(_PROJECT_ ${_PROJECT_NAME_} C CXX ASM)
message( "${MESSAGE_TABS}Folder ${_PROJECT_} ..." )
set(MESSAGE_TABS "${MESSAGE_TABS}\t")

# add this directory to the eclipse source directories
register_eclipse_prj_source_dir("${_PROJECT_NAME_}")
project(${_PROJECT_})

# add this directory to the doxygen input directories
register_doxygen_input_dir("${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(${BSP_SRC_ROOT_DIR}/lwip/include)
#include_directories(${BSP_SRC_ROOT_DIR}/lwip/include/lwip/prot)
#include_directories(${BSP_SRC_ROOT_DIR}/lwip/include/lwip)
#include_directories(${BSP_SRC_ROOT_DIR}/lwip/include/lwip/prot)
include_directories(${BSP_SRC_ROOT_DIR}/lwip/port)
include_directories(${BSP_SRC_ROOT_DIR}/lwip/port/arch)

# library to be build
add_library(lwip STATIC  # !!! Adjust <library name>  here.
   apps/lwiperf/lwiperf.c
   api/api_lib.c
   api/api_msg.c
   api/err.c
   api/if_api.c
   api/netbuf.c
   api/netdb.c
   api/netifapi.c
   api/sockets.c
   api/tcpip.c
   core/altcp.c
   core/altcp_alloc.c
   core/def.c
   core/dns.c
   core/inet_chksum.c
   core/init.c
   core/ip.c
   core/mem.c
   core/memp.c
   core/netif.c
   core/pbuf.c
   core/raw.c
   core/stats.c
   core/sys.c
   core/tcp.c
   core/tcp_in.c
   core/tcp_out.c
   core/timeouts.c
   core/udp.c
   core/ipv4/autoip.c
   core/ipv4/dhcp.c
   core/ipv4/etharp.c
   core/ipv4/icmp.c
   core/ipv4/igmp.c
   core/ipv4/ip4.c
   core/ipv4/ip4_addr.c
   core/ipv4/ip4_frag.c
   core/ipv6/dhcp6.c
   core/ipv6/ethip6.c
   core/ipv6/icmp6.c
   core/ipv6/inet6.c
   core/ipv6/ip6.c
   core/ipv6/ip6_addr.c
   core/ipv6/ip6_frag.c
   core/ipv6/mld6.c
   core/ipv6/nd6.c
   netif/bridgeif.c
   netif/bridgeif_fdb.c
   netif/ethernet.c
   netif/lowpan6.c
   netif/lowpan6_ble.c
   netif/lowpan6_common.c
   netif/slipif.c
   netif/zepif.c
   netif/ppp/auth.c
   netif/ppp/ccp.c
   netif/ppp/chap_ms.c
   netif/ppp/chap-md5.c
   netif/ppp/chap-new.c
   netif/ppp/demand.c
   netif/ppp/eap.c
   netif/ppp/eui64.c
   netif/ppp/fsm.c
   netif/ppp/ipcp.c
   netif/ppp/ipv6cp.c
   netif/ppp/lcp.c
   #netif/ppp/lwip_ecp.c
   netif/ppp/magic.c
   netif/ppp/mppe.c
   netif/ppp/multilink.c
   netif/ppp/ppp.c
   netif/ppp/pppapi.c
   netif/ppp/pppcrypt.c
   netif/ppp/pppoe.c
   netif/ppp/pppol2tp.c
   netif/ppp/pppos.c
   netif/ppp/upap.c
   netif/ppp/utils.c
   netif/ppp/vj.c
   port/sys_arch.c
   apps/ping/ping.c
   port/enet_ethernetif_kinetis.c
   port/enet_ethernetif.c
)

if(NOT ${MESSAGE_TABS} STREQUAL "")
	STRING(SUBSTRING ${MESSAGE_TABS} 1 -1 MESSAGE_TABS)
endif(NOT ${MESSAGE_TABS} STREQUAL "")
message( "${MESSAGE_TABS}Folder ${_PROJECT_} done.\n" )
