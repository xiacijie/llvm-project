// RUN: %clang -c -O2 -S -mcpu=pwr8 %s -o - | \
// RUN: FileCheck %s
long test_ldarx(volatile long* a) {
  // CHECK-LABEL: test_ldarx
  // CHECK:       ldarx 3, 0, 3
  // CHECK-NEXT:  blr
  return __ldarx(a);
}
