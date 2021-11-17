#pragma once

namespace Kernel{
    #define PAGE_FAULT 0x1000000001    //page fault
    #define GP_FAULT   0x1000000002    //general protection fault
    #define DB_FAULT   0x1000000003    //double fault
    #define TRP_FAULT  0x1000000004    //triple fault
    #define MEM_FAULT  0x1000000005    //memory fault
    #define APP_RSVD_SE 0x1000000006   //app reserved storage
}
namespace Userspace{
    //not yet
}
namespace Bootloader{
    #define KRNL_MSING 0x2000000001    //kernel missing
    #define FNT_MSING  0x2000000002    //font missing
    #define KRNL_BFORMT 0x200000003    //kernal bad format
}