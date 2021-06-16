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
  // CHECK-32-NEXT:  extsh 3, 3
  // CHECK-32-NEXT:  blr
  return __lharx(a);
}

char test_lbarx(volatile unsigned char* a) {
  // CHECK-64-LABEL: test_lbarx
  // CHECK-64:       lbarx 3, 0, 3
  // CHECK-64-NEXT:  clrldi 3, 3, 56
  // CHECK-64-NEXT:  blr

  // CHECK-32-LABEL: test_lbarx
  // CHECK-32:       lbarx 3, 0, 3
  // CHECK-32-NEXT:  clrlwi 3, 3, 24
  // CHECK-32-NEXT:  blr
  return __lbarx(a);
}

int test_stwcx(volatile int* a, int val) {
  // CHECK-64-LABEL: test_stwcx
  // CHECK-64:       stwcx. 4, 0, 3

  // CHECK-32-LABEL: test_stwcx
  // CHECK-32:       stwcx. 4, 0, 3

  return __stwcx(a, val);
}

int test_sthcx(volatile short* a, short val) {
  // CHECK-64-LABEL: test_sthcx
  // CHECK-64:       sthcx. 4, 0, 3

  // CHECK-32-LABEL: test_sthcx
  // CHECK-32:       sthcx. 4, 0, 3

  return __sthcx(a, val);
}

int test_stbcx(volatile char* a, char val) {
  // CHECK-64-LABEL: test_stbcx
  // CHECK-64:       stbcx. 4, 0, 3

  // CHECK-32-LABEL: test_stbcx
  // CHECK-32:       stbcx. 4, 0, 3

  return __stbcx(a, val);
}
