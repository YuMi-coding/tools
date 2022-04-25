#include <linux/jhash.h>
#include <linux/bpf.h>

int syscall__getuid(void * ctx)
{
    __u32 value_to_hash = 0xbeefcafe, length=4;
    __u32 init_val = 0xdeadbeef;
    __u32 hash_value = 0;

    hash_value = jhash(&value_to_hash, length, init_val);

    bpf_trace_printk("The hash value for %u is %u.\n", value_to_hash, init_val);

    return 0;
}