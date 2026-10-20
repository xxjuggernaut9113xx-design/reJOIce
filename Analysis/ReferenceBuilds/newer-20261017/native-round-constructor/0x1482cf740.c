// Selected newer-build routine; caller-supplied label: Constructor_URoundManager
// Address: 0x1482cf740
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: Constructor_URoundManager */

undefined8 * FUN_1482cf740(undefined8 *param_1)

{
  ulonglong *puVar1;
  int iVar2;
  code *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  char cVar11;
  undefined8 *puVar12;
  undefined8 unaff_retaddr;
  undefined1 auStackX_10 [8];
  undefined8 in_stack_fffffffffffffef8;
  undefined4 uVar14;
  undefined8 uVar13;
  undefined4 uVar15;
  undefined8 in_stack_ffffffffffffff00;
  undefined4 *puVar16;
  undefined4 uVar18;
  undefined8 uVar17;
  undefined4 uVar19;
  undefined8 in_stack_ffffffffffffff08;
  undefined4 *puVar20;
  undefined4 uVar22;
  undefined8 uVar21;
  undefined4 uVar23;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 auStack_d0 [42];
  
  uVar14 = (undefined4)((ulonglong)in_stack_fffffffffffffef8 >> 0x20);
  uVar18 = (undefined4)((ulonglong)in_stack_ffffffffffffff00 >> 0x20);
  uVar22 = (undefined4)((ulonglong)in_stack_ffffffffffffff08 >> 0x20);
  FUN_14190d360();
  *param_1 = &UNK_14d1cdf08;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  func_0x0001481f3f20(param_1 + 0x17);
  *(undefined4 *)(param_1 + 0x33) = 5;
  *(undefined1 *)((longlong)param_1 + 0x19c) = 0;
  param_1[0x34] = 0;
  param_1[0x35] = 0;
  param_1[0x36] = 0;
  param_1[0x37] = 0;
  param_1[0x38] = 0;
  param_1[0x39] = 0;
  *(undefined1 *)(param_1 + 0x3a) = 1;
  *(undefined4 *)((longlong)param_1 + 0x1d4) = 3;
  param_1[0x3b] = 0;
  param_1[0x3c] = 0;
  param_1[0x3d] = 0;
  param_1[0x3e] = 0;
  *(undefined4 *)(param_1 + 0x43) = 10;
  *(undefined4 *)((longlong)param_1 + 0x21c) = 0x40f00000;
  *(undefined4 *)(param_1 + 0x44) = 0x3e4ccccd;
  puVar1 = param_1 + 0x45;
  *puVar1 = 0;
  param_1[0x46] = 0;
  *(undefined4 *)(param_1 + 0x47) = 0x3f400000;
  *(undefined4 *)((longlong)param_1 + 0x23c) = 0x3ecccccd;
  *(undefined4 *)(param_1 + 0x48) = 0x3f800000;
  *(undefined4 *)((longlong)param_1 + 0x244) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x49) = 0x3f400000;
  *(undefined4 *)((longlong)param_1 + 0x24c) = 0x3fe00000;
  *(undefined4 *)(param_1 + 0x4a) = 0x40400000;
  *(undefined4 *)((longlong)param_1 + 0x254) = 0x40000000;
  *(undefined4 *)(param_1 + 0x4b) = 2;
  *(undefined4 *)((longlong)param_1 + 0x25c) = 4;
  *(undefined4 *)(param_1 + 0x4c) = 2;
  *(undefined4 *)((longlong)param_1 + 0x264) = 5;
  *(undefined4 *)(param_1 + 0x4d) = 3;
  *(undefined8 *)((longlong)param_1 + 0x26c) = 2;
  *(undefined8 *)((longlong)param_1 + 0x274) = 0;
  *(undefined8 *)((longlong)param_1 + 0x27c) = 0;
  *(undefined8 *)((longlong)param_1 + 0x284) = 0;
  *(undefined8 *)((longlong)param_1 + 0x28c) = 0;
  *(undefined8 *)((longlong)param_1 + 0x294) = 0;
  *(undefined8 *)((longlong)param_1 + 0x29c) = 0;
  *(undefined8 *)((longlong)param_1 + 0x2a4) = 0;
  param_1[0x56] = 0;
  param_1[0x57] = 0;
  param_1[0x58] = 0;
  param_1[0x59] = 0;
  param_1[0x5a] = 0;
  param_1[0x5b] = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0x3f000000;
  *(undefined8 *)((longlong)param_1 + 0x2e4) = 0x40200000;
  *(undefined8 *)((longlong)param_1 + 0x2ec) = 0x3fc00000;
  *(undefined8 *)((longlong)param_1 + 0x2f4) = 0x3f800000;
  *(undefined8 *)((longlong)param_1 + 0x2fc) = 0x3f800000;
  *(undefined8 *)((longlong)param_1 + 0x304) = 0x3f800000;
  *(undefined4 *)((longlong)param_1 + 0x30c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x62) = 0x3ecccccd;
  *(undefined4 *)((longlong)param_1 + 0x314) = 0x3e99999a;
  *(undefined4 *)(param_1 + 99) = 0x3e4ccccd;
  *(undefined4 *)((longlong)param_1 + 0x31c) = 0x3e19999a;
  *(undefined4 *)(param_1 + 100) = 0x3e19999a;
  *(undefined4 *)((longlong)param_1 + 0x324) = 0x3e19999a;
  *(undefined4 *)(param_1 + 0x65) = 0x3e4ccccd;
  *(undefined4 *)((longlong)param_1 + 0x32c) = 0x3dcccccd;
  *(undefined4 *)(param_1 + 0x66) = 0x3f19999a;
  *(undefined4 *)((longlong)param_1 + 0x334) = 0x3d75c28f;
  *(undefined4 *)(param_1 + 0x67) = 0x3f666666;
  *(undefined4 *)((longlong)param_1 + 0x33c) = 0x40400000;
  *(undefined4 *)(param_1 + 0x68) = 0x40000000;
  *(undefined4 *)((longlong)param_1 + 0x344) = 0x40000000;
  *(undefined4 *)(param_1 + 0x69) = 0x40000000;
  *(undefined4 *)((longlong)param_1 + 0x34c) = 0x40000000;
  *(undefined4 *)(param_1 + 0x6a) = 0x40000000;
  param_1[0x6b] = 0;
  param_1[0x6c] = 0;
  param_1[0x6d] = 0;
  param_1[0x6e] = 0;
  uStack_d8 = 2;
  puVar20 = (undefined4 *)*puVar1;
  if ((puVar20 <= &uStack_d8) && (&uStack_d8 < puVar20 + *(int *)((longlong)param_1 + 0x234))) {
    puVar16 = &uStack_d8;
    uVar14 = 1;
    cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,puVar16,
                           puVar20,(longlong)*(int *)((longlong)param_1 + 0x234),
                           (longlong)*(int *)(param_1 + 0x46),4);
    uVar18 = (undefined4)((ulonglong)puVar16 >> 0x20);
    uVar22 = (undefined4)((ulonglong)puVar20 >> 0x20);
    if (cVar11 != '\0') {
      pcVar3 = (code *)swi(3);
      puVar12 = (undefined8 *)(*pcVar3)();
      return puVar12;
    }
  }
  iVar2 = *(int *)(param_1 + 0x46);
  *(uint *)(param_1 + 0x46) = iVar2 + 1U;
  if (*(uint *)((longlong)param_1 + 0x234) < iVar2 + 1U) {
    FUN_140d21b90(puVar1,iVar2);
  }
  *(undefined4 *)(*puVar1 + (longlong)iVar2 * 4) = uStack_d8;
  puVar1 = param_1 + 0x45;
  uStack_d4 = 3;
  puVar20 = (undefined4 *)*puVar1;
  if ((puVar20 <= &uStack_d4) && (&uStack_d4 < puVar20 + *(int *)((longlong)param_1 + 0x234))) {
    puVar16 = &uStack_d4;
    uVar14 = 1;
    cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,puVar16,
                           puVar20,(longlong)*(int *)((longlong)param_1 + 0x234),
                           (longlong)*(int *)(param_1 + 0x46),4);
    uVar18 = (undefined4)((ulonglong)puVar16 >> 0x20);
    uVar22 = (undefined4)((ulonglong)puVar20 >> 0x20);
    if (cVar11 != '\0') {
      pcVar3 = (code *)swi(3);
      puVar12 = (undefined8 *)(*pcVar3)();
      return puVar12;
    }
  }
  iVar2 = *(int *)(param_1 + 0x46);
  *(uint *)(param_1 + 0x46) = iVar2 + 1U;
  if (*(uint *)((longlong)param_1 + 0x234) < iVar2 + 1U) {
    FUN_140d21b90(puVar1,iVar2);
  }
  *(undefined4 *)(*puVar1 + (longlong)iVar2 * 4) = uStack_d4;
  puVar1 = param_1 + 0x45;
  auStack_d0[0] = 4;
  puVar20 = (undefined4 *)*puVar1;
  if ((puVar20 <= auStack_d0) && (auStack_d0 < puVar20 + *(int *)((longlong)param_1 + 0x234))) {
    puVar16 = auStack_d0;
    uVar14 = 1;
    cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,puVar16,
                           puVar20,(longlong)*(int *)((longlong)param_1 + 0x234),
                           (longlong)*(int *)(param_1 + 0x46),4);
    uVar18 = (undefined4)((ulonglong)puVar16 >> 0x20);
    uVar22 = (undefined4)((ulonglong)puVar20 >> 0x20);
    if (cVar11 != '\0') {
      pcVar3 = (code *)swi(3);
      puVar12 = (undefined8 *)(*pcVar3)();
      return puVar12;
    }
  }
  iVar2 = *(int *)(param_1 + 0x46);
  *(uint *)(param_1 + 0x46) = iVar2 + 1U;
  if (*(uint *)((longlong)param_1 + 0x234) < iVar2 + 1U) {
    FUN_140d21b90(puVar1,iVar2);
  }
  *(undefined4 *)(*puVar1 + (longlong)iVar2 * 4) = auStack_d0[0];
  *(undefined4 *)(param_1 + 0x4e) = 0x42340000;
  *(undefined4 *)((longlong)param_1 + 0x274) = 0x41c80000;
  *(undefined4 *)(param_1 + 0x4f) = 0x41a00000;
  *(undefined4 *)((longlong)param_1 + 0x27c) = 0x40a00000;
  *(undefined4 *)(param_1 + 0x50) = 0x40a00000;
  *(undefined4 *)((longlong)param_1 + 0x284) = 0x41b00000;
  *(undefined4 *)(param_1 + 0x51) = 0x420c0000;
  *(undefined4 *)((longlong)param_1 + 0x28c) = 0x41e00000;
  *(undefined4 *)(param_1 + 0x52) = 0x41400000;
  *(undefined4 *)((longlong)param_1 + 0x294) = 0x41200000;
  *(undefined4 *)(param_1 + 0x53) = 0x40a00000;
  *(undefined4 *)((longlong)param_1 + 0x29c) = 0x420c0000;
  *(undefined4 *)(param_1 + 0x54) = 0x42340000;
  *(undefined4 *)((longlong)param_1 + 0x2a4) = 0x420c0000;
  *(undefined4 *)(param_1 + 0x55) = 0x41c80000;
  puVar12 = param_1 + 0x56;
  *(undefined4 *)(param_1 + 0x57) = 0;
  if (*(int *)((longlong)param_1 + 700) < 0) {
    FUN_14830c190(puVar12,0);
  }
  uVar15 = _DAT_14c561aa0;
  uVar6 = _DAT_14bf8d138;
  uVar5 = _DAT_14bf56a58;
  uVar4 = _DAT_14bf3cd5c;
  uVar21 = CONCAT44(uVar22,_DAT_14bf3cd3c);
  uVar17 = CONCAT44(uVar18,_DAT_14bf3cd5c);
  uVar13 = CONCAT44(uVar14,_DAT_14bf8d138);
  FUN_1482d1cb0(auStackX_10,puVar12,_DAT_14c561aa0,_DAT_14bf56a58,uVar13,uVar17,uVar21);
  uVar22 = _DAT_14c06d510;
  uVar18 = _DAT_14bfe47b8;
  uVar14 = _DAT_14bf8d120;
  uVar21 = CONCAT44((int)((ulonglong)uVar21 >> 0x20),uVar4);
  uVar17 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),_DAT_14bf8d120);
  uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),_DAT_14bfe47b8);
  FUN_1482d1cb0(auStackX_10,puVar12,_DAT_14c06d510,uVar5,uVar13,uVar17,uVar21);
  uVar9 = _DAT_14c1bfee8;
  uVar21 = CONCAT44((int)((ulonglong)uVar21 >> 0x20),uVar14);
  uVar17 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),_DAT_14bf8d124);
  uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),_DAT_14c18d0b8);
  FUN_1482d1cb0(auStackX_10,puVar12,_DAT_14c1bfee8,uVar5,uVar13,uVar17,uVar21);
  uVar8 = _DAT_14c127898;
  uVar7 = _DAT_14c06d514;
  uVar21 = CONCAT44((int)((ulonglong)uVar21 >> 0x20),_DAT_14c127898);
  uVar17 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),_DAT_14c127898);
  uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),_DAT_14c18d0bc);
  FUN_1482d1cb0(auStackX_10,puVar12,uVar18,_DAT_14c06d514,uVar13,uVar17,uVar21);
  uVar21 = CONCAT44((int)((ulonglong)uVar21 >> 0x20),uVar6);
  uVar17 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),uVar6);
  uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),_DAT_14c18d0c0);
  FUN_1482d1cb0(auStackX_10,puVar12,_DAT_14bfe47b4,_DAT_14c21d090,uVar13,uVar17,uVar21);
  uVar18 = _DAT_14c1e1048;
  uVar21 = CONCAT44((int)((ulonglong)uVar21 >> 0x20),_DAT_14c1e1048);
  uVar17 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),_DAT_14c1e1048);
  uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),_DAT_14c16e008);
  FUN_1482d1cb0(auStackX_10,puVar12,uVar8,uVar15,uVar13,uVar17,uVar21);
  uVar15 = (undefined4)((ulonglong)uVar13 >> 0x20);
  uVar19 = (undefined4)((ulonglong)uVar17 >> 0x20);
  uVar23 = (undefined4)((ulonglong)uVar21 >> 0x20);
  puVar12 = param_1 + 0x58;
  *(undefined4 *)(param_1 + 0x59) = 0;
  if (*(int *)((longlong)param_1 + 0x2cc) < 0) {
    FUN_14830c190(puVar12,0);
  }
  uVar10 = _DAT_14c1ce750;
  uVar21 = CONCAT44(uVar23,uVar4);
  uVar17 = CONCAT44(uVar19,uVar14);
  uVar13 = CONCAT44(uVar15,_DAT_14c1ce750);
  FUN_1482d1cb0(auStackX_10,puVar12,uVar9,uVar7,uVar13,uVar17,uVar21);
  uVar21 = CONCAT44((int)((ulonglong)uVar21 >> 0x20),uVar14);
  uVar17 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),uVar8);
  uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),_DAT_14c18d0bc);
  FUN_1482d1cb0(auStackX_10,puVar12,uVar10,_DAT_14c21d090,uVar13,uVar17,uVar21);
  uVar21 = CONCAT44((int)((ulonglong)uVar21 >> 0x20),uVar8);
  uVar17 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),uVar6);
  uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),_DAT_14c19ed88);
  FUN_1482d1cb0(auStackX_10,puVar12,uVar18,_DAT_14c16e008,uVar13,uVar17,uVar21);
  uVar21 = CONCAT44((int)((ulonglong)uVar21 >> 0x20),uVar18);
  uVar17 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),uVar18);
  uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),uVar7);
  FUN_1482d1cb0(auStackX_10,puVar12,_DAT_14c18d0b4,_DAT_14c18d0c0,uVar13,uVar17,uVar21);
  uVar21 = CONCAT44((int)((ulonglong)uVar21 >> 0x20),uVar10);
  uVar17 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),uVar10);
  uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),uVar5);
  FUN_1482d1cb0(auStackX_10,puVar12,_DAT_14bf8d124,uVar22,uVar13,uVar17,uVar21);
  uVar8 = _DAT_14c18d0bc;
  uVar21 = CONCAT44((int)((ulonglong)uVar21 >> 0x20),uVar9);
  uVar17 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),uVar9);
  uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),_DAT_14bfb66c0);
  FUN_1482d1cb0(auStackX_10,puVar12,uVar14,_DAT_14c18d0bc,uVar13,uVar17,uVar21);
  uVar15 = (undefined4)((ulonglong)uVar13 >> 0x20);
  uVar19 = (undefined4)((ulonglong)uVar17 >> 0x20);
  uVar23 = (undefined4)((ulonglong)uVar21 >> 0x20);
  puVar12 = param_1 + 0x5a;
  *(undefined4 *)(param_1 + 0x5b) = 0;
  if (*(int *)((longlong)param_1 + 0x2dc) < 0) {
    FUN_14830c190(puVar12,0);
  }
  FUN_1482d1cb0(auStackX_10,puVar12,uVar14,_DAT_14c18d0c0,CONCAT44(uVar15,uVar7),
                CONCAT44(uVar19,uVar22),CONCAT44(uVar23,uVar6));
  FUN_1482d1cb0(auStackX_10,puVar12,_DAT_14bf3cd64,uVar22,uVar5,_DAT_14c561aa0,uVar18);
  uVar14 = _DAT_14bfb66c0;
  FUN_1482d1cb0(auStackX_10,puVar12,uVar4,uVar8,_DAT_14bfb66c0,uVar7,uVar10);
  uVar18 = _DAT_14c561aa4;
  FUN_1482d1cb0(auStackX_10,puVar12,_DAT_14bf3cd58,uVar9,_DAT_14c561aa4,uVar5,uVar22);
  FUN_1482d1cb0(auStackX_10,puVar12,_DAT_14bf3cd3c,uVar10,_DAT_14bf8d158,uVar14,uVar7);
  FUN_1482d1cb0(auStackX_10,puVar12,_DAT_14bf56a24,_DAT_14bfe47b8,_DAT_14d21cc90,uVar18,uVar5);
  return param_1;
}

