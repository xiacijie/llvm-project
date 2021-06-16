// RUN: %clang -c -O2 -S -mcpu=pwr8 %s -o - | \
// RUN: FileCheck %s
long test_ldarx(volatile long* a) {
  // CHECK-LABEL: test_ldarx
  // CHECK:       ldarx 3, 0, 3
  // CHECK-NEXT:  blr
  return __ldarx(a);
}

int test_stdcx(volatile long* addr, long val) {
  // CHECK-LABEL: test_stdcx
  // CHECK:       stdcx. 3, 0, 4
  return __stdcx(addr, val);
}
