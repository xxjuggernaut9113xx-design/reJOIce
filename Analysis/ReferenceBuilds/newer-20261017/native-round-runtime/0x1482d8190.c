// Selected newer-build routine; caller-supplied label: CalculateRewardsForRound_URoundManager
// Address: 0x1482d8190
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: CalculateRewardsForRound_URoundManager */

ulonglong *
FUN_1482d8190(longlong param_1,ulonglong *param_2,uint param_3,char param_4,longlong *param_5,
             char param_6)

{
  byte *pbVar1;
  byte *pbVar2;
  char *pcVar3;
  byte bVar4;
  undefined1 *puVar5;
  ulonglong uVar6;
  code *pcVar7;
  float fVar8;
  float fVar9;
  char cVar10;
  undefined1 uVar11;
  uint uVar12;
  int iVar13;
  undefined4 uVar14;
  undefined8 *puVar15;
  ulonglong *puVar16;
  longlong lVar17;
  char *pcVar18;
  longlong *plVar19;
  undefined *puVar20;
  byte *pbVar21;
  char *pcVar22;
  uint uVar23;
  uint uVar24;
  ulonglong uVar25;
  ulonglong uVar26;
  byte *pbVar27;
  int iVar28;
  int iVar29;
  char *pcVar30;
  longlong *plVar31;
  longlong lVar32;
  int iVar33;
  uint uVar34;
  bool bVar35;
  float fVar36;
  undefined8 unaff_retaddr;
  undefined1 auStackX_8 [8];
  ulonglong *puStackX_10;
  uint uStackX_18;
  char acStackX_20 [8];
  longlong in_stack_fffffffffffffdb0;
  byte bStack_238;
  undefined1 auStack_237 [2];
  undefined1 uStack_235;
  undefined1 auStack_234 [4];
  uint uStack_230;
  uint uStack_22c;
  undefined1 uStack_228;
  undefined1 uStack_227;
  undefined1 uStack_226;
  undefined1 uStack_225;
  undefined4 uStack_224;
  longlong *plStack_220;
  undefined8 uStack_218;
  longlong *plStack_210;
  undefined8 uStack_208;
  byte *pbStack_200;
  undefined8 uStack_1f8;
  byte *pbStack_1f0;
  undefined8 uStack_1e8;
  undefined1 auStack_1e0 [4];
  int iStack_1dc;
  ulonglong *puStack_1d8;
  undefined4 uStack_1d0;
  ulonglong *puStack_1c8;
  ulonglong *puStack_1c0;
  ulonglong **ppuStack_1b8;
  longlong lStack_1b0;
  ulonglong *puStack_1a8;
  ulonglong *puStack_1a0;
  ulonglong ***pppuStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined4 uStack_180;
  ulonglong *puStack_178;
  ulonglong **ppuStack_170;
  ulonglong **ppuStack_168;
  ulonglong **ppuStack_160;
  ulonglong **ppuStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined4 uStack_140;
  ulonglong *puStack_138;
  ulonglong **ppuStack_130;
  ulonglong **ppuStack_128;
  uint *puStack_120;
  longlong lStack_118;
  char *pcStack_110;
  longlong lStack_108;
  char *pcStack_100;
  ulonglong **ppuStack_f8;
  uint *puStack_f0;
  int *piStack_e8;
  uint **ppuStack_e0;
  ulonglong **ppuStack_d8;
  byte **ppbStack_d0;
  ulonglong **ppuStack_c8;
  longlong **pplStack_c0;
  byte **ppbStack_b8;
  ulonglong **ppuStack_a8;
  undefined1 *puStack_a0;
  ulonglong ***pppuStack_98;
  byte **ppbStack_90;
  byte **ppbStack_88;
  ulonglong ***pppuStack_80;
  longlong **pplStack_78;
  
  *param_2 = 0;
  param_2[1] = 0;
  uStack_1d0 = 1;
  uStack_230 = 1;
  if (1 < (int)param_3) {
    uStack_230 = param_3;
  }
  puStackX_10 = param_2;
  uStackX_18 = param_3;
  acStackX_20[0] = param_4;
  puStack_1c8 = param_2;
  lStack_1b0 = FUN_1482f85c0(param_1,param_3);
  fVar9 = _DAT_14bf3cd28;
  fVar8 = _DAT_14bf3cd14;
  uVar34 = 2;
  iVar33 = 0;
  if (lStack_1b0 == 0) {
    iVar29 = (uStack_230 + 2) * 5;
    uVar12 = (int)ROUND((float)iVar29 * _DAT_14bfe47a8 + (float)iVar29 * _DAT_14bfe47a8 +
                        _DAT_14bf3cd28) >> 1;
    if ((int)uVar12 < 2) {
      uVar12 = uVar34;
    }
    uVar24 = iVar29 - uVar12;
    uVar12 = uVar12 + iVar29;
    uVar23 = uVar12;
    if ((int)uVar24 <= (int)uVar12) {
      uVar23 = uVar24;
      uVar24 = uVar12;
    }
    if ((int)uVar23 < 1) {
      uVar23 = 1;
    }
    if ((int)uVar24 < (int)uVar23) {
      uVar24 = uVar23;
    }
    if (uVar23 != uVar24) {
      iVar28 = uVar24 - uVar23;
      iVar29 = iVar33;
      if (0 < iVar28 + 1) {
        uVar12 = rand();
        iVar13 = (int)((float)(uVar12 & 0x7fff) * (float)(iVar28 + 1) * fVar8);
        iVar29 = iVar28;
        if (iVar13 < iVar28) {
          iVar29 = iVar13;
        }
      }
      uVar23 = uVar23 + iVar29;
    }
    if ((int)uVar23 < 1) {
      uVar23 = 1;
    }
    uVar12 = uStack_230 + 1;
    uStack_22c = uVar23;
    if ((int)(uStack_230 + 1) < 2) {
      uVar12 = uVar34;
    }
  }
  else {
    uVar12 = *(uint *)(lStack_1b0 + 0x54);
    uVar23 = *(uint *)(lStack_1b0 + 0x50);
    uVar24 = (uStack_230 + 2) * 5;
    if (0 < (int)*(uint *)(lStack_1b0 + 0x48)) {
      uVar24 = *(uint *)(lStack_1b0 + 0x48);
    }
    if ((int)uVar23 < 0) {
      uVar23 = uVar24;
      if ((int)uVar12 < 0) {
        uVar12 = (int)ROUND((float)(int)uVar24 * _DAT_14bfe47a8 +
                            (float)(int)uVar24 * _DAT_14bfe47a8 + _DAT_14bf3cd28) >> 1;
        if ((int)uVar12 < 2) {
          uVar12 = uVar34;
        }
        uVar23 = uVar24 - uVar12;
        uVar12 = uVar12 + uVar24;
      }
    }
    else if ((int)uVar12 < 0) {
      uVar12 = uVar24;
    }
    uVar24 = uVar12;
    if ((int)uVar23 <= (int)uVar12) {
      uVar24 = uVar23;
      uVar23 = uVar12;
    }
    if ((int)uVar24 < 1) {
      uVar24 = 1;
    }
    if ((int)uVar23 < (int)uVar24) {
      uVar23 = uVar24;
    }
    if (uVar24 != uVar23) {
      iVar28 = uVar23 - uVar24;
      iVar29 = iVar33;
      if (0 < iVar28 + 1) {
        uVar12 = rand();
        iVar13 = (int)((float)(uVar12 & 0x7fff) * (float)(iVar28 + 1) * fVar8);
        iVar29 = iVar28;
        if (iVar13 < iVar28) {
          iVar29 = iVar13;
        }
      }
      uVar24 = uVar24 + iVar29;
    }
    if ((int)uVar24 < 1) {
      uVar24 = 1;
    }
    uVar12 = uStack_230 + 1;
    if ((int)(uStack_230 + 1) < 2) {
      uVar12 = uVar34;
    }
    uVar34 = *(uint *)(lStack_1b0 + 0x5c);
    uVar23 = *(uint *)(lStack_1b0 + 0x58);
    if (0 < (int)*(uint *)(lStack_1b0 + 0x4c)) {
      uVar12 = *(uint *)(lStack_1b0 + 0x4c);
    }
    uStack_22c = uVar24;
    if (-1 < (int)uVar23) {
      if ((int)uVar34 < 0) {
        uVar34 = uVar12;
      }
      goto LAB_1482d83f5;
    }
    uVar23 = uVar12;
    if (-1 < (int)uVar34) goto LAB_1482d83f5;
  }
  uVar34 = (int)ROUND((float)(int)uVar12 * _DAT_14bf8cea0 + (float)(int)uVar12 * _DAT_14bf8cea0 +
                      fVar9) >> 1;
  if ((int)uVar34 < 1) {
    uVar34 = 1;
  }
  uVar23 = uVar12 - uVar34;
  uVar34 = uVar34 + uVar12;
LAB_1482d83f5:
  uVar12 = uVar34;
  if ((int)uVar23 <= (int)uVar34) {
    uVar12 = uVar23;
    uVar23 = uVar34;
  }
  if ((int)uVar12 < 1) {
    uVar12 = 1;
  }
  if ((int)uVar23 < (int)uVar12) {
    uVar23 = uVar12;
  }
  if (uVar12 != uVar23) {
    iVar29 = uVar23 - uVar12;
    if (0 < iVar29 + 1) {
      uVar34 = rand();
      iVar28 = (int)((float)(uVar34 & 0x7fff) * (float)(iVar29 + 1) * fVar8);
      iVar33 = iVar29;
      if (iVar28 < iVar29) {
        iVar33 = iVar28;
      }
    }
    uVar12 = uVar12 + iVar33;
  }
  if ((int)uVar12 < 1) {
    uVar12 = 1;
  }
  if (acStackX_20[0] == '\0') {
    fVar36 = *(float *)(param_1 + 0x240);
  }
  else if ((acStackX_20[0] == '\x01') || (acStackX_20[0] != '\x02')) {
    fVar36 = *(float *)(param_1 + 0x24c);
  }
  else {
    fVar36 = *(float *)(param_1 + 0x250);
  }
  iStack_1dc = (int)ROUND((float)(int)uVar12 * fVar36 + (float)(int)uVar12 * fVar36 + fVar9) >> 1;
  if (iStack_1dc < 1) {
    iStack_1dc = 1;
  }
  pbStack_1f0 = (byte *)0x0;
  uStack_1e8 = 0;
  pbStack_200 = (byte *)0x0;
  uStack_1f8 = 0;
  plStack_220 = (longlong *)0x0;
  uStack_218 = 0;
  puVar15 = (undefined8 *)FUN_1482f6630();
  pbVar27 = (byte *)*puVar15;
  iVar33 = *(int *)(puVar15 + 1);
  pbVar1 = pbVar27 + iVar33;
LAB_1482d84e0:
  if (*(int *)(puVar15 + 1) != iVar33) {
    auStackX_8[0] = 0;
    cVar10 = FUN_14be5bab0(auStackX_8);
    if (cVar10 != '\0') {
      pcVar7 = (code *)swi(3);
      puVar16 = (ulonglong *)(*pcVar7)();
      return puVar16;
    }
  }
  lVar17 = lStack_1b0;
  if (pbVar27 != pbVar1) {
    bStack_238 = *pbVar27;
    if ((bStack_238 & 0xf7) == 0) goto LAB_1482d8656;
    lVar17 = FUN_1482df780(param_1);
    if (lVar17 != 0) goto LAB_1482d8553;
    if (DAT_14edc6208 < 3) goto LAB_1482d8656;
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d21b020);
    pbVar27 = pbVar27 + 1;
    goto LAB_1482d84e0;
  }
  if (lStack_1b0 != 0) {
    pcVar30 = *(char **)(lStack_1b0 + 0x60);
    iVar33 = *(int *)(lStack_1b0 + 0x68);
    pcVar3 = pcVar30 + iVar33;
    while( true ) {
      if (*(int *)(lVar17 + 0x68) != iVar33) {
        uStack_235 = 0;
        cVar10 = FUN_14be5bb00(&uStack_235);
        if (cVar10 != '\0') {
          pcVar7 = (code *)swi(3);
          puVar16 = (ulonglong *)(*pcVar7)();
          return puVar16;
        }
      }
      if (pcVar30 == pcVar3) break;
      auStack_237[0] = *pcVar30;
      if (auStack_237[0] != '\x16') {
        pcVar18 = *(char **)(param_1 + 0x180);
        pcVar22 = pcVar18 + *(int *)(param_1 + 0x188);
        for (; pcVar18 != pcVar22; pcVar18 = pcVar18 + 1) {
          if (*pcVar18 == auStack_237[0]) goto LAB_1482d889a;
        }
        for (plVar19 = plStack_220;
            plVar19 != (longlong *)((longlong)plStack_220 + (longlong)(int)uStack_218);
            plVar19 = (longlong *)((longlong)plVar19 + 1)) {
          if ((char)*plVar19 == auStack_237[0]) goto LAB_1482d889a;
        }
        if (plStack_220 <= auStack_237) {
          lVar32 = (longlong)(int)uStack_218._4_4_;
          if ((auStack_237 < (char *)(lVar32 + (longlong)plStack_220)) &&
             (cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                     &UNK_14bf25f80,auStack_237,plStack_220,lVar32,
                                     (longlong)(int)uStack_218,1),
             in_stack_fffffffffffffdb0 = lVar32, cVar10 != '\0')) {
            pcVar7 = (code *)swi(3);
            puVar16 = (ulonglong *)(*pcVar7)();
            return puVar16;
          }
        }
        uVar26 = uStack_218;
        lVar32 = (longlong)(int)uStack_218;
        uVar34 = (int)uStack_218 + 1;
        uStack_218 = CONCAT44(uStack_218._4_4_,uVar34);
        if (uStack_218._4_4_ < uVar34) {
          FUN_14830b890(&plStack_220,uVar26 & 0xffffffff);
        }
        *(char *)(lVar32 + (longlong)plStack_220) = auStack_237[0];
      }
LAB_1482d889a:
      pcVar30 = pcVar30 + 1;
    }
  }
  puVar16 = puStack_1c8;
  puStack_1d8 = puStack_1c8;
  puStack_1a8 = puStack_1c8;
  puStack_1a0 = puStack_1c8;
  ppuStack_160 = &puStack_1a8;
  ppuStack_158 = &puStack_1a0;
  puStack_1c0 = puStack_1c8;
  ppuStack_1b8 = &puStack_1d8;
  puStack_138 = puStack_1c8;
  ppuStack_130 = &puStack_1d8;
  ppuStack_128 = &puStack_1a8;
  puStack_178 = puStack_1c8;
  ppuStack_170 = &puStack_1d8;
  ppuStack_168 = &puStack_1a0;
  ppuStack_a8 = &puStack_1d8;
  puStack_a0 = auStack_1e0;
  pppuStack_98 = &ppuStack_160;
  ppbStack_90 = &pbStack_200;
  ppbStack_88 = &pbStack_1f0;
  pppuStack_80 = &ppuStack_158;
  pplStack_78 = &plStack_220;
  pppuStack_198 = &ppuStack_a8;
  puStack_120 = &uStack_230;
  pcStack_110 = acStackX_20;
  pcStack_100 = acStackX_20;
  ppuStack_f8 = &puStack_1c0;
  puStack_f0 = &uStack_22c;
  piStack_e8 = &iStack_1dc;
  ppuStack_e0 = &puStack_120;
  ppuStack_d8 = &puStack_138;
  ppbStack_d0 = &pbStack_200;
  ppuStack_c8 = &puStack_178;
  pplStack_c0 = &plStack_220;
  ppbStack_b8 = &pbStack_1f0;
  if (acStackX_20[0] == '\0') {
    uStack_190 = *(undefined8 *)(param_1 + 0x270);
    uStack_188 = *(undefined8 *)(param_1 + 0x278);
    uStack_180 = *(undefined4 *)(param_1 + 0x280);
  }
  else if ((acStackX_20[0] == '\x01') || (acStackX_20[0] != '\x02')) {
    uStack_190 = *(undefined8 *)(param_1 + 0x284);
    uStack_188 = *(undefined8 *)(param_1 + 0x28c);
    uStack_180 = *(undefined4 *)(param_1 + 0x294);
  }
  else {
    uStack_190 = *(undefined8 *)(param_1 + 0x298);
    uStack_188 = *(undefined8 *)(param_1 + 0x2a0);
    uStack_180 = *(undefined4 *)(param_1 + 0x2a8);
  }
  lStack_118 = param_1;
  lStack_108 = param_1;
  if ((param_6 != '\0') && (acStackX_20[0] == '\x02')) {
    FUN_1482d1ac0(&lStack_108,4,0);
  }
  if ((int)puVar16[1] == 0) {
    uVar11 = FUN_1482d1660(&pppuStack_198,&uStack_190,1);
    FUN_1482d1ac0(&lStack_108,uVar11,0);
  }
  bVar35 = acStackX_20[0] != '\0';
  if (acStackX_20[0] == '\0') {
    lVar17 = 0x2b0;
  }
  else if ((acStackX_20[0] == '\x01') || (acStackX_20[0] != '\x02')) {
    lVar17 = 0x2c0;
  }
  else {
    lVar17 = 0x2d0;
  }
  plVar19 = (longlong *)(lVar17 + param_1);
  uVar34 = 6;
  if ((int)uStack_230 < 6) {
    uVar34 = uStack_230;
  }
  uVar12 = 1;
  if (1 < (int)uVar34) {
    uVar12 = uVar34;
  }
  uVar12 = uVar12 - 1;
  if (((plVar19 == (longlong *)0x0) || ((int)uVar12 < 0)) || ((int)plVar19[1] <= (int)uVar12)) {
    uStack_140 = 0;
    uStack_150 = _DAT_14d21cca0;
    uStack_148 = _UNK_14d21cca8;
  }
  else {
    uVar34 = 0;
    if ((int)uVar12 < (int)plVar19[1]) {
      uVar34 = ~uVar12 >> 0x1f;
    }
    if ((uVar34 == 0) &&
       (cVar10 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                               (longlong)(int)uVar12,(longlong)(int)plVar19[1]), cVar10 != '\0')) {
      pcVar7 = (code *)swi(3);
      puVar16 = (ulonglong *)(*pcVar7)();
      return puVar16;
    }
    puVar15 = (undefined8 *)(*plVar19 + (longlong)(int)uVar12 * 0x14);
    uStack_140 = *(undefined4 *)(*plVar19 + 0x10 + (longlong)(int)uVar12 * 0x14);
    uStack_150 = *puVar15;
    uStack_148 = puVar15[1];
  }
  uVar26 = 0;
  uVar11 = FUN_1482d1660(&pppuStack_198,&uStack_150,bVar35 + '\x01');
  FUN_1482d1ac0(&lStack_108,uVar11,1);
