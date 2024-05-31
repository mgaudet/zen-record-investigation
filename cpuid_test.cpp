#include <cstdio>
#include <cstdint>

typedef enum  {
  CPUID_GETVENDORSTRING,
  CPUID_GETFEATURES,
  CPUID_GETTLB,
  CPUID_GETSERIAL,
  CPUID_GETCACHEPARAMS = 0x04,
  CPUID_GETEXTENDEDFEATURES = 0x07,
  CPUID_GETEXTENDEDTOPOLOGY = 0x0B,
  CPUID_GETXSAVE = 0x0D,
  CPUID_GETRDTMONITORING = 0x0F,
  CPUID_GETRDTALLOCATION = 0x10,
  CPUID_GETSGX = 0x12,
  CPUID_GETPT = 0x14,
  CPUID_GETSOC = 0x17,
  CPUID_HYPERVISOR = 0x40000000,
  CPUID_INTELEXTENDED = 0x80000000,
  CPUID_INTELFEATURES,
  CPUID_INTELBRANDSTRING,
  CPUID_INTELBRANDSTRINGMORE,
  CPUID_INTELBRANDSTRINGEND,
  CPUID_AMD_CACHE_TOPOLOGY = 0x8000001D,
  CPUID_AMD_PLATFORM_QOS = 0x80000020
} cpuid_requests;

struct CPUIDData {
  uint32_t eax, ebx, ecx, edx;
};

CPUIDData cpuid(uint32_t code, uint32_t subrequest) {
  CPUIDData result;
  asm volatile("cpuid"
               : "=a"(result.eax), "=b"(result.ebx), "=c"(result.ecx),
                 "=d"(result.edx)
               : "a"(code), "c"(subrequest));
  return result;
}

int main(int argc, char** argv) {
  CPUIDData cpuid_data = cpuid(CPUID_GETFEATURES, 0);
  unsigned int cpu_type = cpuid_data.eax & 0xF0FF0;
  unsigned int ext_family = (cpuid_data.eax >> 20) & 0xff;

  fprintf(stdout, "Raw eax: 0x%x, cpu_type 0x%x, ext_family 0x%x\n", cpuid_data.eax, cpu_type, ext_family);
  return 0;
}
