#!/usr/bin/env python3

# This file examines the map-in-map mechanisms in bcc.
import argparse
import ctypes
import os
import signal
import subprocess
import time
from bcc import BPF

parser = argparse.ArgumentParser(description="An example program to invoke jhash eBPF.")

if __name__ == "__main__":
    args = parser.parse_args()

    src_text = open("ebpf_jhash.c", "r").read()

    bpf_program = BPF(text = src_text, debug=8)

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
