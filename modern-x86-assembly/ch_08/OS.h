//-----------------------------------------------------------------------------
// OS.h
//-----------------------------------------------------------------------------

#pragma once
#include <string>
#include <cstdlib> // Required for free() and posix_memalign
#include <cstdint>


#if defined(_MSC_VER)
    #define NOMINMAX
    #include <windows.h>
#elif defined(__APPLE__)
    #include <unistd.h>
    #include <mach/mach.h>
#elif defined(__GNUG__)
    #include <unistd.h>
#else
    #error Unexpected target in OS.h
#endif

class OS
{
public:

    static std::string GetComputerName()
    {
        std::string computer_name;
        const size_t cn_len = 256;
        char cn[cn_len] = { '\0' };

#if defined(_MSC_VER)
        size_t cn_len_ret;

        if (getenv_s(&cn_len_ret, cn, cn_len * sizeof(char), "COMPUTERNAME") == 0)
            computer_name = cn;
#endif

#if defined(__GNUG__) || defined(__APPLE__)
        if (gethostname(cn, cn_len) == 0)
            computer_name = cn;
#endif

        return computer_name;
    }

    static void AlignedFree(void* p)
    {
#if defined(_MSC_VER)
        _aligned_free(p);
#else
        // Works for both Linux (__GNUG__) and macOS (__APPLE__)
        free(p);
#endif
    }

    static void* AlignedMalloc(size_t mem_size, size_t mem_alignment)
    {
        void* p = nullptr;
#if defined(_MSC_VER)
        p = _aligned_malloc(mem_size, mem_alignment);
#elif defined(__APPLE__)
        // posix_memalign is safer on macOS than aligned_alloc
        if (posix_memalign(&p, mem_alignment, mem_size) != 0) {
            p = nullptr;
        }
#elif defined(__GNUG__)
        p = aligned_alloc(mem_alignment, mem_size);
#endif
        return p;
    }

    static bool GetAvailableMemory(unsigned long long* mem_size)
    {
        bool rc = false;

#if defined(_MSC_VER)
        MEMORYSTATUSEX ms;
        ms.dwLength = sizeof(ms);
        rc = GlobalMemoryStatusEx(&ms);
        *mem_size = (rc) ? ms.ullAvailPhys : 0ULL;
#elif defined(__APPLE__)
        vm_size_t page_size;
        mach_port_t host = mach_host_self();

        if (host_page_size(host, &page_size) == KERN_SUCCESS) {
            vm_statistics64_data_t vm_stat;
            mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;

            if (host_statistics64(host, HOST_VM_INFO64, (host_info64_t)&vm_stat, &count) == KERN_SUCCESS) {
                // Free pages + speculative (cached but instantly available) pages
                unsigned long long available_pages = vm_stat.free_count + vm_stat.speculative_count;
                *mem_size = available_pages * page_size;
                rc = true;
            }
        }
        if (!rc) *mem_size = 0ULL;
#elif defined(__GNUG__)
        long pages = sysconf(_SC_AVPHYS_PAGES);
        long page_size = sysconf(_SC_PAGE_SIZE);
        rc = (pages != -1 && page_size != -1);
        *mem_size = (rc) ? (unsigned long long)pages * page_size : 0ULL;
#endif

        return rc;
    }

    static bool IsX32()
    {
        return sizeof(void*) == 4;
    }

    static bool IsX64()
    {
        return sizeof(void*) == 8;
    }

    static std::string GetXyyString()
    {
        if (OS::IsX32())
            return "X32";
        if (OS::IsX64())
            return "X64";
        return "Unknown";
    }
};
