// Selected newer-build routine; caller-supplied label: EndSession_UProgressionManager
// Address: 0x1482ddd60
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: EndSession_UProgressionManager */

void FUN_1482ddd60(longlong *param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined8 uVar7;
  longlong lVar8;
  undefined *puVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  ulonglong *puVar12;
  uint uVar13;
  undefined7 uVar14;
  longlong *plVar15;
  uint uVar16;
  undefined8 *puVar17;
  int iVar18;
  longlong *plVar19;
  ulonglong *puVar20;
  longlong lVar21;
  ulonglong *puVar22;
  float fVar23;
  double dVar24;
  undefined8 unaff_retaddr;
  longlong *plStackX_8;
  undefined1 auStackX_18 [8];
  int iStackX_20;
  undefined8 in_stack_fffffffffffffde8;
  undefined4 uVar25;
  undefined8 in_stack_fffffffffffffdf0;
  undefined8 uVar26;
  undefined4 uVar27;
  undefined8 in_stack_fffffffffffffdf8;
  undefined8 uVar28;
  undefined4 uVar29;
  undefined8 in_stack_fffffffffffffe08;
  undefined4 uVar30;
  longlong lStack_1c8;
  int iStack_1c0;
  undefined4 uStack_1bc;
  uint uStack_1b8;
  ulonglong *puStack_1b0;
  undefined8 uStack_1a8;
  ulonglong *puStack_1a0;
  ulonglong *puStack_198;
  undefined8 uStack_190;
  undefined8 *puStack_188;
  uint uStack_180;
  ulonglong *puStack_178;
  ulonglong *puStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  longlong lStack_158;
  ulonglong uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined1 auStack_f8 [64];
  longlong *plStack_b8;
  int iStack_b0;
  
  uVar7 = (**(code **)(*param_1 + 0x188))();
  uVar7 = func_0x000147a1ed70(uVar7);
  lVar8 = FUN_14789e810(uVar7,param_1 + 9);
  if (lVar8 != 0) {
    FUN_1478cf910(uVar7,param_1[9]);
  }
  param_1[9] = 0;
  lVar8 = (**(code **)(*param_1 + 0x188))(param_1);
  dVar24 = *(double *)(lVar8 + 0x740) - (double)*(float *)(param_1 + 0x76);
  dVar24 = (dVar24 + dVar24) - _DAT_14bf2ec00;
  plVar19 = param_1 + 0x46;
  uVar7 = FUN_148300f90(auStack_f8,plVar19,param_2);
  FUN_1481e5cc0(plVar19,uVar7);
  uVar25 = (undefined4)((ulonglong)in_stack_fffffffffffffde8 >> 0x20);
  uVar27 = (undefined4)((ulonglong)in_stack_fffffffffffffdf0 >> 0x20);
  uVar29 = (undefined4)((ulonglong)in_stack_fffffffffffffdf8 >> 0x20);
  uVar30 = (undefined4)((ulonglong)in_stack_fffffffffffffe08 >> 0x20);
  plVar15 = plStack_b8;
  for (; iStack_b0 != 0; iStack_b0 = iStack_b0 + -1) {
    if (*plVar15 != 0) {
      FUN_140e289f0();
    }
    uVar25 = (undefined4)((ulonglong)in_stack_fffffffffffffde8 >> 0x20);
    uVar27 = (undefined4)((ulonglong)in_stack_fffffffffffffdf0 >> 0x20);
    uVar29 = (undefined4)((ulonglong)in_stack_fffffffffffffdf8 >> 0x20);
    uVar30 = (undefined4)((ulonglong)in_stack_fffffffffffffe08 >> 0x20);
    plVar15 = plVar15 + 2;
  }
  if (plStack_b8 != (longlong *)0x0) {
    FUN_140e289f0(plStack_b8);
  }
  iVar4 = (int)((longlong)ROUND(dVar24) >> 1);
  if (iVar4 < (int)param_1[0x4b]) {
    iVar4 = (int)param_1[0x4b];
  }
  *(int *)(param_1 + 0x4b) = iVar4;
  iVar18 = 0;
  if (0 < iVar4) {
    iVar5 = (int)param_1[0x51];
    if ((int)param_1[0x51] < 0) {
      iVar5 = iVar18;
    }
    fVar23 = ((float)iVar5 / (float)iVar4) * _DAT_14bf56a6c;
    iVar5 = (int)ROUND((fVar23 + fVar23) - _DAT_14bf3cd28) >> 1;
    iVar4 = 100;
    if (iVar5 < 100) {
      iVar4 = iVar5;
    }
    if (0 < iVar4) {
      iVar18 = iVar4;
    }
  }
  *(int *)((longlong)param_1 + 0x28c) = iVar18;
  iVar4 = FUN_1482d90e0(param_1,plVar19);
  if (2 < DAT_14edc6208) {
    puVar9 = &UNK_14bf4e28c;
    if (*(char *)((longlong)param_1 + 0x25c) != '\0') {
      puVar9 = &UNK_14bf4e298;
    }
    uVar28 = CONCAT44(uVar29,(int)param_1[0x47]);
    uVar26 = CONCAT44(uVar27,*(undefined4 *)((longlong)param_1 + 0x23c));
    uVar7 = CONCAT44(uVar25,*(undefined4 *)((longlong)param_1 + 0x234));
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d211ef8,iVar4,(int)*plVar19,uVar7,uVar26,uVar28,
                  (int)param_1[0x4b],puVar9);
    uVar25 = (undefined4)((ulonglong)uVar7 >> 0x20);
    uVar27 = (undefined4)((ulonglong)uVar26 >> 0x20);
    uVar29 = (undefined4)((ulonglong)uVar28 >> 0x20);
    uVar30 = (undefined4)((ulonglong)puVar9 >> 0x20);
  }
  FUN_140cf7780(&lStack_158,&UNK_14d212340);
  lVar8 = lStack_158;
  if (0 < iVar4) {
    *(int *)(param_1 + 8) = (int)param_1[8] + iVar4;
    *(int *)((longlong)param_1 + 0x54) = *(int *)((longlong)param_1 + 0x54) + iVar4;
    plStackX_8 = &lStack_1c8;
    lStack_1c8 = 0;
    iVar18 = (int)uStack_150;
    iStack_1c0 = iVar18;
    if (iVar18 == 0) {
      uStack_1bc = 0;
    }
    else {
      FUN_140ca40a0(&lStack_1c8,uStack_150 & 0xffffffff,0);
      func_0x00014ba120de(lStack_1c8,lVar8,(longlong)iVar18 * 2);
    }
    plStackX_8 = &lStack_1c8;
    FUN_1481e87b0(param_1 + 0x7f,iVar4,&lStack_1c8);
    if (lStack_1c8 != 0) {
      FUN_140e289f0();
    }
    FUN_1482d9830(param_1);
    uStack_168 = 0;
    uStack_160 = 0;
    FUN_148318be0(param_1,0xf,iVar4,&uStack_168);
    FUN_14830f490(param_1);
  }
  if (lStack_158 != 0) {
    FUN_140e289f0();
  }
  FUN_148318970(param_1,0,(int)*plVar19);
  FUN_148318970(param_1,1,*(undefined4 *)((longlong)param_1 + 0x234));
  FUN_148318970(param_1,2,(int)param_1[0x47]);
  FUN_148318970(param_1,3,*(undefined4 *)((longlong)param_1 + 0x23c));
  FUN_148318970(param_1,4,(int)param_1[0x48]);
  FUN_148318970(param_1,0x11,(int)param_1[0x50]);
  FUN_148318970(param_1,0x12,*(undefined4 *)((longlong)param_1 + 0x284));
  FUN_148318970(param_1,0xc,(int)param_1[0x4b]);
  FUN_148318970(param_1,6,*(undefined4 *)((longlong)param_1 + 0x244));
  FUN_148318970(param_1,8,*(undefined4 *)((longlong)param_1 + 0x24c));
  FUN_148318970(param_1,10,(int)param_1[0x4a]);
  FUN_148318970(param_1,0x17,(int)param_1[0x51]);
  FUN_148318970(param_1,0x13,(int)param_1[0x52]);
  FUN_148318970(param_1,0x10,*(undefined4 *)((longlong)param_1 + 0x294));
  FUN_148318970(param_1,0x28,(int)param_1[0x53]);
  FUN_148318970(param_1,0x18,*(undefined4 *)((longlong)param_1 + 0x28c));
  FUN_148318970(param_1,0x1a,(int)param_1[0x54]);
  FUN_148318970(param_1,0x1b,*(undefined4 *)((longlong)param_1 + 0x2a4));
  FUN_148318970(param_1,0x1c,(int)param_1[0x55]);
  FUN_148318970(param_1,0x1d,*(undefined4 *)((longlong)param_1 + 0x2ac));
  FUN_148318970(param_1,0x1e,(int)param_1[0x56]);
  FUN_148318970(param_1,0x1f,*(undefined4 *)((longlong)param_1 + 0x2b4));
  FUN_148318970(param_1,0x20,(int)param_1[0x57]);
  FUN_148318970(param_1,0x21,*(undefined4 *)((longlong)param_1 + 700));
  FUN_148318970(param_1,0x29,(int)param_1[0x5b]);
  FUN_148318970(param_1,0x22,(int)param_1[0x58]);
  FUN_148318970(param_1,0x23,*(undefined4 *)((longlong)param_1 + 0x2c4));
  FUN_148318970(param_1,0x24,(int)param_1[0x59]);
  FUN_148318970(param_1,0x25,*(undefined4 *)((longlong)param_1 + 0x2cc));
  FUN_148318970(param_1,0x26,(int)param_1[0x5a]);
  FUN_148318970(param_1,0x27,*(undefined4 *)((longlong)param_1 + 0x2d4));
  FUN_148318970(param_1,0x2a,*(undefined4 *)((longlong)param_1 + 0x2dc));
  FUN_148318970(param_1,0x2b,(int)param_1[0x5c]);
  FUN_148318970(param_1,0x2c,*(undefined4 *)((longlong)param_1 + 0x2e4));
  FUN_148318970(param_1,0x2d,(int)param_1[0x5d]);
  FUN_148318970(param_1,0x2e,*(undefined4 *)((longlong)param_1 + 0x2ec));
  *(int *)(param_1 + 0x5e) = (int)param_1[0x5e] + (int)*plVar19;
  *(int *)((longlong)param_1 + 0x2f4) =
       *(int *)((longlong)param_1 + 0x2f4) + *(int *)((longlong)param_1 + 0x234);
  *(int *)(param_1 + 0x5f) = (int)param_1[0x5f] + (int)param_1[0x47];
  *(int *)((longlong)param_1 + 0x2fc) =
       *(int *)((longlong)param_1 + 0x2fc) + *(int *)((longlong)param_1 + 0x23c);
  iVar18 = (int)param_1[99] + (int)param_1[0x4b];
  *(int *)(param_1 + 99) = iVar18;
  *(int *)((longlong)param_1 + 0x304) =
       *(int *)((longlong)param_1 + 0x304) + *(int *)((longlong)param_1 + 0x244);
  *(int *)((longlong)param_1 + 0x30c) =
       *(int *)((longlong)param_1 + 0x30c) + *(int *)((longlong)param_1 + 0x24c);
  *(int *)(param_1 + 0x61) = (int)param_1[0x61] + (int)param_1[0x49];
  *(int *)(param_1 + 0x62) = (int)param_1[0x62] + (int)param_1[0x4a];
  *(int *)((longlong)param_1 + 0x314) =
       *(int *)((longlong)param_1 + 0x314) + *(int *)((longlong)param_1 + 0x254);
  uVar13 = (int)param_1[0x69] + (int)param_1[0x51];
  uVar10 = (ulonglong)uVar13;
  *(uint *)(param_1 + 0x69) = uVar13;
  *(int *)(param_1 + 0x6a) = (int)param_1[0x6a] + (int)param_1[0x52];
  *(int *)((longlong)param_1 + 0x354) =
       *(int *)((longlong)param_1 + 0x354) + *(int *)((longlong)param_1 + 0x294);
  *(int *)(param_1 + 0x6b) = (int)param_1[0x6b] + (int)param_1[0x53];
  *(int *)((longlong)param_1 + 0x35c) =
       *(int *)((longlong)param_1 + 0x35c) + *(int *)((longlong)param_1 + 0x29c);
  *(int *)(param_1 + 0x6c) = (int)param_1[0x6c] + (int)param_1[0x54];
  *(int *)((longlong)param_1 + 0x364) =
       *(int *)((longlong)param_1 + 0x364) + *(int *)((longlong)param_1 + 0x2a4);
  *(int *)(param_1 + 0x6d) = (int)param_1[0x6d] + (int)param_1[0x55];
  *(int *)((longlong)param_1 + 0x36c) =
       *(int *)((longlong)param_1 + 0x36c) + *(int *)((longlong)param_1 + 0x2ac);
  *(int *)(param_1 + 0x6e) = (int)param_1[0x6e] + (int)param_1[0x56];
  *(int *)((longlong)param_1 + 0x374) =
       *(int *)((longlong)param_1 + 0x374) + *(int *)((longlong)param_1 + 0x2b4);
  *(int *)(param_1 + 0x6f) = (int)param_1[0x6f] + (int)param_1[0x57];
  *(int *)((longlong)param_1 + 0x37c) =
       *(int *)((longlong)param_1 + 0x37c) + *(int *)((longlong)param_1 + 700);
  *(int *)(param_1 + 0x73) = (int)param_1[0x73] + (int)param_1[0x5b];
  *(int *)(param_1 + 0x70) = (int)param_1[0x70] + (int)param_1[0x58];
  *(int *)((longlong)param_1 + 900) =
       *(int *)((longlong)param_1 + 900) + *(int *)((longlong)param_1 + 0x2c4);
  *(int *)(param_1 + 0x71) = (int)param_1[0x71] + (int)param_1[0x59];
  *(int *)((longlong)param_1 + 0x38c) =
       *(int *)((longlong)param_1 + 0x38c) + *(int *)((longlong)param_1 + 0x2cc);
  *(int *)(param_1 + 0x72) = (int)param_1[0x72] + (int)param_1[0x5a];
  *(int *)((longlong)param_1 + 0x394) =
       *(int *)((longlong)param_1 + 0x394) + *(int *)((longlong)param_1 + 0x2d4);
  iVar4 = *(int *)((longlong)param_1 + 0x2dc);
  if (*(int *)((longlong)param_1 + 0x2dc) < *(int *)((longlong)param_1 + 0x39c)) {
    iVar4 = *(int *)((longlong)param_1 + 0x39c);
  }
  *(int *)((longlong)param_1 + 0x39c) = iVar4;
  iVar4 = (int)param_1[0x5c];
  if ((int)param_1[0x5c] < (int)param_1[0x74]) {
    iVar4 = (int)param_1[0x74];
  }
  *(int *)(param_1 + 0x74) = iVar4;
  *(int *)((longlong)param_1 + 0x3a4) =
       *(int *)((longlong)param_1 + 0x3a4) + *(int *)((longlong)param_1 + 0x2e4);
  *(int *)(param_1 + 0x75) = (int)param_1[0x75] + (int)param_1[0x5d];
  *(int *)((longlong)param_1 + 0x3ac) =
       *(int *)((longlong)param_1 + 0x3ac) + *(int *)((longlong)param_1 + 0x2ec);
  *(int *)((longlong)param_1 + 0x324) = *(int *)((longlong)param_1 + 0x324) + 1;
  iVar4 = 0;
  if (0 < iVar18) {
    uVar10 = (ulonglong)uVar13;
    if ((int)uVar13 < 0) {
      uVar10 = 0;
    }
    fVar23 = ((float)(int)uVar10 / (float)iVar18) * _DAT_14bf56a6c;
    iVar5 = (int)ROUND((fVar23 + fVar23) - _DAT_14bf3cd28) >> 1;
    iVar18 = 100;
    if (iVar5 < 100) {
      iVar18 = iVar5;
    }
    if (0 < iVar18) {
      iVar4 = iVar18;
    }
  }
  *(int *)((longlong)param_1 + 0x34c) = iVar4;
  if ((int)param_1[0x60] < (int)param_1[0x48]) {
    *(int *)(param_1 + 0x60) = (int)param_1[0x48];
  }
  if ((int)param_1[0x68] < (int)param_1[0x50]) {
    *(int *)(param_1 + 0x68) = (int)param_1[0x50];
  }
  if (*(int *)((longlong)param_1 + 0x344) < *(int *)((longlong)param_1 + 0x284)) {
    *(int *)((longlong)param_1 + 0x344) = *(int *)((longlong)param_1 + 0x284);
  }
  uVar14 = (undefined7)(uVar10 >> 8);
  if ((*(char *)((longlong)param_1 + 0x25c) == '\0') && ((int)param_1[0x4c] < 1)) {
    uStack_148 = 0;
    uStack_140 = 0;
    FUN_148318be0(param_1,CONCAT71(uVar14,0x15),1,&uStack_148);
  }
  else {
    *(int *)(param_1 + 100) = (int)param_1[100] + 1;
    uStack_138 = 0;
    uStack_130 = 0;
    FUN_148318be0(param_1,CONCAT71(uVar14,0xe),1,&uStack_138);
  }
  if (0 < (int)param_1[0x4d]) {
    *(int *)(param_1 + 0x65) = (int)param_1[0x65] + (int)param_1[0x4d];
  }
  if (0 < *(int *)((longlong)param_1 + 0x2dc)) {
    uStack_128 = 0;
    uStack_120 = 0;
    FUN_148318be0(param_1,0x2a,*(int *)((longlong)param_1 + 0x2dc),&uStack_128);
  }
  if (0 < (int)param_1[0x5c]) {
    uStack_118 = 0;
    uStack_110 = 0;
    FUN_148318be0(param_1,0x2b,(int)param_1[0x5c],&uStack_118);
  }
  if (2 < DAT_14edc6208) {
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d212010,*(undefined4 *)((longlong)param_1 + 0x2dc),
                  (int)param_1[0x5c],CONCAT44(uVar25,*(undefined4 *)((longlong)param_1 + 0x2d4)),
                  CONCAT44(uVar27,*(undefined4 *)((longlong)param_1 + 0x2e4)),
                  CONCAT44(uVar29,(int)param_1[0x5d]),*(undefined4 *)((longlong)param_1 + 0x2ec),
                  CONCAT44(uVar30,*(undefined4 *)((longlong)param_1 + 0x39c)),(int)param_1[0x74],
                  *(undefined4 *)((longlong)param_1 + 0x394),
                  *(undefined4 *)((longlong)param_1 + 0x3a4),(int)param_1[0x75],
                  *(undefined4 *)((longlong)param_1 + 0x3ac));
  }
  uStack_108 = 0;
  uStack_100 = 0;
  FUN_148318be0(param_1,0xd,1,&uStack_108);
  puStack_1b0 = (ulonglong *)0x0;
  uStack_1a8 = 0;
  FUN_1482cce40(param_1 + 0x3c,0x10,&puStack_1b0,0);
  uVar10 = (ulonglong)(int)(uint)uStack_1a8;
  uStack_1b8 = (uint)uStack_1a8;
  puStack_170 = puStack_1b0 + uVar10;
  puVar20 = puStack_1b0;
