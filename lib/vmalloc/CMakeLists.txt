include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(vmalloc STATIC
    # Header files
    vmalloc.h
    vmhdr.h

    # Source files
    vmbest.c
    vmclear.c
    vmclose.c
    vmopen.c
    vmstrdup.c
)
