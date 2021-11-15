#define MAX_ARRAY 10
BPF_ARRAY(ex0, __u32, 1024);
BPF_ARRAY(control, __u32, 1);
BPF_ARRAY_OF_MAPS(maps_array, "ex0" , MAX_ARRAY);

int syscall__getuid(void * ctx)
{
    __u32 zero = 0, *val, *no_maps;
    void * inner_map;

    no_maps = control.lookup(&zero);
    if(!no_maps)
    {
        bpf_trace_printk("No available number of maps.\n");
        return 0;
    }
    if(*no_maps == 0)
        return 0;

// Use compiler instruction(#pragma...) to enable unrolling of loops
#pragma clang loop unroll(full)
    for(__u32 i = 0; i< MAX_ARRAY && i < *no_maps; i++)
    {
        /*
         * Using a temporary value to be key for lookup, otherwise unroll of loops doesn't work
         */
        int temp = i;
        
        inner_map = maps_array.lookup(&temp);
        if(!inner_map)
            break;

        val = bpf_map_lookup_elem(inner_map, &zero);
        /*
         * NOTE: The inner map have to invoke `bpf_map_lookup_elem` for item lookup.
         * See https://github.com/torvalds/linux/blob/master/kernel/bpf/helpers.c#L36 for prototype
         */
        if(val)
        {
            bpf_trace_printk("We are getting %d at No.%d map.\n", *val, i+1);
        }
    }

    return 0;
}