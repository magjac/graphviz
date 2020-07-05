include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(vmalloc STATIC
    # Header files
    vmalloc.h
    vmhdr.h

    # Source files
    vmbest.c
    vmclear.c
    vmclose.c
    vmdcheap.c
    vmdisc.c
    vmopen.c
    vmprivate.c
    vmregion.c
    vmsegment.c
    vmset.c
    vmstat.c
    vmstrdup.c
    vmtrace.c
    vmwalk.c
)
