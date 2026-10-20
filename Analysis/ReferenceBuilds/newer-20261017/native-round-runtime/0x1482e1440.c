// Selected newer-build routine; caller-supplied label: GenerateRoundOptions_URoundManager
// Address: 0x1482e1440
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: GenerateRoundOptions_URoundManager */

undefined8 * FUN_1482e1440(longlong param_1,undefined8 *param_2,longlong *param_3,longlong *param_4)

{
  ulonglong *puVar1;
  undefined1 *puVar2;
  char *pcVar3;
  undefined1 auVar4 [16];
  undefined1 uVar5;
  uint uVar6;
  code *pcVar7;
  bool bVar8;
  undefined8 uVar9;
  float fVar10;
  char cVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined8 *puVar17;
  undefined1 *puVar18;
  longlong lVar19;
  char *pcVar20;
  longlong *plVar21;
  longlong **pplVar22;
  undefined *puVar23;
  byte bVar24;
  char *pcVar25;
  undefined *puVar26;
  longlong lVar27;
  int iVar28;
  longlong *plVar29;
  uint *puVar30;
  undefined8 *puVar31;
  ulonglong uVar32;
  longlong *plVar33;
  uint uVar34;
  longlong lVar35;
  char *pcVar36;
  longlong *plVar37;
  ulonglong uVar38;
  uint uVar39;
  ulonglong uVar40;
  uint *puVar41;
  bool bVar42;
  undefined8 unaff_retaddr;
  undefined1 auStack_248 [2];
  undefined1 auStack_246 [6];
  longlong *plStack_240;
  undefined8 uStack_238;
  undefined1 uStack_230;
  undefined1 uStack_22f;
  undefined1 uStack_22e;
  undefined1 uStack_22d;
  undefined1 uStack_22c;
  undefined1 uStack_22b;
  undefined1 auStack_22a [2];
  longlong *plStack_228;
  undefined8 uStack_220;
  longlong *plStack_218;
  undefined8 uStack_210;
  longlong *plStack_208;
  undefined8 uStack_200;
  longlong lStack_1f8;
  longlong *plStack_1f0;
  undefined8 uStack_1e8;
  longlong lStack_1d8;
  undefined8 uStack_1d0;
  char cStack_1c8;
  longlong *plStack_1c0;
  longlong *plStack_1b8;
  longlong lStack_1b0;
  longlong lStack_1a8;
  char cStack_1a0;
  undefined8 uStack_19c;
  longlong *plStack_188;
  undefined8 uStack_180;
  int iStack_178;
  uint uStack_174;
  longlong *plStack_170;
  int iStack_168;
  uint uStack_164;
  uint *puStack_160;
  undefined4 uStack_158;
  int iStack_154;
  int iStack_150;
  undefined4 uStack_14c;
  int iStack_148;
  uint uStack_144;
  uint *puStack_140;
  uint uStack_138;
  uint uStack_134;
  uint uStack_130;
  undefined4 uStack_12c;
  longlong *plStack_128;
  undefined8 uStack_120;
  uint *puStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  int iStack_100;
  undefined4 uStack_fc;
  undefined8 *puStack_f8;
  int iStack_f0;
  int iStack_ec;
  longlong *plStack_e0;
  int iStack_d8;
  longlong *plStack_d0;
  undefined8 uStack_c8;
  uint *puStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  longlong *plStack_a0;
  longlong alStack_98 [2];
  longlong *plStack_88;
  undefined8 uStack_80;
  undefined1 auStack_78 [16];
  undefined1 auStack_68 [16];
  
  puStack_f8 = param_2;
  FUN_1482dd8c0(param_1 + 0x1e8,0);
  iStack_168 = 0;
  uStack_164 = 1;
  puVar41 = (uint *)(param_3 + 2);
  uStack_158 = 0xffffffff;
  iStack_154 = 0;
  iStack_150 = 0;
  puStack_160 = puVar41;
  if (((int)param_3[5] < 0) &&
     (cVar11 = FUN_140f8e6d0(&UNK_14bf32160,&UNK_14d167530,0x70b,unaff_retaddr,&UNK_14bf24094),
     cVar11 != '\0')) {
    pcVar7 = (code *)swi(3);
    puVar17 = (undefined8 *)(*pcVar7)();
    return puVar17;
  }
  iVar28 = (int)param_3[5];
  if (iVar28 != 0) {
    puVar30 = puVar41;
    if ((uint *)param_3[4] != (uint *)0x0) {
      puVar30 = (uint *)param_3[4];
    }
    uVar13 = *puVar30;
    iVar12 = 0;
    iVar14 = 0;
    while (uVar13 == 0) {
      iStack_168 = iVar14 + 1;
      iStack_150 = iVar12 + 0x20;
      if ((int)((iVar28 + -1 >> 0x1f & 0x1fU) + iVar28 + -1) >> 5 < iStack_168) goto LAB_1482e157a;
      uVar13 = puVar30[iStack_168];
      uStack_158 = 0xffffffff;
      iVar12 = iStack_150;
      iVar14 = iStack_168;
    }
    uStack_164 = uVar13 - 1 & uVar13 ^ uVar13;
    uVar40 = (ulonglong)uStack_164 * 2 + 1;
    lVar27 = 0x3f;
    if (uVar40 != 0) {
      for (; uVar40 >> lVar27 == 0; lVar27 = lVar27 + -1) {
      }
    }
    iStack_ec = (int)lVar27;
    iStack_154 = iVar12 + -1 + iStack_ec;
    if (iVar28 < iStack_154) {
LAB_1482e157a:
      iStack_154 = iVar28;
    }
  }
  uStack_120 = CONCAT44(uStack_164,iStack_168);
  puStack_118 = puStack_160;
  uStack_110 = CONCAT44(iStack_154,uStack_158);
  uStack_108 = CONCAT44(uStack_14c,iStack_150);
  iStack_100 = (int)param_3[1] - *(int *)((longlong)param_3 + 0x34);
  puStack_c0 = puStack_160;
  uStack_a8 = CONCAT44(uStack_fc,iStack_100);
  uVar13 = *(uint *)(param_3 + 5);
  iVar28 = (int)uVar13 >> 5;
  bVar24 = (byte)uVar13 & 0x1f;
  uStack_144 = 1 << bVar24;
  uVar39 = -1 << bVar24;
  uVar34 = uVar13 & 0xffffffe0;
  iStack_148 = iVar28;
  puStack_140 = puVar41;
  uStack_138 = uVar39;
  uStack_134 = uVar13;
  uStack_130 = uVar34;
  plStack_d0 = param_3;
  uStack_c8 = uStack_120;
  uStack_b8 = uStack_110;
  uStack_b0 = uStack_108;
  if (((int)uVar13 < 0) &&
     (plStack_128 = param_3,
     cVar11 = FUN_140f8e6d0(&UNK_14bf32160,&UNK_14d167530,0x70b,unaff_retaddr,&UNK_14bf24094),
     cVar11 != '\0')) {
    pcVar7 = (code *)swi(3);
    puVar17 = (undefined8 *)(*pcVar7)();
    return puVar17;
  }
  uVar6 = *(uint *)(param_3 + 5);
  if (uVar13 != uVar6) {
    if ((uint *)param_3[4] != (uint *)0x0) {
      puVar41 = (uint *)param_3[4];
    }
    uVar39 = puVar41[iVar28] & uVar39;
    while (uVar39 == 0) {
      iStack_148 = iVar28 + 1;
      uStack_130 = uVar34 + 0x20;
      if ((int)(((int)(uVar6 - 1) >> 0x1f & 0x1fU) + (uVar6 - 1)) >> 5 < iStack_148)
      goto LAB_1482e16bb;
      uVar39 = puVar41[iStack_148];
      uStack_138 = 0xffffffff;
      iVar28 = iStack_148;
      uVar34 = uStack_130;
    }
    uStack_144 = uVar39 - 1 & uVar39 ^ uVar39;
    uVar40 = (ulonglong)uStack_144 * 2 + 1;
    lVar27 = 0x3f;
    if (uVar40 != 0) {
      for (; uVar40 >> lVar27 == 0; lVar27 = lVar27 + -1) {
      }
    }
    iStack_f0 = (int)lVar27;
    uStack_134 = iStack_f0 + -1 + uVar34;
    if ((int)uVar6 < (int)uStack_134) {
LAB_1482e16bb:
      uStack_134 = uVar6;
    }
  }
  uStack_120 = CONCAT44(uStack_144,iStack_148);
  puStack_118 = puStack_140;
  uStack_110 = CONCAT44(uStack_134,uStack_138);
  uStack_108 = CONCAT44(uStack_12c,uStack_130);
  iStack_100 = (int)param_3[1] - *(int *)((longlong)param_3 + 0x34);
  auStack_78._8_8_ = uStack_110;
  auStack_78._0_8_ = puStack_140;
  auStack_68._8_4_ = iStack_100;
  auStack_68._0_8_ = uStack_108;
  auStack_68._12_4_ = uStack_fc;
  plStack_128 = param_3;
  plStack_88 = param_3;
  uStack_80 = uStack_120;
  while( true ) {
    plVar37 = plStack_d0;
    if ((int)plStack_d0[1] - *(int *)((longlong)plStack_d0 + 0x34) != (int)uStack_a8) {
      uStack_230 = 0;
      cVar11 = FUN_14be5c140(&uStack_230);
      if (cVar11 != '\0') {
        pcVar7 = (code *)swi(3);
        puVar17 = (undefined8 *)(*pcVar7)();
        return puVar17;
      }
    }
    if (((uStack_b8._4_4_ == auStack_78._12_4_) && (puStack_c0 == (uint *)auStack_78._0_8_)) &&
       (plVar37 == plStack_88)) break;
    puVar2 = (undefined1 *)(*plVar37 + (longlong)uStack_b8._4_4_ * 0x18);
    puVar18 = (undefined1 *)FUN_1482c8390(param_1 + 0x118,*puVar2);
    *puVar18 = 1;
    iVar28 = 1;
    if (1 < *(int *)(puVar2 + 8)) {
      iVar28 = *(int *)(puVar2 + 8);
    }
    if (iVar28 < *(int *)(puVar18 + 4)) {
      iVar28 = *(int *)(puVar18 + 4);
    }
    *(int *)(puVar18 + 4) = iVar28;
    iVar28 = *(int *)(puVar2 + 0xc);
    if (*(int *)(puVar2 + 0xc) < *(int *)(puVar18 + 8)) {
      iVar28 = *(int *)(puVar18 + 8);
    }
    *(int *)(puVar18 + 8) = iVar28;
    uStack_b8 = CONCAT44(uStack_b8._4_4_,(uint)uStack_b8 & ~uStack_c8._4_4_);
    FUN_140d11090(&uStack_c8);
  }
  iStack_178 = *(int *)(param_1 + 0xb8) + 1;
  if (((*(char *)(param_1 + 0xc0) == '\0') && (0 < iStack_178)) &&
     (*(int *)(param_1 + 0xbc) <= iStack_178)) {
    bVar8 = true;
  }
  else {
    bVar8 = false;
  }
  if (((*(int *)(param_1 + 0xb8) != 0) || (bVar8)) ||
     (auStack_246[1] = '\x01', *(int *)(param_1 + 0x230) < 1)) {
    auStack_246[1] = '\0';
  }
  plStack_228 = (longlong *)0x0;
  uStack_220 = 0;
  pplVar22 = (longlong **)(param_1 + 0x1b0);
  plVar37 = *pplVar22;
  iVar28 = *(int *)(param_1 + 0x1b8);
  plVar29 = plVar37 + (longlong)iVar28 * 2;
  while( true ) {
    if (*(int *)(param_1 + 0x1b8) != iVar28) {
      uStack_22f = 0;
      cVar11 = FUN_14bd21c30(&uStack_22f);
      if (cVar11 != '\0') {
        pcVar7 = (code *)swi(3);
        puVar17 = (undefined8 *)(*pcVar7)();
        return puVar17;
      }
    }
    if (plVar37 == plVar29) break;
    puVar17 = *(undefined8 **)(param_1 + 0x358);
    puVar31 = puVar17 + (longlong)*(int *)(param_1 + 0x360) * 2;
    uVar9 = uStack_220;
    for (; uStack_220 = uVar9, puVar17 != puVar31; puVar17 = puVar17 + 2) {
      iVar12 = *(int *)(puVar17 + 1);
      if (iVar12 == (int)plVar37[1]) {
        if (iVar12 < 2) goto LAB_1482e1993;
        iVar12 = func_0x000140d80e70(*puVar17);
        bVar42 = iVar12 == 0;
      }
      else {
        bVar42 = iVar12 + (int)plVar37[1] == 1;
      }
      if (bVar42) goto LAB_1482e1993;
      uVar9 = uStack_220;
    }
    if (plStack_228 <= plVar37) {
      uStack_220._4_4_ = (uint)((ulonglong)uVar9 >> 0x20);
      lVar27 = (longlong)(int)uStack_220._4_4_;
      if (plVar37 < plStack_228 + lVar27 * 2) {
        uStack_220._0_4_ = (int)uVar9;
        lVar19 = (longlong)(int)uStack_220;
        cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                               plVar37,plStack_228,lVar27,lVar19,0x10);
        if (cVar11 != '\0') {
          pcVar7 = (code *)swi(3);
          puVar17 = (undefined8 *)(*pcVar7)();
          return puVar17;
        }
      }
    }
    lVar27 = (longlong)(int)uStack_220;
    uVar13 = (int)uStack_220 + 1;
    uStack_220 = CONCAT44(uStack_220._4_4_,uVar13);
    if (uStack_220._4_4_ < uVar13) {
      FUN_140ca5230(&plStack_228);
    }
    plVar21 = plStack_228 + lVar27 * 2;
    *plVar21 = 0;
    iVar12 = (int)plVar37[1];
    *(int *)(plVar21 + 1) = iVar12;
    plStack_170 = plVar21;
    if (iVar12 == 0) {
      *(undefined4 *)((longlong)plVar21 + 0xc) = 0;
    }
    else {
      FUN_140ca40a0(plVar21,iVar12,0);
      func_0x00014ba120de(*plVar21);
    }
LAB_1482e1993:
    plVar37 = plVar37 + 2;
  }
  if (((int)uStack_220 < 3) &&
     (iVar28 = (int)uStack_220, plVar37 = plStack_228, &plStack_228 != pplVar22)) {
    for (; iVar28 != 0; iVar28 = iVar28 + -1) {
      if (*plVar37 != 0) {
        FUN_140e289f0();
      }
      plVar37 = plVar37 + 2;
    }
    uStack_220._4_4_ = (uint)((ulonglong)uStack_220 >> 0x20);
    uVar15 = uStack_220._4_4_;
    FUN_140c64d10(&plStack_228,*pplVar22,*(undefined4 *)(param_1 + 0x1b8),uVar15);
  }
  bVar42 = false;
  lVar27 = *param_4;
  lVar19 = param_4[1];
  lVar35 = (longlong)(int)lVar19 * 0xc0 + lVar27;
  while( true ) {
    if ((int)param_4[1] != (int)lVar19) {
      uStack_22e = 0;
      cVar11 = FUN_14be5b9c0(&uStack_22e);
      if (cVar11 != '\0') {
        pcVar7 = (code *)swi(3);
        puVar17 = (undefined8 *)(*pcVar7)();
        return puVar17;
      }
    }
    if (lVar27 == lVar35) goto LAB_1482e1a4c;
    if ((0 < *(int *)(lVar27 + 4)) || (0 < *(int *)(lVar27 + 0x80))) break;
    lVar27 = lVar27 + 0xc0;
  }
  bVar42 = true;
