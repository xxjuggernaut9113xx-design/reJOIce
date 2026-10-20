// Selected newer-build routine; caller-supplied label: CalculateAdaptivePressure_URoundManager
// Address: 0x1482d76b0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: CalculateAdaptivePressure_URoundManager */

void FUN_1482d76b0(longlong param_1,longlong *param_2)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  code *pcVar7;
  char cVar8;
  int iVar9;
  uint uVar10;
  longlong lVar11;
  uint uVar12;
  int iVar13;
  longlong lVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  undefined8 unaff_retaddr;
  undefined1 auStack_158 [32];
  undefined *puStack_138;
  double dStack_130;
  double dStack_128;
  double dStack_120;
  double dStack_118;
  double dStack_110;
  float fStack_108;
  float fStack_104;
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  float fStack_f4;
  float fStack_f0;
  float afStack_e8 [4];
  ulonglong uStack_d8;
  
  uStack_d8 = _DAT_14ed716f8 ^ (ulonglong)auStack_158;
  iVar6 = (int)param_2[1];
  if (iVar6 == 0) {
    fVar15 = 0.0;
    goto LAB_1482d7c44;
  }
  fStack_f0 = (float)FUN_1482ef930(param_1,*(undefined4 *)(param_1 + 0xb8));
  fVar17 = _DAT_14bf2ebec;
  fStack_f4 = (float)func_0x00014ba12492(_DAT_14bf2ebec - fStack_f0,*(undefined4 *)(param_1 + 0x330)
                                        );
  fStack_f4 = fVar17 - fStack_f4;
  iVar13 = 0;
  iVar9 = 3;
  if (iVar6 < 3) {
    iVar9 = iVar6;
  }
  afStack_e8[0] = 0.6;
  fVar15 = 0.0;
  afStack_e8[1] = 0.3;
  fVar25 = (*(float *)(param_1 + 0x2ec) - *(float *)(param_1 + 0x2e8)) * fStack_f4 +
           *(float *)(param_1 + 0x2e8);
  fStack_104 = 0.0;
  afStack_e8[2] = 0.1;
  fStack_f8 = (*(float *)(param_1 + 0x2e4) - *(float *)(param_1 + 0x2e0)) * fStack_f4 +
              *(float *)(param_1 + 0x2e0);
  fStack_fc = (*(float *)(param_1 + 0x2fc) - *(float *)(param_1 + 0x2f8)) * fStack_f4 +
              *(float *)(param_1 + 0x2f8);
  fStack_108 = (*(float *)(param_1 + 0x2f4) - *(float *)(param_1 + 0x2f0)) * fStack_f4 +
               *(float *)(param_1 + 0x2f0);
  fStack_100 = (*(float *)(param_1 + 0x304) - *(float *)(param_1 + 0x300)) * fStack_f4 +
               *(float *)(param_1 + 0x300);
  if (iVar9 < 1) {
LAB_1482d7b4f:
    fVar15 = 0.0;
  }
  else {
    lVar14 = 0;
    do {
      fVar2 = fStack_f8;
      fVar20 = fStack_fc;
      fVar21 = fStack_100;
      fVar22 = _DAT_14bf8ce7c;
      fVar16 = _DAT_14bf3cd20;
      iVar6 = (int)param_2[1];
      uVar12 = (iVar6 - iVar13) - 1;
      uVar10 = 0;
      if ((int)uVar12 < iVar6) {
        uVar10 = ~uVar12 >> 0x1f;
      }
      if (uVar10 == 0) {
        dStack_130 = (double)(longlong)(int)uVar12;
        puStack_138 = &UNK_14bf260f0;
        dStack_128 = (double)(longlong)iVar6;
        cVar8 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr);
        if (cVar8 != '\0') {
          pcVar7 = (code *)swi(3);
          (*pcVar7)();
          return;
        }
      }
      fVar24 = 0.0;
      lVar11 = (longlong)(int)uVar12 * 0xc0 + *param_2;
      iVar6 = *(int *)(lVar11 + 4);
      fVar16 = (float)*(int *)(lVar11 + 0x28) * fVar16;
      if (fVar16 <= fVar22) {
        fVar16 = fVar22;
      }
      fVar17 = fVar17 / fVar16;
      if ((0 < iVar6) && (0.0 < *(float *)(param_1 + 0x33c))) {
        fVar24 = ((float)iVar6 * fVar17 - fVar2) / *(float *)(param_1 + 0x33c);
      }
      if (*(float *)(param_1 + 0x340) <= 0.0) {
        fVar16 = 0.0;
      }
      else {
        fVar16 = ((float)*(int *)(lVar11 + 0x80) * fVar17 - fVar25) / *(float *)(param_1 + 0x340);
      }
      if (*(float *)(param_1 + 0x344) <= 0.0) {
        fVar22 = 0.0;
      }
      else {
        fVar22 = (fStack_108 - (float)*(int *)(lVar11 + 0x84) * fVar17) /
                 *(float *)(param_1 + 0x344);
      }
      if (*(float *)(param_1 + 0x348) <= 0.0) {
        fVar20 = 0.0;
      }
      else {
        fVar20 = (fVar20 - (float)*(int *)(lVar11 + 0x18) * fVar17) / *(float *)(param_1 + 0x348);
      }
      if (*(float *)(param_1 + 0x34c) <= 0.0) {
        fVar17 = 0.0;
      }
      else {
        fVar17 = (fVar21 - (float)*(int *)(lVar11 + 0x78) * fVar17) / *(float *)(param_1 + 0x34c);
      }
      if (iVar6 < 1) {
        fVar21 = 0.0;
      }
      else {
        fVar21 = *(float *)(param_1 + 0x310);
      }
      fVar2 = *(float *)(param_1 + 800);
      fVar3 = *(float *)(param_1 + 0x31c);
      fVar4 = *(float *)(param_1 + 0x314);
      fVar5 = *(float *)(param_1 + 0x318);
      fVar23 = fVar2 + fVar3 + fVar5 + fVar4 + fVar21;
      fVar18 = fVar2 + fVar3 + fVar5 + fVar4 + *(float *)(param_1 + 0x310);
      fVar19 = _DAT_14bf2ebec;
      if ((0.0 < fVar23) && (0.0 < fVar18)) {
        fVar19 = fVar18 / fVar23;
      }
      pfVar1 = afStack_e8 + lVar14;
      iVar13 = iVar13 + 1;
      lVar14 = lVar14 + 1;
      fStack_104 = fStack_104 + *pfVar1;
      fVar15 = fVar15 + (fVar2 * fVar17 + fVar3 * fVar20 + fVar5 * fVar22 +
                        fVar4 * fVar16 + fVar21 * fVar24) * fVar19 * *pfVar1;
      fVar17 = _DAT_14bf2ebec;
    } while (lVar14 < iVar9);
    if (fStack_104 <= 0.0) goto LAB_1482d7b4f;
    fVar15 = fVar15 / fStack_104;
  }
  if (4 < DAT_14edc6208) {
    dStack_110 = (double)fStack_100;
    dStack_118 = (double)fStack_fc;
    dStack_120 = (double)fStack_108;
    dStack_128 = (double)fVar25;
    dStack_130 = (double)fStack_f8;
    puStack_138 = (undefined *)(double)fStack_f4;
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d21acf8,(double)fVar15,(double)fStack_f0);
  }
LAB_1482d7c44:
  FUN_14b9fb8d0(fVar15);
  return;
}

