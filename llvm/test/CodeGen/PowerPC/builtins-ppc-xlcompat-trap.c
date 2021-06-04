// RUN: clang -mcpu=pwr7 -m64 -O2 -c -S %s -o - | FileCheck %s

long long lla, llb;
double da;

void test_tdlgt(void) {
// CHECK-LABEL: test_tdlgt
// CHECK: tdlgt
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 1);
}

void test_xl_tdlgt(void) {
// CHECK-LABEL: test_xl_tdlgt
// CHECK: tdlgt
// CHECK: blr

  __tdw(lla, llb, 1);
}

void test_tdllt(void) {
// CHECK-LABEL: test_tdllt
// CHECK: tdllt
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 2);
}

void test_xl_tdllt(void) {
// CHECK-LABEL: test_xl_tdllt
// CHECK: tdllt
// CHECK: blr

  __tdw(lla, llb, 2);
}

void test_tdne3(void) {
// CHECK-LABEL: test_tdne3
// CHECK: tdne
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 3);
}

void test_xl_tdne3(void) {
// CHECK-LABEL: test_xl_tdne3
// CHECK: tdne
// CHECK: blr

  __tdw(lla, llb, 3);
}

void test_tdeq(void) {
// CHECK-LABEL: test_tdeq
// CHECK: tdeq
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 4);
}

void test_xl_tdeq(void) {
// CHECK-LABEL: test_xl_tdeq
// CHECK: tdeq
// CHECK: blr

  __tdw(lla, llb, 4);
}

void test_tdlge(void) {
// CHECK-LABEL: test_tdlge
// CHECK: tdlge
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 5);
}

void test_xl_tdlge(void) {
// CHECK-LABEL: test_xl_tdlge
// CHECK: tdlge
// CHECK: blr

  __tdw(lla, llb, 5);
}

void test_tdlle(void) {
// CHECK-LABEL: test_tdlle
// CHECK: tdlle
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 6);
}

void test_xl_tdlle(void) {
// CHECK-LABEL: test_xl_tdlle
// CHECK: tdlle
// CHECK: blr

  __tdw(lla, llb, 6);
}

void test_tdgt(void) {
// CHECK-LABEL: test_tdgt
// CHECK: tdgt
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 8);
}

void test_xl_tdgt(void) {
// CHECK-LABEL: test_xl_tdgt
// CHECK: tdgt
// CHECK: blr

  __tdw(lla, llb, 8);
}

void test_tdge(void) {
// CHECK-LABEL: test_tdge
// CHECK: tdge
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 12);
}

void test_xl_tdge(void) {
// CHECK-LABEL: test_xl_tdge
// CHECK: tdge
// CHECK: blr

  __tdw(lla, llb, 12);
}

void test_tdlt(void) {
// CHECK-LABEL: test_tdlt
// CHECK: tdlt
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 16);
}

void test_xl_tdlt(void) {
// CHECK-LABEL: test_xl_tdlt
// CHECK: tdlt
// CHECK: blr

  __tdw(lla, llb, 16);
}

void test_tdle(void) {
// CHECK-LABEL: test_tdle
// CHECK: tdle
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 20);
}

void test_xl_tdle(void) {
// CHECK-LABEL: test_xl_tdle
// CHECK: tdle
// CHECK: blr

  __tdw(lla, llb, 20);
}

void test_tdne24(void) {
// CHECK-LABEL: test_tdne24
// CHECK: tdne
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 24);
}

void test_xl_tdne24(void) {
// CHECK-LABEL: test_xl_tdne24
// CHECK: tdne
// CHECK: blr

  __tdw(lla, llb, 24);
}

void test_tdeq31(void) {
// CHECK-LABEL: test_tdeq31
// CHECK: tdeq
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 31);
}

void test_xl_tdeq31(void) {
// CHECK-LABEL: test_xl_tdeq31
// CHECK: tdeq
// CHECK: blr

  __tdw(lla, llb, 31);
}

void test_td_no_match(void) {
// CHECK-LABEL: test_td_no_match
// CHECK: td 13
// CHECK: blr

  __builtin_ppc_tdw(lla, llb, 13);
}

void test_xl_td_no_match(void) {
// CHECK-LABEL: test_xl_td_no_match
// CHECK: td 13
// CHECK: blr

  __tdw(lla, llb, 13);
}

void test_trapd(void) {
// CHECK-LABEL: test_trapd
// CHECK: tdnei 3, 0
// CHECK: blr
  __builtin_ppc_trapd(da);
}

void test_xl_trapd(void) {
// CHECK-LABEL: test_xl_trapd
// CHECK: tdnei 3, 0
// CHECK: blr
  __trapd(da);
}