LAB_1482e1a4c:
  plStack_240 = (longlong *)0x0;
  uStack_238 = 0;
  pcVar36 = *(char **)(param_1 + 0x1a0);
  iVar28 = *(int *)(param_1 + 0x1a8);
  pcVar3 = pcVar36 + iVar28;
  do {
    if (*(int *)(param_1 + 0x1a8) != iVar28) {
      uStack_22d = 0;
      cVar11 = FUN_14be5c050(&uStack_22d);
      if (cVar11 != '\0') {
        pcVar7 = (code *)swi(3);
        puVar17 = (undefined8 *)(*pcVar7)();
        return puVar17;
      }
    }
    uVar13 = uStack_238._4_4_;
    if (pcVar36 == pcVar3) {
      if ((int)uStack_238 < 3) {
        uStack_238 = (ulonglong)uStack_238._4_4_ << 0x20;
        if (uVar13 != 0) {
          FUN_14830c2f0(&plStack_240,0);
        }
        pcVar36 = *(char **)(param_1 + 0x1a0);
        iVar28 = *(int *)(param_1 + 0x1a8);
        pcVar3 = pcVar36 + iVar28;
        while( true ) {
          if (*(int *)(param_1 + 0x1a8) != iVar28) {
            uStack_22c = 0;
            cVar11 = FUN_14be5c050(&uStack_22c);
            if (cVar11 != '\0') {
              pcVar7 = (code *)swi(3);
              puVar17 = (undefined8 *)(*pcVar7)();
              return puVar17;
            }
          }
          if (pcVar36 == pcVar3) break;
          auStack_246[0] = *pcVar36;
          if (((1 < (byte)(auStack_246[0] - 6U)) || (bVar8)) &&
             ((auStack_246[0] != '\x03' || (bVar42)))) {
            if (plStack_240 <= auStack_246) {
              if (auStack_246 < (char *)((longlong)plStack_240 + (longlong)(int)uStack_238._4_4_)) {
                cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                       &UNK_14bf25f80,auStack_246,plStack_240,
                                       (longlong)(int)uStack_238._4_4_,(longlong)(int)uStack_238,1);
                if (cVar11 != '\0') {
                  pcVar7 = (code *)swi(3);
                  puVar17 = (undefined8 *)(*pcVar7)();
                  return puVar17;
                }
              }
            }
            uVar40 = uStack_238;
            lVar27 = (longlong)(int)uStack_238;
            uVar13 = (int)uStack_238 + 1;
            uStack_238 = CONCAT44(uStack_238._4_4_,uVar13);
            if (uStack_238._4_4_ < uVar13) {
              FUN_14830b750(&plStack_240,uVar40 & 0xffffffff);
            }
            *(char *)(lVar27 + (longlong)plStack_240) = auStack_246[0];
          }
          pcVar36 = pcVar36 + 1;
        }
      }
      fVar10 = _DAT_14bf3cd14;
      iVar28 = (int)uStack_220 + -1;
      if (0 < iVar28) {
        lVar27 = (longlong)iVar28 << 4;
        do {
          if (iVar28 + 1 < 1) {
            iVar12 = 0;
          }
          else {
            uVar13 = rand();
            iVar14 = (int)((float)(uVar13 & 0x7fff) * (float)(iVar28 + 1) * fVar10);
            iVar12 = iVar28;
            if (iVar14 < iVar28) {
              iVar12 = iVar14;
            }
            if ((iVar12 < 0) &&
               (cVar11 = FUN_140f8e6d0(&UNK_14bf3c4e0,&UNK_14d166cc0,0xab4,unaff_retaddr,
                                       &UNK_14bf24094), cVar11 != '\0')) {
              pcVar7 = (code *)swi(3);
              puVar17 = (undefined8 *)(*pcVar7)();
              return puVar17;
            }
          }
          if ((((int)uStack_220 <= iVar28) || ((int)uStack_220 <= iVar12)) &&
             (cVar11 = FUN_140f8e6d0(&UNK_14bf3c520,&UNK_14d166cc0,0xab5,unaff_retaddr,
                                     &UNK_14bf24094), cVar11 != '\0')) {
            pcVar7 = (code *)swi(3);
            puVar17 = (undefined8 *)(*pcVar7)();
            return puVar17;
          }
          if (iVar28 != iVar12) {
            auVar4 = *(undefined1 (*) [16])((longlong)plStack_228 + lVar27);
            *(undefined1 (*) [16])((longlong)plStack_228 + lVar27) =
                 *(undefined1 (*) [16])(plStack_228 + (longlong)iVar12 * 2);
            *(undefined1 (*) [16])(plStack_228 + (longlong)iVar12 * 2) = auVar4;
          }
          iVar28 = iVar28 + -1;
          lVar27 = lVar27 + -0x10;
        } while (0 < iVar28);
      }
      iVar28 = (int)uStack_238 + -1;
      if (0 < iVar28) {
        lVar27 = (longlong)iVar28;
        do {
          if (iVar28 + 1 < 1) {
            iVar12 = 0;
          }
          else {
            uVar13 = rand();
            iVar14 = (int)((float)(uVar13 & 0x7fff) * (float)(iVar28 + 1) * fVar10);
            iVar12 = iVar28;
            if (iVar14 < iVar28) {
              iVar12 = iVar14;
            }
            if ((iVar12 < 0) &&
               (cVar11 = FUN_140f8e6d0(&UNK_14bf3c4e0,&UNK_14d166cc0,0xab4,unaff_retaddr,
                                       &UNK_14bf24094), cVar11 != '\0')) {
              pcVar7 = (code *)swi(3);
              puVar17 = (undefined8 *)(*pcVar7)();
              return puVar17;
            }
          }
          if ((((int)uStack_238 <= iVar28) || ((int)uStack_238 <= iVar12)) &&
             (cVar11 = FUN_140f8e6d0(&UNK_14bf3c520,&UNK_14d166cc0,0xab5,unaff_retaddr,
                                     &UNK_14bf24094), cVar11 != '\0')) {
            pcVar7 = (code *)swi(3);
            puVar17 = (undefined8 *)(*pcVar7)();
            return puVar17;
          }
          if (iVar28 != iVar12) {
            cVar11 = *(char *)(lVar27 + (longlong)plStack_240);
            *(char *)(lVar27 + (longlong)plStack_240) =
                 *(char *)((longlong)iVar12 + (longlong)plStack_240);
            *(char *)((longlong)iVar12 + (longlong)plStack_240) = cVar11;
          }
          iVar28 = iVar28 + -1;
          lVar27 = lVar27 + -1;
        } while (0 < iVar28);
      }
      iVar28 = 0;
      uVar15 = 0;
      plStack_218 = (longlong *)0x0;
      uStack_210 = 0;
      plStack_208 = (longlong *)0x0;
      uStack_200 = 0;
      uStack_174 = uStack_174 & 0xffffff00;
      if (!bVar8) {
        if (auStack_246[1] == '\0') {
          uVar15 = FUN_14830cdb0(param_1,iStack_178,param_4);
          FUN_1482e0480(param_1,uVar15,&plStack_218,&plStack_208);
        }
        else {
          plVar37 = (longlong *)&UNK_14d219b98;
          do {
            lStack_1f8._0_4_ = FUN_1482f3bf0(param_1,iVar28);
            if (plStack_218 <= &lStack_1f8) {
              if (&lStack_1f8 <
                  (undefined4 *)((longlong)plStack_218 + (longlong)(int)uStack_210._4_4_ * 4)) {
                cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                       &UNK_14bf25f80,&lStack_1f8,plStack_218,
                                       (longlong)(int)uStack_210._4_4_,(longlong)(int)uStack_210,4);
                if (cVar11 != '\0') {
                  pcVar7 = (code *)swi(3);
                  puVar17 = (undefined8 *)(*pcVar7)();
                  return puVar17;
                }
              }
            }
            uVar40 = uStack_210;
            lVar27 = (longlong)(int)uStack_210;
            uVar13 = (int)uStack_210 + 1;
            uStack_210 = CONCAT44(uStack_210._4_4_,uVar13);
            if (uStack_210._4_4_ < uVar13) {
              FUN_140d21b90(&plStack_218,uVar40 & 0xffffffff);
            }
            *(undefined4 *)((longlong)plStack_218 + lVar27 * 4) = (undefined4)lStack_1f8;
            if (plStack_208 <= plVar37) {
              if (plVar37 < (longlong *)((longlong)plStack_208 + (longlong)(int)uStack_200._4_4_)) {
                cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                       &UNK_14bf25f80,plVar37,plStack_208,
                                       (longlong)(int)uStack_200._4_4_,(longlong)(int)uStack_200,1);
                if (cVar11 != '\0') {
                  pcVar7 = (code *)swi(3);
                  puVar17 = (undefined8 *)(*pcVar7)();
                  return puVar17;
                }
              }
            }
            uVar40 = uStack_200;
            lVar27 = (longlong)(int)uStack_200;
            uVar13 = (int)uStack_200 + 1;
            uStack_200 = CONCAT44(uStack_200._4_4_,uVar13);
            if (uStack_200._4_4_ < uVar13) {
              FUN_14830b6b0(&plStack_208,uVar40 & 0xffffffff);
            }
            *(char *)(lVar27 + (longlong)plStack_208) = (char)*plVar37;
            iVar28 = iVar28 + 1;
            plVar37 = (longlong *)((longlong)plVar37 + 1);
          } while (iVar28 < 3);
          iVar28 = (int)uStack_210 + -1;
          if (0 < iVar28) {
            lVar27 = (longlong)iVar28;
            do {
              if (iVar28 + 1 < 1) {
                iVar12 = 0;
              }
              else {
                uVar13 = rand();
                iVar14 = (int)((float)(uVar13 & 0x7fff) * (float)(iVar28 + 1) * fVar10);
                iVar12 = iVar28;
                if (iVar14 < iVar28) {
                  iVar12 = iVar14;
                }
                if ((iVar12 < 0) &&
                   (cVar11 = FUN_140f8e6d0(&UNK_14bf3c4e0,&UNK_14d166cc0,0xab4,unaff_retaddr,
                                           &UNK_14bf24094), cVar11 != '\0')) {
                  pcVar7 = (code *)swi(3);
                  puVar17 = (undefined8 *)(*pcVar7)();
                  return puVar17;
                }
              }
              if ((((int)uStack_210 <= iVar28) || ((int)uStack_210 <= iVar12)) &&
                 (cVar11 = FUN_140f8e6d0(&UNK_14bf3c520,&UNK_14d166cc0,0xab5,unaff_retaddr,
                                         &UNK_14bf24094), cVar11 != '\0')) {
                pcVar7 = (code *)swi(3);
                puVar17 = (undefined8 *)(*pcVar7)();
                return puVar17;
              }
              if (iVar28 != iVar12) {
                uVar16 = *(undefined4 *)((longlong)plStack_218 + lVar27 * 4);
                *(undefined4 *)((longlong)plStack_218 + lVar27 * 4) =
                     *(undefined4 *)((longlong)plStack_218 + (longlong)iVar12 * 4);
                *(undefined4 *)((longlong)plStack_218 + (longlong)iVar12 * 4) = uVar16;
              }
              if ((iVar12 < 0) &&
                 (cVar11 = FUN_140f8e6d0(&UNK_14bf3c4e0,&UNK_14d166cc0,0xab4,unaff_retaddr,
                                         &UNK_14bf24094), cVar11 != '\0')) {
                pcVar7 = (code *)swi(3);
                puVar17 = (undefined8 *)(*pcVar7)();
                return puVar17;
              }
              if ((((int)uStack_200 <= iVar28) || ((int)uStack_200 <= iVar12)) &&
                 (cVar11 = FUN_140f8e6d0(&UNK_14bf3c520,&UNK_14d166cc0,0xab5,unaff_retaddr,
                                         &UNK_14bf24094), cVar11 != '\0')) {
                pcVar7 = (code *)swi(3);
                puVar17 = (undefined8 *)(*pcVar7)();
                return puVar17;
              }
              if (iVar28 != iVar12) {
                uVar5 = *(undefined *)(lVar27 + (longlong)plStack_208);
                *(undefined *)(lVar27 + (longlong)plStack_208) =
                     *(undefined *)((longlong)iVar12 + (longlong)plStack_208);
                *(undefined1 *)((longlong)iVar12 + (longlong)plStack_208) = uVar5;
              }
              iVar28 = iVar28 + -1;
              lVar27 = lVar27 + -1;
            } while (0 < iVar28);
          }
        }
      }
      uVar32 = 0;
      plStack_1f0 = (longlong *)0x0;
      uStack_1e8 = 0;
      plStack_188 = (longlong *)0x0;
      uStack_180 = 0;
      plStack_170 = (longlong *)(param_1 + 0x118);
      uVar40 = uVar32;
      do {
        lStack_1d8 = 0;
        uStack_1d0 = 0;
        cStack_1c8 = '\0';
        plStack_1c0 = (longlong *)0x0;
        plStack_1b8 = (longlong *)0x0;
        lStack_1b0 = 0;
        lStack_1a8 = 0;
        cStack_1a0 = 1;
        uStack_19c = 1;
        iVar28 = (int)uStack_220;
        plVar29 = plStack_228 + (longlong)(int)uStack_220 * 2;
        plVar37 = plStack_228;
LAB_1482e2260:
        if ((int)uStack_220 != iVar28) {
          uStack_22b = 0;
          cVar11 = FUN_14bd21c30(&uStack_22b);
          if (cVar11 != '\0') {
            pcVar7 = (code *)swi(3);
            puVar17 = (undefined8 *)(*pcVar7)();
            return puVar17;
          }
        }
        if (plVar37 != plVar29) {
          plVar33 = plStack_1f0 + (longlong)(int)uStack_1e8 * 2;
          plVar21 = plStack_1f0;
          do {
            if (plVar21 == plVar33) {
              if (&lStack_1d8 != plVar37) {
                iVar28 = (int)plVar37[1];
                lVar27 = *plVar37;
                uStack_1d0 = CONCAT44(uStack_1d0._4_4_,iVar28);
                if ((iVar28 == 0) && (uStack_1d0._4_4_ == 0)) {
                  uStack_1d0 = 0;
                }
                else {
                  FUN_140ca40a0(&lStack_1d8,iVar28);
                  if (iVar28 != 0) {
                    func_0x00014ba120de(lStack_1d8,lVar27,(longlong)iVar28 * 2);
                  }
                }
              }
              if (plStack_1f0 <= plVar37) {
                if (plVar37 < plStack_1f0 + (longlong)(int)uStack_1e8._4_4_ * 2) {
                  cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                         &UNK_14bf25f80,plVar37,plStack_1f0,
                                         (longlong)(int)uStack_1e8._4_4_,(longlong)(int)uStack_1e8,
                                         0x10);
                  if (cVar11 != '\0') {
                    pcVar7 = (code *)swi(3);
                    puVar17 = (undefined8 *)(*pcVar7)();
                    return puVar17;
                  }
                }
              }
              uVar38 = uStack_1e8;
              lVar27 = (longlong)(int)uStack_1e8;
              uVar13 = (int)uStack_1e8 + 1;
              uStack_1e8 = CONCAT44(uStack_1e8._4_4_,uVar13);
              if (uStack_1e8._4_4_ < uVar13) {
                FUN_140ca5230(&plStack_1f0,uVar38 & 0xffffffff);
              }
              plVar29 = plStack_1f0 + lVar27 * 2;
              *plVar29 = 0;
              iVar28 = (int)plVar37[1];
              lVar27 = *plVar37;
              *(int *)(plVar29 + 1) = iVar28;
              plStack_a0 = plVar29;
              if (iVar28 == 0) {
                *(undefined4 *)((longlong)plVar29 + 0xc) = 0;
              }
              else {
                FUN_140ca40a0(plVar29,iVar28,0);
                func_0x00014ba120de(*plVar29,lVar27,(longlong)iVar28 * 2);
              }
              break;
            }
            iVar12 = (int)plVar21[1];
            if (iVar12 == (int)plVar37[1]) {
              if (iVar12 < 2) goto LAB_1482e22c9;
              iVar12 = func_0x000140d80e70(*plVar21,*plVar37);
              bVar42 = iVar12 == 0;
            }
            else {
              bVar42 = iVar12 + (int)plVar37[1] == 1;
            }
            if (bVar42) goto LAB_1482e22c9;
            plVar21 = plVar21 + 2;
          } while( true );
        }
        if (((int)uStack_1d0 < 2) && (iVar28 = (int)uStack_220, 0 < (int)uStack_220)) {
          uVar13 = (int)uStack_220 - 1;
          if ((int)uStack_220 < 1) {
            uVar13 = 0;
          }
          else {
            uVar39 = rand();
            uVar39 = (uint)((float)(uVar39 & 0x7fff) * (float)iVar28 * fVar10);
            if ((int)uVar39 < (int)uVar13) {
              uVar13 = uVar39;
            }
          }
          uVar39 = 0;
          if ((int)uVar13 < (int)uStack_220) {
            uVar39 = ~uVar13 >> 0x1f;
          }
          if ((uVar39 == 0) &&
             (cVar11 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                     &UNK_14bf260f0,(longlong)(int)uVar13,(longlong)(int)uStack_220)
             , cVar11 != '\0')) {
            pcVar7 = (code *)swi(3);
            puVar17 = (undefined8 *)(*pcVar7)();
            return puVar17;
          }
          iVar12 = (int)(plStack_228 + (longlong)(int)uVar13 * 2)[1];
          iVar28 = iVar12 + -1;
          if (iVar12 == 0) {
            iVar28 = 0;
          }
          FUN_140d05200(&lStack_1d8,plStack_228[(longlong)(int)uVar13 * 2],iVar28);
        }
        iVar28 = (int)uStack_238;
        uVar38 = (ulonglong)(int)uStack_238;
        plVar37 = (longlong *)((longlong)plStack_240 + uVar38);
        plVar29 = plStack_240;
        while( true ) {
          if ((int)uVar38 != iVar28) {
            auStack_22a[0] = 0;
            cVar11 = FUN_14be5c050(auStack_22a);
            if (cVar11 != '\0') {
              pcVar7 = (code *)swi(3);
              puVar17 = (undefined8 *)(*pcVar7)();
              return puVar17;
            }
            uVar38 = uStack_238 & 0xffffffff;
          }
          iVar12 = (int)uVar38;
          if (plVar29 == plVar37) break;
          auStack_248[1] = (char)*plVar29;
          plVar21 = plStack_188;
          while( true ) {
            if (plVar21 == (longlong *)((longlong)(int)uStack_180 + (longlong)plStack_188)) {
              cStack_1c8 = auStack_248[1];
              if (plStack_188 <= auStack_248 + 1) {
                if ((auStack_248 + 1 <
                     (char *)((longlong)plStack_188 + (longlong)(int)uStack_180._4_4_)) &&
                   (cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                           &UNK_14bf25f80,auStack_248 + 1,plStack_188,
                                           (longlong)(int)uStack_180._4_4_,(longlong)(int)uStack_180
                                           ,1), cVar11 != '\0')) {
                  pcVar7 = (code *)swi(3);
                  puVar17 = (undefined8 *)(*pcVar7)();
                  return puVar17;
                }
              }
              uVar38 = uStack_180;
              lVar27 = (longlong)(int)uStack_180;
              uVar13 = (int)uStack_180 + 1;
              uStack_180 = CONCAT44(uStack_180._4_4_,uVar13);
              if (uStack_180._4_4_ < uVar13) {
                FUN_14830b750(&plStack_188,uVar38 & 0xffffffff);
              }
              *(char *)(lVar27 + (longlong)plStack_188) = auStack_248[1];
              goto LAB_1482e25bb;
            }
            if ((char)*plVar21 == auStack_248[1]) break;
            plVar21 = (longlong *)((longlong)plVar21 + 1);
          }
          plVar29 = (longlong *)((longlong)plVar29 + 1);
        }
        if (0 < iVar12) {
          if (iVar12 < 1) {
            uVar13 = 0;
          }
          else {
            uVar13 = rand();
            uVar39 = (uint)((float)(uVar13 & 0x7fff) * (float)iVar12 * fVar10);
            uVar13 = iVar12 - 1U;
            if ((int)uVar39 < (int)(iVar12 - 1U)) {
              uVar13 = uVar39;
            }
            iVar12 = (int)uStack_238;
          }
          uVar39 = 0;
          if ((int)uVar13 < iVar12) {
            uVar39 = ~uVar13 >> 0x1f;
          }
          if ((uVar39 == 0) &&
             (cVar11 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                     &UNK_14bf260f0,(longlong)(int)uVar13,(longlong)iVar12),
             cVar11 != '\0')) {
            pcVar7 = (code *)swi(3);
            puVar17 = (undefined8 *)(*pcVar7)();
            return puVar17;
          }
          cStack_1c8 = *(char *)((longlong)(int)uVar13 + (longlong)plStack_240);
        }