LAB_1482de6fd:
  puVar12 = puStack_170;
  puStack_198 = puVar20;
  if ((uint)uStack_1a8 != (int)uVar10) {
    plStackX_8 = (longlong *)((ulonglong)plStackX_8 & 0xffffffffffffff00);
    cVar3 = FUN_14bd26430(&plStackX_8);
    if (cVar3 != '\0') {
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
  }
  if (puVar20 == puVar12) {
    FUN_14830f490(param_1);
    if (2 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d2122d0);
    }
    uStack_190 = 0;
    FUN_1481e86d0(param_1 + 5,0);
    if (puStack_1b0 != (ulonglong *)0x0) {
      FUN_140e289f0();
    }
    return;
  }
  uVar10 = *puVar20;
  if (param_1[0xc] != 0) {
    FUN_1468fb7a0(param_1[0xc],&puStack_188);
    uVar13 = uStack_180;
    uVar11 = (ulonglong)(int)uStack_180;
    puVar1 = puStack_188 + uVar11;
    puVar17 = puStack_188;
    while( true ) {
      if ((uint)uVar11 != uVar13) {
        auStackX_18[0] = 0;
        cVar3 = FUN_14bd26430(auStackX_18);
        if (cVar3 != '\0') {
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
      }
      if (puVar17 == puVar1) {
        if (puStack_188 != (undefined8 *)0x0) {
          FUN_140e289f0();
        }
        goto LAB_1482dea0f;
      }
      lVar8 = FUN_1482c8730(param_1[0xc],*puVar17,&UNK_14bf24094,1);
      if ((lVar8 != 0) && (*(ulonglong *)(lVar8 + 8) == uVar10)) break;
      puVar17 = puVar17 + 1;
      uVar11 = (ulonglong)uStack_180;
    }
    if (puStack_188 != (undefined8 *)0x0) {
      FUN_140e289f0();
    }
    if (*(char *)(lVar8 + 0x68) == '\0') {
      uVar10 = *puVar20;
      iVar4 = func_0x0001411c35b0(uVar10 & 0xffffffff);
      if ((int)param_1[0x1f] != *(int *)((longlong)param_1 + 0x124)) {
        plVar19 = param_1 + 0x25;
        if ((longlong *)param_1[0x26] != (longlong *)0x0) {
          plVar19 = (longlong *)param_1[0x26];
        }
        iVar4 = *(int *)((longlong)plVar19 +
                        (ulonglong)((int)param_1[0x27] - 1U & iVar4 + (int)(uVar10 >> 0x20)) * 4);
        if (iVar4 != -1) {
          while (puVar12 = (ulonglong *)((longlong)iVar4 * 0x40 + param_1[0x1e]), *puVar12 != uVar10
                ) {
            iVar4 = (int)puVar12[7];
            if (iVar4 == -1) goto code_r0x0001482de837;
          }
          puVar22 = puVar12 + 1;
          if (puVar12 == (ulonglong *)0x0) {
            puVar22 = (ulonglong *)0x0;
          }
          if (puVar22 == (ulonglong *)0x0) goto LAB_1482dea0f;
          uVar13 = 0;
          puStack_178 = puVar22 + 2;
          if ((int)*puStack_178 < 1) goto LAB_1482dea0f;
          puStack_1a0 = puVar22 + 1;
          lVar8 = 0;
          lVar21 = 0;
          do {
            uVar16 = ~uVar13 >> 0x1f;
            uVar6 = 0;
            if ((int)uVar13 < (int)puStack_1a0[1]) {
              uVar6 = uVar16;
            }
            if ((uVar6 == 0) &&
               (cVar3 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                      &UNK_14bf260f0,(longlong)(int)uVar13,
                                      (longlong)(int)puStack_1a0[1]), cVar3 != '\0')) {
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
            if (((*(char *)(*puStack_1a0 + lVar21) == '\x10') && (-1 < (int)uVar13)) &&
               ((int)uVar13 < (int)puVar22[5])) {
              uVar6 = 0;
              if ((int)uVar13 < (int)puVar22[5]) {
                uVar6 = uVar16;
              }
              if ((uVar6 == 0) &&
                 (cVar3 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                        &UNK_14bf260f0,(longlong)(int)uVar13,
                                        (longlong)(int)puVar22[5]), cVar3 != '\0')) {
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              iStackX_20 = *(int *)((longlong)param_1 + 0x294);
              if (*(int *)(lVar8 + puVar22[4]) < iStackX_20) {
                uVar6 = 0;
                if ((int)uVar13 < (int)puVar22[5]) {
                  uVar6 = uVar16;
                }
                if ((uVar6 == 0) &&
                   (cVar3 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                          &UNK_14bf260f0,(longlong)(int)uVar13,
                                          (longlong)(int)puVar22[5]), cVar3 != '\0')) {
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
                *(int *)(lVar8 + puVar22[4]) = iStackX_20;
              }
            }
            uVar13 = uVar13 + 1;
            lVar21 = lVar21 + 0x10;
            lVar8 = lVar8 + 4;
          } while ((int)uVar13 < (int)*puStack_178);
          puVar20 = puStack_198 + 1;
          uVar10 = (ulonglong)uStack_1b8;
          goto LAB_1482de6fd;
        }
      }
    }
  }
LAB_1482dea0f:
  puVar20 = puVar20 + 1;
  uVar10 = (ulonglong)uStack_1b8;
  goto LAB_1482de6fd;
code_r0x0001482de837:
  puVar20 = puVar20 + 1;
  uVar10 = (ulonglong)uStack_1b8;
  goto LAB_1482de6fd;
}

