// Selected newer-build routine; caller-supplied label: StartRoundSession_URoundManager
// Address: 0x148314ce0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: StartRoundSession_URoundManager */

void FUN_148314ce0(longlong param_1,undefined4 *param_2,undefined8 param_3,undefined8 param_4,
                  undefined1 param_5)

{
  ulonglong uVar1;
  uint uVar2;
  uint uVar3;
  longlong lVar4;
  code *pcVar5;
  int iVar6;
  char cVar7;
  byte bVar8;
  undefined4 uVar9;
  longlong *plVar10;
  int iVar11;
  uint uVar12;
  undefined *puVar13;
  uint *puVar14;
  uint uVar15;
  uint *puVar16;
  undefined8 unaff_retaddr;
  undefined1 auStack_288 [32];
  undefined *puStack_268;
  undefined4 uStack_260;
  undefined4 uStack_258;
  undefined1 auStack_248 [8];
  int iStack_240;
  uint uStack_23c;
  uint *puStack_238;
  uint uStack_230;
  int iStack_22c;
  int iStack_228;
  undefined4 uStack_224;
  int iStack_220;
  uint uStack_21c;
  uint *puStack_218;
  uint uStack_210;
  uint uStack_20c;
  uint uStack_208;
  undefined4 uStack_204;
  longlong *plStack_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  int iStack_1d8;
  undefined4 uStack_1d4;
  int iStack_1d0;
  int iStack_1cc;
  undefined4 *puStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  longlong *plStack_1b0;
  undefined8 uStack_1a8;
  undefined4 uStack_1a0;
  undefined4 uStack_19c;
  uint uStack_198;
  int iStack_194;
  int iStack_190;
  undefined4 uStack_18c;
  int iStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [16];
  longlong *plStack_170;
  undefined8 uStack_168;
  uint *puStack_160;
  undefined8 uStack_158;
  uint uStack_150;
  undefined4 uStack_14c;
  int iStack_148;
  undefined4 uStack_144;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined2 uStack_130;
  longlong lStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  longlong *plStack_110;
  undefined8 uStack_108;
  longlong lStack_100;
  undefined8 uStack_f8;
  undefined1 uStack_f0;
  undefined8 uStack_ec;
  undefined8 uStack_e0;
  longlong lStack_d8;
  ulonglong uStack_d0;
  undefined1 auStack_c8 [16];
  longlong lStack_b8;
  undefined4 uStack_b0;
  uint uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  longlong lStack_98;
  undefined4 uStack_90;
  undefined4 uStack_88;
  undefined1 uStack_84;
  undefined8 uStack_80;
  undefined2 uStack_78;
  longlong lStack_70;
  undefined8 uStack_68;
  undefined4 uStack_60;
  ulonglong uStack_58;
  
  uStack_58 = _DAT_14ed716f8 ^ (ulonglong)auStack_288;
  *(undefined4 *)(param_1 + 0x198) = *param_2;
  *(undefined1 *)(param_1 + 0x19c) = *(undefined1 *)(param_2 + 1);
  puStack_1c8 = param_2;
  uStack_1c0 = param_4;
  uStack_1b8 = param_3;
  FUN_1482d0960(param_1 + 0x1a0,param_2 + 2);
  FUN_140f82850(param_1 + 0x1b0,param_2 + 6);
  FUN_140f82850(param_1 + 0x1c0,param_2 + 10);
  *(undefined1 *)(param_1 + 0x1d0) = *(undefined1 *)(param_2 + 0xe);
  *(undefined4 *)(param_1 + 0x1d4) = param_2[0xf];
  FUN_140cf99e0(param_1 + 0x1d8,param_2 + 0x10);
  *(undefined1 *)(param_1 + 0x1d0) = param_5;
  func_0x00014ba120f6(&uStack_138,0,0xe0);
  uStack_138 = 0;
  uStack_134 = 5;
  uStack_130 = 0;
  lStack_128 = 0;
  uStack_120 = 0;
  uStack_118 = 0;
  plStack_110 = (longlong *)0x0;
  uStack_108 = 0;
  lStack_100 = 0;
  uStack_f8 = 0;
  uStack_f0 = 1;
  uStack_ec = 1;
  uStack_e0 = 0;
  lStack_d8 = 0;
  uStack_d0 = 0;
  lStack_b8 = 0;
  uStack_b0 = 0;
  uStack_ac = 0x80;
  uStack_a8 = 0xffffffff;
  uStack_a4 = 0;
  lStack_98 = 0;
  uStack_90 = 0;
  uStack_88 = 3;
  uStack_84 = 0;
  uStack_80 = 0;
  uStack_78 = 0;
  lStack_70 = 0;
  uStack_68 = 0;
  uStack_60 = 0;
  FUN_1481f51a0(param_1 + 0xb8,&uStack_138);
  if (lStack_70 != 0) {
    FUN_140e289f0();
  }
  uStack_90 = 0;
  if (lStack_98 != 0) {
    FUN_140e289f0();
  }
  uVar1 = uStack_d0 >> 0x20;
  uStack_d0 = uStack_d0 & 0xffffffff00000000;
  if ((int)uVar1 != 0) {
    FUN_140eedf40(&lStack_d8,0);
  }
  uStack_a8 = 0xffffffff;
  uStack_a4 = 0;
  uStack_b0 = 0;
  if (0x80 < uStack_ac) {
    uStack_ac = 0x80;
    FUN_140d189e0(auStack_c8,0);
  }
  if (lStack_b8 != 0) {
    FUN_140e289f0();
  }
  if (lStack_d8 != 0) {
    FUN_140e289f0();
  }
  if (lStack_100 != 0) {
    FUN_140e289f0();
  }
  plVar10 = plStack_110;
  for (iVar11 = (int)uStack_108; iVar11 != 0; iVar11 = iVar11 + -1) {
    if (*plVar10 != 0) {
      FUN_140e289f0();
    }
    plVar10 = plVar10 + 2;
  }
  if (plStack_110 != (longlong *)0x0) {
    FUN_140e289f0(plStack_110);
  }
  if (lStack_128 != 0) {
    FUN_140e289f0();
  }
  *(undefined4 *)(param_1 + 0xbc) = *param_2;
  *(undefined1 *)(param_1 + 0xc0) = *(undefined1 *)(param_2 + 1);
  *(undefined4 *)(param_1 + 0xb8) = 0;
  *(undefined4 *)(param_1 + 0x168) = param_2[0xf];
  plVar10 = (longlong *)(param_1 + 0x118);
  FUN_1482d0cb0(plVar10,param_3);
  iStack_240 = 0;
  uStack_23c = 1;
  puVar14 = (uint *)(param_1 + 0x128);
  uStack_230 = 0xffffffff;
  iStack_22c = 0;
  iStack_228 = 0;
  puStack_238 = puVar14;
  if (*(int *)(param_1 + 0x140) < 0) {
    puStack_268 = &UNK_14bf24094;
    cVar7 = FUN_140f8e6d0(&UNK_14bf32160,&UNK_14d167530,0x70b,unaff_retaddr);
    if (cVar7 != '\0') {
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
  }
  iVar11 = *(int *)(param_1 + 0x140);
  if (iVar11 != 0) {
    puVar16 = puVar14;
    if (*(uint **)(param_1 + 0x138) != (uint *)0x0) {
      puVar16 = *(uint **)(param_1 + 0x138);
    }
    uVar2 = *puVar16;
    iStack_22c = 0;
    iVar6 = 0;
    while (uVar2 == 0) {
      iStack_240 = iVar6 + 1;
      iStack_228 = iStack_22c + 0x20;
      if ((int)((iVar11 + -1 >> 0x1f & 0x1fU) + iVar11 + -1) >> 5 < iStack_240) goto LAB_1483150cd;
      uVar2 = puVar16[iStack_240];
      uStack_230 = 0xffffffff;
      iStack_22c = iStack_228;
      iVar6 = iStack_240;
    }
    uStack_23c = uVar2 - 1 & uVar2 ^ uVar2;
    uVar1 = (ulonglong)uStack_23c * 2 + 1;
    lVar4 = 0x3f;
    if (uVar1 != 0) {
      for (; uVar1 >> lVar4 == 0; lVar4 = lVar4 + -1) {
      }
    }
    iStack_1d0 = (int)lVar4;
    iStack_22c = iStack_1d0 + -1 + iStack_22c;
    if (iVar11 < iStack_22c) {
LAB_1483150cd:
      iStack_22c = iVar11;
    }
  }
  uStack_1f8 = CONCAT44(uStack_23c,iStack_240);
  uStack_1f0 = puStack_238;
  puVar16 = uStack_1f0;
  uStack_1e8 = CONCAT44(iStack_22c,uStack_230);
  uStack_1e0 = CONCAT44(uStack_224,iStack_228);
  iStack_1d8 = *(int *)(param_1 + 0x120) - *(int *)(param_1 + 0x14c);
  uStack_1f0._0_4_ = SUB84(puStack_238,0);
  uStack_1f0._4_4_ = (undefined4)((ulonglong)puStack_238 >> 0x20);
  uStack_1a0 = (undefined4)uStack_1f0;
  uStack_19c = uStack_1f0._4_4_;
  uStack_198 = uStack_230;
  iStack_194 = iStack_22c;
  iStack_190 = iStack_228;
  uStack_18c = uStack_224;
  uStack_184 = uStack_1d4;
  uVar2 = *(uint *)(param_1 + 0x140);
  iVar11 = (int)uVar2 >> 5;
  bVar8 = (byte)uVar2 & 0x1f;
  uStack_21c = 1 << bVar8;
  uVar15 = -1 << bVar8;
  uVar12 = uVar2 & 0xffffffe0;
  iStack_220 = iVar11;
  puStack_218 = puVar14;
  uStack_210 = uVar15;
  uStack_20c = uVar2;
  uStack_208 = uVar12;
  plStack_1b0 = plVar10;
  uStack_1a8 = uStack_1f8;
  iStack_188 = iStack_1d8;
  if ((int)uVar2 < 0) {
    puStack_268 = &UNK_14bf24094;
    plStack_200 = plVar10;
    uStack_1f0 = puVar16;
    cVar7 = FUN_140f8e6d0(&UNK_14bf32160,&UNK_14d167530,0x70b,unaff_retaddr);
    if (cVar7 != '\0') {
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
  }
  uVar3 = *(uint *)(param_1 + 0x140);
  if (uVar2 != uVar3) {
    if (*(uint **)(param_1 + 0x138) != (uint *)0x0) {
      puVar14 = *(uint **)(param_1 + 0x138);
    }
    uVar15 = puVar14[iVar11] & uVar15;
    while (uVar15 == 0) {
      iStack_220 = iVar11 + 1;
      uStack_208 = uVar12 + 0x20;
      if ((int)(((int)(uVar3 - 1) >> 0x1f & 0x1fU) + (uVar3 - 1)) >> 5 < iStack_220)
      goto LAB_14831521c;
      uVar15 = puVar14[iStack_220];
      uStack_210 = 0xffffffff;
      iVar11 = iStack_220;
      uVar12 = uStack_208;
    }
    uStack_21c = uVar15 - 1 & uVar15 ^ uVar15;
    uVar1 = (ulonglong)uStack_21c * 2 + 1;
    lVar4 = 0x3f;
    if (uVar1 != 0) {
      for (; uVar1 >> lVar4 == 0; lVar4 = lVar4 + -1) {
      }
    }
    iStack_1cc = (int)lVar4;
    uStack_20c = iStack_1cc + -1 + uVar12;
    if ((int)uVar3 < (int)uStack_20c) {
LAB_14831521c:
      uStack_20c = uVar3;
    }
  }
  uStack_1f8 = CONCAT44(uStack_21c,iStack_220);
  uStack_1f0 = puStack_218;
  uStack_1e8 = CONCAT44(uStack_20c,uStack_210);
  uStack_1e0 = CONCAT44(uStack_204,uStack_208);
  iStack_1d8 = *(int *)(param_1 + 0x120) - *(int *)(param_1 + 0x14c);
  puStack_160 = puStack_218;
  uStack_150 = uStack_208;
  uStack_14c = uStack_204;
  uStack_144 = uStack_1d4;
  plStack_200 = plVar10;
  plStack_170 = plVar10;
  uStack_168 = uStack_1f8;
  uStack_158 = uStack_1e8;
  iStack_148 = iStack_1d8;
  while( true ) {
    plVar10 = plStack_1b0;
    if ((int)plStack_1b0[1] - *(int *)((longlong)plStack_1b0 + 0x34) != iStack_188) {
      auStack_248[0] = 0;
      cVar7 = FUN_14be5a630(auStack_248);
      if (cVar7 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    if (((iStack_194 == uStack_158._4_4_) &&
        ((uint *)CONCAT44(uStack_19c,uStack_1a0) == puStack_160)) && (plVar10 == plStack_170))
    break;
    lVar4 = *plVar10 + (longlong)iStack_194 * 0x18;
    *(undefined1 *)(lVar4 + 4) = 1;
    uVar9 = 1;
    if (1 < *(int *)(lVar4 + 8)) {
      uVar9 = *(undefined4 *)(lVar4 + 8);
    }
    *(undefined4 *)(lVar4 + 8) = uVar9;
    uStack_198 = uStack_198 & ~uStack_1a8._4_4_;
    FUN_140d11090(&uStack_1a8);
  }
  plVar10 = *(longlong **)(param_1 + 0x358);
  for (iVar11 = *(int *)(param_1 + 0x360); iVar11 != 0; iVar11 = iVar11 + -1) {
    if (*plVar10 != 0) {
      FUN_140e289f0();
    }
    plVar10 = plVar10 + 2;
  }
  *(undefined4 *)(param_1 + 0x360) = 0;
  if (*(int *)(param_1 + 0x364) != 0) {
    FUN_140d24a90(param_1 + 0x358,0);
  }
  *(undefined4 *)(param_1 + 0x370) = 0;
  if (*(int *)(param_1 + 0x374) != 0) {
    FUN_14830c2f0(param_1 + 0x368,0);
  }
  FUN_1482dd8c0(param_1 + 0x1e8,0);
  if (4 < DAT_14edc6208) {
    puVar13 = &UNK_14bf4e28c;
    puStack_268 = &UNK_14bf4e28c;
    if (*(char *)(param_1 + 0x1d0) != '\0') {
      puStack_268 = &UNK_14bf4e298;
    }
    if (*(char *)(puStack_1c8 + 1) != '\0') {
      puVar13 = &UNK_14bf4e298;
    }
    uStack_258 = puStack_1c8[8];
    uStack_260 = puStack_1c8[4];
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d219a08,*puStack_1c8,puVar13);
  }
  if (*(char *)(param_1 + 0xc1) != '\x02') {
    *(undefined1 *)(param_1 + 0xc1) = 2;
    FUN_1481f7370(param_1 + 0x28,2);
  }
  FUN_1482e1440(param_1,auStack_180,uStack_1b8,uStack_1c0);
  FUN_1481f43d0(auStack_180);
  FUN_14b9fb8d0(uStack_58 ^ (ulonglong)auStack_288);
  return;
}