LAB_1482e25bb:
        iVar28 = (int)uVar32;
        if (bVar8) {
          uStack_19c = CONCAT44(uStack_19c._4_4_,6);
          cStack_1a0 = '\x02';
        }
        else {
          uVar13 = 0;
          if (auStack_246[1] == '\0') {
            uVar16 = uVar15;
            if ((int)uStack_210 <= iVar28) goto LAB_1482e278f;
            uVar39 = (uint)(uVar32 >> 0x1f);
            uVar34 = uVar13;
            if (iVar28 < (int)uStack_210) {
              uVar34 = uVar39 ^ 1;
            }
            if ((uVar34 == 0) &&
               (cVar11 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                       &UNK_14bf260f0,uVar32,(longlong)(int)uStack_210),
               cVar11 != '\0')) {
              pcVar7 = (code *)swi(3);
              puVar17 = (undefined8 *)(*pcVar7)();
              return puVar17;
            }
LAB_1482e277c:
            uStack_19c = CONCAT44(uStack_19c._4_4_,
                                  *(undefined4 *)((longlong)plStack_218 + uVar40 * 4));
          }
          else {
            if (iVar28 < (int)uStack_210) {
              uVar39 = (uint)(uVar32 >> 0x1f);
              uVar34 = uVar13;
              if (iVar28 < (int)uStack_210) {
                uVar34 = uVar39 ^ 1;
              }
              if ((uVar34 == 0) &&
                 (cVar11 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                         &UNK_14bf260f0,uVar32,(longlong)(int)uStack_210),
                 cVar11 != '\0')) {
                pcVar7 = (code *)swi(3);
                puVar17 = (undefined8 *)(*pcVar7)();
                return puVar17;
              }
              goto LAB_1482e277c;
            }
            uVar16 = FUN_1482f3bf0(param_1,uVar32);
