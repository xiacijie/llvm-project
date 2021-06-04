// RUN: clang -mcpu=pwr9 -O2 -c -S %s -o - | FileCheck %s

double a;

double test_fcfid(double a) {
  // CHECK-LABEL: test_fcfid
  // CHECK: xscvsxddp 1, 1
  // CHECK: blr
  return __builtin_ppc_fcfid(a);
}

double test_xl_fcfid(double a) {
  // CHECK-LABEL: test_xl_fcfid
  // CHECK: xscvsxddp 1, 1
  // CHECK: blr
  return __fcfid(a);
}

double test_fcfud(double a) {
  // CHECK-LABEL: test_fcfud
  // CHECK: xscvuxddp 1, 1
  // CHECK: blr
  return __builtin_ppc_fcfud(a);
}

double test_xl_fcfud(double a) {
  // CHECK-LABEL: test_xl_fcfud
  // CHECK: xscvuxddp 1, 1
  // CHECK: blr
  return __fcfud(a);
}

double test_fctid(double a) {
  // CHECK-LABEL: test_fctid
  // CHECK: fctid 1, 1
  // CHECK: blr
  return __builtin_ppc_fctid(a);
}

double test_xl_fctid(double a) {
  // CHECK-LABEL: test_xl_fctid
  // CHECK: fctid 1, 1
  // CHECK: blr
  return __fctid(a);
}

double test_fctidz(double a) {
  // CHECK-LABEL: test_fctidz
  // CHECK: xscvdpsxds 1, 1
  // CHECK: blr
  return __builtin_ppc_fctidz(a);
}

double test_xl_fctidz(double a) {
  // CHECK-LABEL: test_xl_fctidz
  // CHECK: xscvdpsxds 1, 1
  // CHECK: blr
  return __fctidz(a);
}

double test_fctiw(double a) {
  // CHECK-LABEL: test_fctiw
  // CHECK: fctiw 1, 1
  // CHECK: blr
  return __builtin_ppc_fctiw(a);
}

double test_xl_fctiw(double a) {
  // CHECK-LABEL: test_xl_fctiw
  // CHECK: fctiw 1, 1
  // CHECK: blr
  return __fctiw(a);
}

double test_fctiwz(double a) {
  // CHECK-LABEL: test_fctiwz
  // CHECK: xscvdpsxws 1, 1
  // CHECK: blr
  return __builtin_ppc_fctiwz(a);
}

double test_xl_fctiwz(double a) {
  // CHECK-LABEL: test_xl_fctiwz
  // CHECK: xscvdpsxws 1, 1
  // CHECK: blr
  return __fctiwz(a);
}

double test_fctudz(double a) {
  // CHECK-LABEL: test_fctudz
  // CHECK: xscvdpuxds 1, 1
  // CHECK: blr
  return __builtin_ppc_fctudz(a);
}

double test_xl_fctudz(double a) {
  // CHECK-LABEL: test_xl_fctudz
  // CHECK: xscvdpuxds 1, 1
  // CHECK: blr
  return __fctudz(a);
}

double test_fctuwz(double a) {
  // CHECK-LABEL: test_fctuwz
  // CHECK: xscvdpuxws 1, 1
  // CHECK: blr
  return __builtin_ppc_fctuwz(a);
}

double test_xl_fctuwz(double a) {
  // CHECK-LABEL: test_xl_fctuwz
  // CHECK: xscvdpuxws 1, 1
  // CHECK: blr
  return __fctuwz(a);
}
