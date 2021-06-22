// RUN: %clang_cc1 -triple=powerpc-unknown-aix -O2 -S %s -o - | \
// RUN: FileCheck %s --check-prefix=CHECK-AIX
// RUN: %clang_cc1 -triple=powerpc64-unknown-aix -O2 -S %s -o - | \
// RUN: FileCheck %s --check-prefix=CHECK-AIX
// RUN: %clang_cc1 -triple=powerpc64le-unknown-unknown -O2 -S %s \
// RUN:  -o - | FileCheck %s --check-prefix=CHECK-COMMON
// RUN: %clang_cc1 -triple=powerpc64be-unknown-unknown -O2 -S %s \
// RUN:  -o - | FileCheck %s --check-prefix=CHECK-COMMON

int test_lwarx(volatile int* a) {
  // CHECK-COMMON-LABEL: test_lwarx
  // CHECK-COMMON:       lwarx 3, 0, 3
  // CHECK-COMMON-NEXT:  extsw 3, 3
  // CHECK-COMMON-NEXT:  blr

  // CHECK-AIX-LABEL: test_lwarx
  // CHECK-AIX:       lwarx 3, 0, 3
  // CHECK-AIX-NEXT:  blr
  return __lwarx(a);
}

short test_lharx(volatile short* a) {
  // CHECK-COMMON-LABEL: test_lharx
  // CHECK-COMMON:       lharx 3, 0, 3
  // CHECK-COMMON-NEXT:  extsh 3, 3
  // CHECK-COMMON-NEXT:  blr

  // CHECK-AIX-LABEL: test_lharx
  // CHECK-AIX:       lharx 3, 0, 3
  // CHECK-AIX-NEXT:  extsh 3, 3
  // CHECK-AIX-NEXT:  blr
  return __lharx(a);
}

char test_lbarx(volatile unsigned char* a) {
  // CHECK-COMMON-LABEL: test_lbarx
  // CHECK-COMMON:       lbarx 3, 0, 3
  // CHECK-COMMON-NEXT:  clrldi 3, 3, 56
  // CHECK-COMMON-NEXT:  blr

  // CHECK-AIX-LABEL: test_lbarx
  // CHECK-AIX:       lbarx 3, 0, 3
  // CHECK-AIX-NEXT:  extsb 3, 3
  // CHECK-AIX-NEXT:  blr
  return __lbarx(a);
}

int test_stwcx(volatile int* a, int val) {
  // CHECK-COMMON-LABEL: test_stwcx
  // CHECK-COMMON:       stwcx. 4, 0, 3

  // CHECK-AIX-LABEL: test_stwcx
  // CHECK-AIX:       stwcx. 4, 0, 3

  return __stwcx(a, val);
}

int test_sthcx(volatile short* a, short val) {
  // CHECK-COMMON-LABEL: test_sthcx
  // CHECK-COMMON:       sthcx. 4, 0, 3

  // CHECK-AIX-LABEL: test_sthcx
  // CHECK-AIX:       sthcx. 4, 0, 3

  return __sthcx(a, val);
}

int test_stbcx(volatile char* a, char val) {
  // CHECK-COMMON-LABEL: test_stbcx
  // CHECK-COMMON:       stbcx. 4, 0, 3

  // CHECK-AIX-LABEL: test_stbcx
  // CHECK-AIX:       stbcx. 4, 0, 3

  return __stbcx(a, val);
}