LAB_1482e278f:
            uStack_19c = CONCAT44(uStack_19c._4_4_,uVar16);
            uVar39 = (uint)(uVar32 >> 0x1f);
          }
          if (iVar28 < (int)uStack_200) {
            if (iVar28 < (int)uStack_200) {
              uVar13 = uVar39 ^ 1;
            }
            if ((uVar13 == 0) &&
               (cVar11 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                       &UNK_14bf260f0,uVar32,(longlong)(int)uStack_200),
               cVar11 != '\0')) {
              pcVar7 = (code *)swi(3);
              puVar17 = (undefined8 *)(*pcVar7)();
              return puVar17;
            }
            cStack_1a0 = *(char *)((longlong)plStack_208 + uVar40);
          }
          else {
            cStack_1a0 = '\x01';
          }
        }
        pplVar22 = (longlong **)
                   FUN_1482e0ad0(param_1,&plStack_e0,uStack_19c & 0xffffffff,cStack_1c8);
        plVar37 = plStack_e0;
        iVar12 = iStack_d8;
        if (&plStack_1c0 != pplVar22) {
          plVar37 = plStack_1c0;
          for (iVar12 = (int)plStack_1b8; iVar12 != 0; iVar12 = iVar12 + -1) {
            if (*plVar37 != 0) {
              FUN_140e289f0();
            }
            plVar37 = plVar37 + 2;
          }
          if (plStack_1c0 != (longlong *)0x0) {
            FUN_140e289f0(plStack_1c0);
          }
          plStack_1c0 = *pplVar22;
          *pplVar22 = (longlong *)0x0;
          plStack_1b8 = pplVar22[1];
          pplVar22[1] = (longlong *)0x0;
          plVar37 = plStack_e0;
          iVar12 = iStack_d8;
        }
        for (; iVar12 != 0; iVar12 = iVar12 + -1) {
          if (*plVar37 != 0) {
            FUN_140e289f0();
          }
          plVar37 = plVar37 + 2;
        }
        if (plStack_e0 != (longlong *)0x0) {
          FUN_140e289f0(plStack_e0);
        }
        plVar37 = plStack_170;
        uVar13 = uStack_174;
        if (((char)uStack_174 == '\0') && (cStack_1a0 == '\x02')) {
          iVar12 = *(int *)(param_1 + 0x26c);
          if (iVar12 < 1) {
            iVar12 = 1;
          }
          if ((*(int *)(param_1 + 400) < iVar12 + -1) ||
             (cVar11 = FUN_1482f9da0(param_1,plStack_170), cVar11 == '\0')) goto LAB_1482e2907;
          cVar11 = '\x01';
        }
        else {
LAB_1482e2907:
          cVar11 = '\0';
        }
        plVar37 = (longlong *)
                  FUN_1482d8190(param_1,alStack_98,uStack_19c & 0xffffffff,cStack_1a0,plVar37,cVar11
                               );
        if (&lStack_1b0 != plVar37) {
          if (lStack_1b0 != 0) {
            FUN_140e289f0();
          }
          lStack_1b0 = *plVar37;
          *plVar37 = 0;
          lStack_1a8 = plVar37[1];
          plVar37[1] = 0;
        }
        if (alStack_98[0] != 0) {
          FUN_140e289f0();
        }
        uStack_174 = uVar13 & 0xff;
        if (cVar11 != '\0') {
          uStack_174 = 1;
        }
        uVar16 = FUN_14830da40(param_1,cStack_1c8,uStack_19c & 0xffffffff);
        uStack_19c = CONCAT44(uVar16,(undefined4)uStack_19c);
        puVar1 = (ulonglong *)(param_1 + 0x1e8);
        plVar37 = (longlong *)*puVar1;
        if (((plVar37 <= &lStack_1d8) &&
            (&lStack_1d8 < plVar37 + (longlong)*(int *)(param_1 + 500) * 9)) &&
           (cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                   &lStack_1d8,plVar37,(longlong)*(int *)(param_1 + 500),
                                   (longlong)*(int *)(param_1 + 0x1f0),0x48), cVar11 != '\0')) {
          pcVar7 = (code *)swi(3);
          puVar17 = (undefined8 *)(*pcVar7)();
          return puVar17;
        }
        iVar12 = *(int *)(param_1 + 0x1f0);
        *(uint *)(param_1 + 0x1f0) = iVar12 + 1U;
        if (*(uint *)(param_1 + 500) < iVar12 + 1U) {
          FUN_14830b2b0(puVar1,iVar12);
        }
        FUN_1482ce300(*puVar1 + (longlong)iVar12 * 0x48,&lStack_1d8);
        if (lStack_1b0 != 0) {
          FUN_140e289f0();
        }
        plVar37 = plStack_1c0;
        for (iVar12 = (int)plStack_1b8; iVar12 != 0; iVar12 = iVar12 + -1) {
          if (*plVar37 != 0) {
            FUN_140e289f0();
          }
          plVar37 = plVar37 + 2;
        }
        if (plStack_1c0 != (longlong *)0x0) {
          FUN_140e289f0(plStack_1c0);
        }
        if (lStack_1d8 != 0) {
          FUN_140e289f0();
        }
        uVar32 = (ulonglong)(iVar28 + 1U);
        uVar40 = uVar40 + 1;
        if (2 < (int)(iVar28 + 1U)) {
          if (4 < DAT_14edc6208) {
            puVar26 = &UNK_14bf4e28c;
            puVar23 = &UNK_14bf4e28c;
            if (bVar8) {
              puVar23 = &UNK_14bf4e298;
            }
            if (auStack_246[1] != '\0') {
              puVar26 = &UNK_14bf4e298;
            }
            FUN_140f252a0(&DAT_14edc6208,&UNK_14d219ba0,*(undefined4 *)(param_1 + 0x1f0),iStack_178,
                          puVar23,puVar26,uVar15);
          }
          FUN_1481f7280(param_1 + 0x40,puVar1);
          puVar17 = puStack_f8;
          *puStack_f8 = 0;
          FUN_1481f3650(puStack_f8,*puVar1,*(undefined4 *)(param_1 + 0x1f0),0);
          if (plStack_188 != (longlong *)0x0) {
            FUN_140e289f0();
          }
          plVar37 = plStack_1f0;
          for (iVar28 = (int)uStack_1e8; iVar28 != 0; iVar28 = iVar28 + -1) {
            if (*plVar37 != 0) {
              FUN_140e289f0();
            }
            plVar37 = plVar37 + 2;
          }
          if (plStack_1f0 != (longlong *)0x0) {
            FUN_140e289f0(plStack_1f0);
          }
          if (plStack_208 != (longlong *)0x0) {
            FUN_140e289f0();
          }
          if (plStack_218 != (longlong *)0x0) {
            FUN_140e289f0();
          }
          if (plStack_240 != (longlong *)0x0) {
            FUN_140e289f0();
          }
          plVar37 = plStack_228;
          for (iVar28 = (int)uStack_220; iVar28 != 0; iVar28 = iVar28 + -1) {
            if (*plVar37 != 0) {
              FUN_140e289f0();
            }
            plVar37 = plVar37 + 2;
          }
          if (plStack_228 != (longlong *)0x0) {
            FUN_140e289f0(plStack_228);
          }
          return puVar17;
        }
      } while( true );
    }
    auStack_248[0] = *pcVar36;
    if (((1 < (byte)(auStack_248[0] - 6U)) || (bVar8)) && ((auStack_248[0] != '\x03' || (bVar42))))
    {
      pcVar20 = *(char **)(param_1 + 0x368);
      pcVar25 = pcVar20 + *(int *)(param_1 + 0x370);
      for (; pcVar20 != pcVar25; pcVar20 = pcVar20 + 1) {
        if (*pcVar20 == auStack_248[0]) goto LAB_1482e1b9d;
      }
      if (((plStack_240 <= auStack_248) &&
          (auStack_248 < (char *)((longlong)plStack_240 + (longlong)(int)uStack_238._4_4_))) &&
         (cVar11 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                 auStack_248,plStack_240,(longlong)(int)uStack_238._4_4_,
                                 (longlong)(int)uStack_238,1), cVar11 != '\0')) {
        pcVar7 = (code *)swi(3);
        puVar17 = (undefined8 *)(*pcVar7)();
        return puVar17;
      }
      uVar40 = uStack_238;
      lVar27 = (longlong)(int)uStack_238;
      uVar13 = (int)uStack_238 + 1;
      uStack_238 = CONCAT44(uStack_238._4_4_,uVar13);
      if (uStack_238._4_4_ < uVar13) {
        FUN_14830b750(&plStack_240,uVar40 & 0xffffffff);
      }
      *(char *)(lVar27 + (longlong)plStack_240) = auStack_248[0];
    }
LAB_1482e1b9d:
    pcVar36 = pcVar36 + 1;
  } while( true );
LAB_1482e22c9:
  plVar37 = plVar37 + 2;
  goto LAB_1482e2260;
}