LAB_1482d8b90:
  do {
    uVar14 = (undefined4)((ulonglong)in_stack_fffffffffffffdb0 >> 0x20);
    iVar33 = (int)puVar16[1];
    if (1 < iVar33) goto LAB_1482d8d5f;
    if ((0 < (int)uStack_218) && (cVar10 = FUN_1482d2ce0(ppuStack_170,5), cVar10 == '\0')) {
      plStack_210 = (longlong *)0x0;
      uStack_208 = 0;
      iVar33 = (int)uStack_218;
      plVar19 = (longlong *)((longlong)plStack_220 + (longlong)(int)uStack_218);
      plVar31 = plStack_220;
      while( true ) {
        if ((int)uStack_218 != iVar33) {
          auStack_234[0] = 0;
          cVar10 = FUN_14be5bb00(auStack_234);
          if (cVar10 != '\0') {
            pcVar7 = (code *)swi(3);
            puVar16 = (ulonglong *)(*pcVar7)();
            return puVar16;
          }
        }
        if (plVar31 == plVar19) break;
        auStack_237[1] = (char)*plVar31;
        if ((auStack_237[1] != '\x16') && (cVar10 = FUN_1482d2dd0(ppuStack_168), cVar10 == '\0')) {
          if (plStack_210 <= auStack_237 + 1) {
            lVar17 = (longlong)(int)uStack_208._4_4_;
            if (auStack_237 + 1 < (undefined1 *)((longlong)plStack_210 + lVar17)) {
              cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                     &UNK_14bf25f80,auStack_237 + 1,plStack_210,lVar17,
                                     (longlong)(int)uStack_208,1);
              in_stack_fffffffffffffdb0 = lVar17;
              if (cVar10 != '\0') {
                pcVar7 = (code *)swi(3);
                puVar16 = (ulonglong *)(*pcVar7)();
                return puVar16;
              }
            }
          }
          uVar25 = uStack_208;
          lVar17 = (longlong)(int)uStack_208;
          uVar34 = (int)uStack_208 + 1;
          uStack_208 = CONCAT44(uStack_208._4_4_,uVar34);
          if (uStack_208._4_4_ < uVar34) {
            FUN_14830b890(&plStack_210,uVar25 & 0xffffffff);
          }
          *(char *)(lVar17 + (longlong)plStack_210) = auStack_237[1];
        }
        plVar31 = (longlong *)((longlong)plVar31 + 1);
      }
      iVar33 = (int)uStack_208;
      if (0 < (int)uStack_208) {
        uStack_227 = 8;
        uStack_226 = 0x16;
        uStack_224 = 0;
        uStack_228 = 5;
        uVar34 = (int)uStack_208 - 1;
        uVar25 = uVar26;
        if (0 < (int)uStack_208) {
          uVar12 = rand();
          uVar12 = (uint)((float)(uVar12 & 0x7fff) * (float)iVar33 * fVar8);
          if ((int)uVar12 < (int)uVar34) {
            uVar34 = uVar12;
          }
          uVar25 = (ulonglong)uVar34;
        }
        uVar12 = (uint)uVar25;
        uVar34 = 0;
        if ((int)uVar12 < (int)uStack_208) {
          uVar34 = ~uVar12 >> 0x1f;
        }
        if ((uVar34 == 0) &&
           (cVar10 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                                   (longlong)(int)uVar12,(longlong)(int)uStack_208), cVar10 != '\0')
           ) {
          pcVar7 = (code *)swi(3);
          puVar16 = (ulonglong *)(*pcVar7)();
          return puVar16;
        }
        puVar16 = puStack_178;
        uStack_226 = *(undefined1 *)((longlong)(int)uVar12 + (longlong)plStack_210);
        uStack_224 = 1;
        puVar5 = (undefined1 *)*puStack_178;
        if (((puVar5 <= &uStack_228) &&
            (lVar17 = (longlong)*(int *)((longlong)puStack_178 + 0xc),
            &uStack_228 < puVar5 + lVar17 * 8)) &&
           (cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                   &uStack_228,puVar5,lVar17,(longlong)(int)puStack_178[1],8),
           in_stack_fffffffffffffdb0 = lVar17, cVar10 != '\0')) {
          pcVar7 = (code *)swi(3);
          puVar16 = (ulonglong *)(*pcVar7)();
          return puVar16;
        }
        iVar33 = (int)puVar16[1];
        *(uint *)(puVar16 + 1) = iVar33 + 1U;
        if (*(uint *)((longlong)puVar16 + 0xc) < iVar33 + 1U) {
          FUN_14830b210(puVar16,iVar33);
        }
        *(ulonglong *)(*puVar16 + (longlong)iVar33 * 8) =
             CONCAT44(uStack_224,
                      CONCAT13(uStack_225,CONCAT12(uStack_226,CONCAT11(uStack_227,uStack_228))));
        puVar16 = puStack_1c8;
        if (plStack_210 != (longlong *)0x0) {
          FUN_140e289f0();
          puVar16 = puStack_1c8;
        }
        goto LAB_1482d8b90;
      }
      puVar16 = puStack_1c8;
      if (plStack_210 != (longlong *)0x0) {
        FUN_140e289f0();
        puVar16 = puStack_1c8;
      }
    }
    uVar14 = func_0x0001482d1a40(&puStack_120);
    cVar10 = FUN_1482d0ec0(&puStack_138,3,&pbStack_200,uVar14);
    if (((cVar10 == '\0') && (cVar10 = FUN_1482d0ec0(&puStack_138,2,&pbStack_1f0,1), cVar10 == '\0')
        ) && (cVar10 = FUN_1482d2f30(&puStack_1c0,1,iStack_1dc), cVar10 == '\0')) {
      cVar10 = FUN_1482d2f30(&puStack_1c0,0,uStack_22c);
      uVar14 = (undefined4)((ulonglong)in_stack_fffffffffffffdb0 >> 0x20);
      if (cVar10 == '\0') {
        iVar33 = (int)puVar16[1];
LAB_1482d8d5f:
        if ((iVar33 < 2) && (cVar10 = FUN_1482d2f30(&puStack_1c0,1,iStack_1dc), cVar10 == '\0')) {
          FUN_1482d2f30(&puStack_1c0,0,uStack_22c);
        }
        uVar34 = uStackX_18;
        if (((int)puVar16[1] < 2) && (2 < DAT_14edc6208)) {
          FUN_140f252a0(&DAT_14edc6208,&UNK_14d21b0d8,uStackX_18,acStackX_20[0],(int)puVar16[1],
                        uStack_1e8 & 0xffffffff,uStack_1f8 & 0xffffffff,
                        CONCAT44(uVar14,(int)uStack_218));
        }
        iVar33 = (int)puVar16[1];
        uVar12 = 0xffffffff;
        if (iVar33 < 1) {
          uVar23 = 0xffffffff;
        }
        else {
          bVar4 = *(byte *)*puVar16;
          uVar23 = (uint)bVar4;
          if (1 < iVar33) {
            uVar12 = (uint)((byte *)*puVar16)[8];
            uVar23 = (uint)bVar4;
          }
        }
        if (4 < DAT_14edc6208) {
          puVar20 = &UNK_14bf4e28c;
          if (param_6 != '\0') {
            puVar20 = &UNK_14bf4e298;
          }
          FUN_140f252a0(&DAT_14edc6208,&UNK_14d21b220,uVar34,acStackX_20[0],iVar33,uVar23,uVar12,
                        puVar20);
        }
        iVar33 = (int)puVar16[1];
        uVar25 = uVar26;
        if (0 < iVar33) {
          do {
            uVar12 = (uint)uVar26;
            uVar34 = 0;
            if ((int)uVar12 < iVar33) {
              uVar34 = ~uVar12 >> 0x1f;
            }
            if ((uVar34 == 0) &&
               (cVar10 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                       &UNK_14bf260f0,(longlong)(int)uVar12,(longlong)iVar33),
               cVar10 != '\0')) {
              pcVar7 = (code *)swi(3);
              puVar16 = (ulonglong *)(*pcVar7)();
              return puVar16;
            }
            uVar6 = *puVar16;
            if (2 < DAT_14edc6208) {
              FUN_140f252a0(&DAT_14edc6208,&UNK_14d21b300,uVar26,*(undefined1 *)(uVar25 + uVar6),
                            *(undefined1 *)(uVar25 + 1 + uVar6),*(undefined1 *)(uVar25 + 2 + uVar6),
                            *(undefined4 *)(uVar25 + 4 + uVar6));
            }
            uVar26 = (ulonglong)(uVar12 + 1);
            iVar33 = (int)puVar16[1];
            uVar25 = uVar25 + 8;
          } while ((int)(uVar12 + 1) < iVar33);
        }
        if (plStack_220 != (longlong *)0x0) {
          FUN_140e289f0();
        }
        if (pbStack_200 != (byte *)0x0) {
          FUN_140e289f0();
        }
        if (pbStack_1f0 != (byte *)0x0) {
          FUN_140e289f0();
        }
        return puVar16;
      }
    }
  } while( true );
