#!/usr/bin/env python3

# This file examines the map-in-map mechanisms in bcc.
import argparse
import ctypes
import os
import signal
import subprocess
import time
from bcc import BPF

parser = argparse.ArgumentParser(description="An example program to implement the map array of eBPF.")
parser.add_argument(
    "-n", "--no-maps",
    help="the number of maps",
    default=2,
    choices=[str(x) for x in range(1,10)],
    metavar=int)

def preprocess_code(args, code_file='ebpf_map_array.c'):
    """ Opens the code file and edit it accordingly.
    """
    prefix = "#include <linux/bpf.h>\n"

    # Adds the map by given number of maps
    map_code = ""
    for i in range(int(args.no_maps)):
        map_code += "BPF_ARRAY(ex" + str(i+1) + ", __u32, 1024);\n"

    src_text = open(code_file, "r").read()
    src_text = prefix + map_code + src_text
    return src_text

if __name__ == "__main__":
    args = parser.parse_args()

    bpf_text = preprocess_code(args)
    print(bpf_text) # Prints a preview of source code after preprocessing

    bpf_program = BPF(text = bpf_text, debug=8)

    control_map = bpf_program.get_table('control')
    outer_map = bpf_program.get_table('maps_array')

    # Inserts the number of maps as an entry at the control map
    control_map[ctypes.c_uint(0)] = ctypes.c_uint(int(args.no_maps))

    inner_maps = []
    for i in range(int(args.no_maps)):
        inner_i_map = bpf_program.get_table('ex'+str(i+1))

        # Insert the zero-th entry in the inner map to be the ID of this map
        inner_i_map[ctypes.c_uint(0)] = ctypes.c_uint(i+1)

        # Insert the inner map's fd into the outer map, `maps_array`
        outer_map[ctypes.c_uint(i)] = ctypes.c_uint(inner_i_map.get_fd())

        inner_maps.append(inner_i_map)

    # Attach this program to the system call for invoking
    syscall_fnname = bpf_program.get_syscall_fnname("getuid")
    bpf_program.attach_kprobe(event=syscall_fnname, fn_name="syscall__getuid")

    os.getuid() # Invoke the system call

    # Print the results from kernel module
    printing_process = subprocess.Popen(["cat", "/sys/kernel/debug/tracing/trace_pipe"], shell=False)
    time.sleep(1)
    os.kill(printing_process.pid, signal.SIGINT)

    # Clean up
    input("Press Enter to exit...")
    bpf_program.detach_kprobe(event=syscall_fnname)
