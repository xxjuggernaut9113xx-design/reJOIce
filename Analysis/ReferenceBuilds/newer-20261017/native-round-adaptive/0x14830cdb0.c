// Selected newer-build routine; caller-supplied label: RollAdaptiveDifficultyTier_URoundManager
// Address: 0x14830cdb0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: RollAdaptiveDifficultyTier_URoundManager */

ulonglong FUN_14830cdb0(longlong param_1,undefined8 param_2,undefined8 param_3)

{
  float *pfVar1;
  code *pcVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  ulonglong uVar7;
  uint uVar8;
  float *pfVar9;
  longlong lVar10;
  longlong lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  undefined8 unaff_retaddr;
  undefined1 auStackX_8 [8];
  float *pfStack_a8;
  undefined8 uStack_a0;
  
  if ((*(char *)(param_1 + 0xc0) == '\0') && (*(int *)(param_1 + 0xbc) < 2)) {
    uVar7 = 1;
  }
  else {
    fVar12 = (float)func_0x0001482ef930();
    fVar13 = (float)FUN_1482d76b0(param_1,param_3);
    fVar16 = _DAT_14bf2ebec;
    fVar17 = 0.0;
    if (fVar13 <= 0.0) {
      fVar18 = *(float *)(param_1 + 0x32c);
    }
    else {
      fVar18 = *(float *)(param_1 + 0x328);
    }
    fVar14 = (float)((uint)(fVar18 * fVar13) ^ _DAT_14bf56aa0);
    fVar18 = fVar14 + fVar12;
    if (_DAT_14bf2ebec <= fVar18) {
      fVar18 = _DAT_14bf2ebec;
    }
    if (fVar18 <= 0.0) {
      fVar18 = 0.0;
    }
    if (4 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d21ae70,(double)fVar12,(double)fVar13,(double)fVar14,
                    (double)fVar18);
    }
    pfStack_a8 = (float *)0x0;
    uStack_a0 = 5;
    FUN_140d21ce0(&pfStack_a8,0);
    pfStack_a8[0] = 0.0;
    pfStack_a8[1] = 0.0;
    pfStack_a8[2] = 0.0;
    pfStack_a8[3] = 0.0;
    pfStack_a8[4] = 0.0;
    fVar14 = _DAT_14bf8cea0;
    fVar13 = _DAT_14bf8ce7c;
    uVar6 = _DAT_14bf56a80;
    fVar12 = _DAT_14bf3cd38;
    uVar8 = 0;
    lVar11 = 0;
    lVar10 = 0;
    do {
      fVar15 = fVar16 - (float)((uint)(fVar18 - (float)(int)uVar8 * fVar14) & uVar6) * fVar12;
      if (fVar15 <= 0.0) {
        fVar15 = 0.0;
      }
      uVar5 = 0;
      if ((int)uVar8 < (int)uStack_a0) {
        uVar5 = ~uVar8 >> 0x1f;
      }
      if ((uVar5 == 0) &&
         (cVar4 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                                lVar10,(longlong)(int)uStack_a0), cVar4 != '\0')) {
        pcVar2 = (code *)swi(3);
        uVar7 = (*pcVar2)();
        return uVar7;
      }
      *(float *)(lVar11 + (longlong)pfStack_a8) = fVar15 * fVar15 + fVar13;
      uVar8 = uVar8 + 1;
      lVar10 = lVar10 + 1;
      lVar11 = lVar11 + 4;
    } while ((int)uVar8 < 5);
    fVar16 = 0.0;
    iVar3 = (int)uStack_a0;
    pfVar1 = pfStack_a8 + (int)uStack_a0;
    pfVar9 = pfStack_a8;
    while( true ) {
      if ((int)uStack_a0 != iVar3) {
        auStackX_8[0] = 0;
        cVar4 = FUN_14bd65c50(auStackX_8);
        if (cVar4 != '\0') {
          pcVar2 = (code *)swi(3);
          uVar7 = (*pcVar2)();
          return uVar7;
        }
      }
      if (pfVar9 == pfVar1) break;
      fVar16 = fVar16 + *pfVar9;
      pfVar9 = pfVar9 + 1;
    }
    uVar6 = rand();
    fVar12 = (float)(uVar6 & 0x7fff) * _DAT_14bf3cd14;
    uVar6 = 0;
    lVar10 = 0;
    do {
      uVar8 = 0;
      if ((int)uVar6 < (int)uStack_a0) {
        uVar8 = ~uVar6 >> 0x1f;
      }
      if ((uVar8 == 0) &&
         (cVar4 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                                (longlong)(int)uVar6,(longlong)(int)uStack_a0), cVar4 != '\0')) {
        pcVar2 = (code *)swi(3);
        uVar7 = (*pcVar2)();
        return uVar7;
      }
      fVar17 = fVar17 + *(float *)(lVar10 + (longlong)pfStack_a8);
      uVar6 = uVar6 + 1;
      uVar8 = uVar6;
    } while ((fVar17 < fVar12 * fVar16) && (lVar10 = lVar10 + 4, uVar8 = 5, (int)uVar6 < 5));
    if (pfStack_a8 != (float *)0x0) {
      FUN_140e289f0();
    }
    uVar7 = (ulonglong)uVar8;
  }
  return uVar7;
}