LAB_1482d8553:
  if ((int)param_5[1] != *(int *)((longlong)param_5 + 0x34)) {
    plVar19 = param_5 + 7;
    if ((longlong *)param_5[8] != (longlong *)0x0) {
      plVar19 = (longlong *)param_5[8];
    }
    iVar29 = *(int *)((longlong)plVar19 +
                     ((ulonglong)((int)param_5[9] - 1) & (ulonglong)bStack_238) * 4);
    if (iVar29 != -1) {
      do {
        pbVar2 = (byte *)(*param_5 + (longlong)iVar29 * 0x18);
        if (*pbVar2 == bStack_238) {
          pbVar21 = pbVar2 + 4;
          if (pbVar2 == (byte *)0x0) {
            pbVar21 = (byte *)0x0;
          }
          if ((pbVar21 != (byte *)0x0) && (*pbVar21 != 0)) {
            iVar29 = 1;
            if (1 < *(int *)(pbVar21 + 4)) {
              iVar29 = *(int *)(pbVar21 + 4);
            }
            if (((*(char *)(lVar17 + 0x38) == '\0') || (4 < iVar29)) ||
               (iVar29 = FUN_1482f8c80(param_1,bStack_238), iVar29 < 1)) goto LAB_1482d8656;
            if (pbStack_200 <= &bStack_238) {
              lVar17 = (longlong)(int)uStack_1f8._4_4_;
              if (&bStack_238 < pbStack_200 + lVar17) {
                cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                       &UNK_14bf25f80,&bStack_238,pbStack_200,lVar17,
                                       (longlong)(int)uStack_1f8,1);
                in_stack_fffffffffffffdb0 = lVar17;
                if (cVar10 != '\0') {
                  pcVar7 = (code *)swi(3);
                  puVar16 = (ulonglong *)(*pcVar7)();
                  return puVar16;
                }
              }
            }
            uVar26 = uStack_1f8;
            lVar17 = (longlong)(int)uStack_1f8;
            uVar34 = (int)uStack_1f8 + 1;
            uStack_1f8 = CONCAT44(uStack_1f8._4_4_,uVar34);
            if (uStack_1f8._4_4_ < uVar34) {
              FUN_14830b7f0(&pbStack_200,uVar26 & 0xffffffff);
            }
            pbStack_200[lVar17] = bStack_238;
            pbVar27 = pbVar27 + 1;
            goto LAB_1482d84e0;
          }
          break;
        }
        iVar29 = *(int *)(pbVar2 + 0x10);
      } while (iVar29 != -1);
    }
  }
  if (pbStack_1f0 <= &bStack_238) {
    lVar17 = (longlong)(int)uStack_1e8._4_4_;
    if (&bStack_238 < pbStack_1f0 + lVar17) {
      cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                             &bStack_238,pbStack_1f0,lVar17,(longlong)(int)uStack_1e8,1);
      in_stack_fffffffffffffdb0 = lVar17;
      if (cVar10 != '\0') {
        pcVar7 = (code *)swi(3);
        puVar16 = (ulonglong *)(*pcVar7)();
        return puVar16;
      }
    }
  }
  uVar26 = uStack_1e8;
  lVar17 = (longlong)(int)uStack_1e8;
  uVar34 = (int)uStack_1e8 + 1;
  uStack_1e8 = CONCAT44(uStack_1e8._4_4_,uVar34);
  if (uStack_1e8._4_4_ < uVar34) {
    FUN_14830b7f0(&pbStack_1f0,uVar26 & 0xffffffff);
  }
  pbStack_1f0[lVar17] = bStack_238;
LAB_1482d8656:
  pbVar27 = pbVar27 + 1;
  goto LAB_1482d84e0;
}

