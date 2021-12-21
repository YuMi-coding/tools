import random
p4 = bfrt.tna_simple_switch.pipe

# This function can clear all the tables and later on other fixed objects
# once bfrt support is added.
def clear_all(verbose=True, batching=True):
    global p4
    global bfrt
      
    # The order is important. We do want to clear from the top, i.e.
    # delete objects that use other objects, e.g. table entries use
    # selector groups and selector groups use action profile members
    
    for table_types in (['MATCH_DIRECT', 'MATCH_INDIRECT_SELECTOR'],
                        ['SELECTOR'],
                        ['ACTION_PROFILE']):
        for table in p4.info(return_info=True, print_info=False):
            if table['type'] in table_types:
                if verbose:
                    print("Clearing table {:<40} ... ".
                          format(table['full_name']), end='', flush=True)
                table['node'].clear(batch=batching)
                if verbose:
                    print('Done')

#################################
# port_mapping control sequence #
#################################
port_mapping = p4.SwitchIngress.port_mapping.port_mapping
# port_mapping.add_with_set_port_attributes(
#     port=17,
#     ifindex=17
# )
port_vlan_to_bd_mapping = p4.SwitchIngress.port_mapping.port_vlan_to_bd_mapping

###################################
# pkt_validation control sequence #
###################################
validate_ethernet = p4.SwitchIngress.pkt_validation.validate_ethernet
validate_ethernet.add_with_valid_pkt_tagged(
    valid=1
)
validate_ethernet.add_with_valid_pkt_untagged(
    valid=0
)

validate_ipv4 = p4.SwitchIngress.pkt_validation.validate_ipv4
validate_ipv4.add_with_valid_ipv4_pkt(
    0x04, # hdr.ipv4.version
    0x0f  # hdr.ipv4.version_prefix_length
)

validate_ipv6 = p4.SwitchIngress.pkt_validation.validate_ipv6
validate_ipv6.add_with_valid_ipv6_pkt(
    0x06, # hdr.ipv6.version
    0x0f  # hdr.ipv6.version_prefix_length
)

############################
# Nexthop control sequence #
############################
nexthop_general = p4.SwitchIngress.nexthop.nexthop
nexthop_general.add_with_set_nexthop_attributes(
    nexthop=17,
    bd=0,
    dmac=""
)