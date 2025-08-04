#include <stdio.h>
#include <ConditionalMacros.h>

int main(int argc,char **argv) {
  freopen("stdout.txt","w",stdout);
  freopen("stderr.txt","w",stderr);
#ifdef TARGET_CPU_PPC
  printf("TARGET_CPU_PPC is %d\n",TARGET_CPU_PPC);
#endif
#ifdef TARGET_CPU_M68K
  printf("TARGET_CPU_M68K is %d\n",TARGET_CPU_M68K);
#endif
#ifdef TARGET_OS_MAC
  printf("TARGET_OS_MAC is %d\n",TARGET_OS_MAC);
#endif
#ifdef TARGET_RT_MAC_CFM
  printf("TARGET_RT_MAC_CFM is %d\n",TARGET_RT_MAC_CFM);
#endif
#ifdef TARGET_RT_MAC_MACHO
  printf("TARGET_RT_MAC_MACHO is %d\n",TARGET_RT_MAC_MACHO);
#endif
  return 0;
}
