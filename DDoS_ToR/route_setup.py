#!/usr/bin/env python3
# This script finds the host type and configures the routes 
# so that they will not go out into the public

import os
import argparse
import ipaddress

parser = argparse.ArgumentParser(description="Configures the default routes for hosts in the testbed")
parser.add_argument("-s", "--setup", dest='is_setup',default = True, action='store_true')
parser.add_argument("-t", "--teardown", dest='is_setup', default = False, action='store_false')

CONTROL_NETWORKS = [
    '75.0.0.0/8',
    '129.22.0.0/16'
]

HOST_TYPE_ATK = 0
HOST_TYPE_USR = 1
HOST_TYPE_TOR = 2
HOST_TYPE_AGG = 3
HOST_TYPE_VIP = 4
HOST_TYPE_CON = 5

def get_host_type():
    hostname = os.popen('hostname').read()
    if hostname.lower().startswith("attacker"):
        return HOST_TYPE_ATK
    if hostname.lower().startswith("user"):
        return HOST_TYPE_USR
    if hostname.lower().startswith("tor"):
        return HOST_TYPE_TOR
    if hostname.lower().startswith("agg"):
        return HOST_TYPE_AGG
    if hostname.lower().startswith("vip"):
        return HOST_TYPE_VIP
    if hostname.lower().startswith("con"):
        return HOST_TYPE_CON

def get_route(network):
    all_routes = os.popen('ip r').read().split('\n')
    gateway = ''
    gatedev = ''
    for route in all_routes:
        if str(network) in route:
            items = route.split(' ')
            for i, item in enumerate(items):
                if item == 'via':
                    gateway = items[i+1]
                if item == 'dev':
                    gatedev = items[i+1]
            break
    return gateway, gatedev

def set_control_routes(gateway, gatedev):
    for control_network in CONTROL_NETWORKS:
        os.popen('ip r add %s via %s dev %s'%(control_network, gateway, gatedev))

def del_route(route):
    os.popen('ip r del %s'%(route))

def reset_default_routes(gateway, gatedev):
    os.popen('ip r del default')
    os.popen('ip r add default via %s dev %s'%(gateway, gatedev))

def restore_default_routes():
    all_routes = os.popen('ip r').read().split('\n')
    default_gateway, default_gatedev = "", ""
    for routes in all_routes:
        items = routes.split(' ')
        if items[0].startswith(CONTROL_NETWORKS[0]):
            for i,item in enumerate(items):
                if item == 'dev':
                    default_gatedev = item[i+1]
                if item == 'via':
                    default_gateway = item[i+1]
    
    os.popen('ip r del default')
    os.popen('ip r add default via %s dev %s'%(default_gateway, default_gatedev))

def configure_host_routes():
    default_gateway, default_gatedev = get_route('default')
    exp_gateway, exp_gatedev = get_route('10.0.0.0/8')

    set_control_routes(default_gateway, default_gatedev)
    reset_default_routes(exp_gateway, exp_gatedev)

def configure_agg_routes():
    default_gateway, default_gatedev = get_route('default')
    set_control_routes(default_gateway, default_gatedev)

    all_routes = os.popen('ip r').read().split('\n')
    for routes in all_routes:
        items = routes.split(' ')
        if items[0].startswith('10.'):
            del_route(items[0])

    all_interfaces = os.listdir('/sys/class/net')
    print(all_interfaces)
    for interface in all_interfaces:
        ipstr = os.popen("ifconfig %s | grep 'inet addr:'"%(interface)).read()
        ipstrs = ipstr.split(' ')
        print(ipstrs)
        ipaddr = ''
        for items in ipstrs:
            if items.startswith("addr:"):
                ipaddr = items.split(':')[-1]
                break
        if len(ipaddr) == 0:
            continue
        remote_ipaddr = str(ipaddress.ip_address(int(ipaddress.ip_address(ipaddr)) - 1))
        remote_ipnetw = str(ipaddress.ip_address(int(ipaddress.ip_address(ipaddr)) - 2)) + '/16'
        os.popen('ip r add %s dev %s src %s'%(remote_ipaddr, interface, ipaddr))
        os.popen('ip r add %s via %s dev %s src %s'%(remote_ipnetw, remote_ipaddr, interface, ipaddr))

def configure_routes():
    hosttype = get_host_type()
    func = {
        HOST_TYPE_ATK: configure_host_routes,
        HOST_TYPE_USR: configure_host_routes,
        HOST_TYPE_VIP: configure_host_routes,
        HOST_TYPE_AGG: configure_agg_routes,
        HOST_TYPE_TOR: configure_host_routes,
        HOST_TYPE_CON: configure_host_routes,
    }[hosttype]
    func()

def add_local_hostname():
    hostname = os.popen('hostname').read()
    os.popen('echo "127.0.0.1 %s"| sudo tee -a /etc/hosts'(hostname))

if __name__ == "__main__":
    assert len(CONTROL_NETWORKS) > 0, "No control networks, aborting!"

    args = parser.parse_args()

    if args.is_setup: # Setup
        add_local_hostname()
        configure_routes()
    else:
        restore_default_routes()
