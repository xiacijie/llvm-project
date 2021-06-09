// RUN: %clang -mcpu=pwr8 -c -m32 -O2 -S %s -o - | \
// RUN: FileCheck %s --check-prefix=CHECK-32
// RUN: %clang -mcpu=pwr8 -c -m64 -O2 -S %s -o - | \
// RUN: FileCheck %s --check-prefix=CHECK-64

int test_lwarx(volatile int* a) {
  // CHECK-64-LABEL: test_lwarx
  // CHECK-64:       lwarx 3, 0, 3
  // CHECK-64-NEXT:  extsw 3, 3
  // CHECK-64-NEXT:  blr

  // CHECK-32-LABEL: test_lwarx
  // CHECK-32:       lwarx 3, 0, 3
  // CHECK-32-NEXT:  blr
  return __lwarx(a);
}

short test_lharx(volatile short* a) {
  // CHECK-64-LABEL: test_lharx
  // CHECK-64:       lharx 3, 0, 3
  // CHECK-64-NEXT:  extsh 3, 3
  // CHECK-64-NEXT:  blr

  // CHECK-32-LABEL: test_lharx
  // CHECK-32:       lharx 3, 0, 3
  // CHECK-32-NEXT:  blr
  return __lharx(a);
}

char test_lbarx(volatile char* a) {
  // CHECK-64-LABEL: test_lbarx
  // CHECK-64:       lbarx 3, 0, 3
  // CHECK-64-NEXT:  clrldi 3, 3, 56
  // CHECK-64-NEXT:  blr

  // CHECK-32-LABEL: test_lbarx
  // CHECK-32:       clrlwi 3, 3, 24
  // CHECK-32-NEXT:  blr
  return __lbarx(a);
}
