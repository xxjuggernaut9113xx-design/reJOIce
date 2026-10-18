// Analyst label for direct call target: ParseBeatArrayPostprocess
// Address: 0x1482cbab0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Direct call target from the newer parser; analyst-assigned label. */

void FUN_1482cbab0(longlong param_1,int param_2,undefined1 param_3,undefined8 param_4)

{
  longlong lVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  longlong lVar6;
  int iVar7;
  double *pdVar8;
  double *pdVar9;
  double *pdVar10;
  double *pdVar11;
  double *pdVar12;
  double *pdVar13;
  longlong *plVar14;
  float fVar15;
  undefined1 auStack_378 [48];
  longlong lStack_348;
  longlong lStack_338;
  longlong lStack_330;
  undefined4 uStack_328;
  undefined1 auStack_320 [744];
  ulonglong uStack_38;
  
  uStack_38 = _DAT_14ed716f8 ^ (ulonglong)auStack_378;
  if (1 < param_2) {
    lStack_330 = param_1 + -0x18 + (longlong)param_2 * 0x18;
    lStack_338 = param_1;
    fVar15 = (float)func_0x00014ba122b2();
    uStack_328 = (undefined4)(longlong)(fVar15 + fVar15);
    func_0x00014ba120f6(auStack_320,0,0x2e8);
    plVar14 = &lStack_338;
    do {
      pdVar8 = (double *)plVar14[1];
      pdVar13 = (double *)*plVar14;
      lVar1 = plVar14[2];
      lStack_348._0_4_ = (int)lVar1;
      iVar7 = (int)(((longlong)pdVar8 - (longlong)pdVar13) / 0x18) + 1;
      pdVar12 = pdVar13;
      if ((int)lStack_348 != 0) {
LAB_1482cbb80:
        if (8 < iVar7) {
          dVar3 = pdVar12[1];
          pdVar10 = pdVar8 + 3;
          lVar6 = (longlong)(iVar7 / 2);
          dVar4 = pdVar12[lVar6 * 3];
          dVar5 = (pdVar12 + lVar6 * 3)[1];
          dVar2 = pdVar12[lVar6 * 3 + 2];
          pdVar12[lVar6 * 3] = *pdVar12;
          (pdVar12 + lVar6 * 3)[1] = dVar3;
          pdVar12[lVar6 * 3 + 2] = pdVar12[2];
          *pdVar12 = dVar4;
          pdVar12[1] = dVar5;
          pdVar12[2] = dVar2;
          pdVar13 = pdVar12;
LAB_1482cbbd0:
          pdVar9 = pdVar13;
          pdVar13 = pdVar9 + 3;
          if (pdVar13 <= pdVar8) goto code_r0x0001482cbbd9;
          goto LAB_1482cbbe5;
        }
        for (; pdVar10 = pdVar12, pdVar13 = pdVar12, pdVar12 < pdVar8; pdVar8 = pdVar8 + -3) {
          while (pdVar13 = pdVar13 + 3, pdVar13 <= pdVar8) {
            if (*pdVar10 < *pdVar13) {
              pdVar10 = pdVar13;
            }
          }
          dVar3 = *pdVar10;
          dVar4 = pdVar10[1];
          dVar2 = pdVar10[2];
          dVar5 = pdVar8[1];
          *pdVar10 = *pdVar8;
          pdVar10[1] = dVar5;
          pdVar10[2] = pdVar8[2];
          *pdVar8 = dVar3;
          pdVar8[1] = dVar4;
          pdVar8[2] = dVar2;
        }
        goto LAB_1482cbd09;
      }
LAB_1482cbcfa:
      lStack_348 = lVar1;
      FUN_1482cab50(pdVar13,iVar7,param_3,param_4);
      lVar1 = lStack_348;
LAB_1482cbd09:
      lStack_348 = lVar1;
      plVar14 = plVar14 + -3;
    } while (&lStack_338 <= plVar14);
  }
  FUN_14b9fb8d0(uStack_38 ^ (ulonglong)auStack_378);
  return;
code_r0x0001482cbbd9:
  if (*pdVar13 < *pdVar12 || *pdVar13 == *pdVar12) goto LAB_1482cbbd0;
LAB_1482cbbe5:
  do {
    pdVar11 = pdVar10;
    pdVar10 = pdVar11 + -3;
    if (pdVar10 <= pdVar12) break;
  } while (*pdVar12 < *pdVar10 || *pdVar12 == *pdVar10);
  dVar2 = pdVar11[-2];
  if (pdVar13 <= pdVar10) {
    dVar4 = *pdVar13;
    dVar5 = pdVar9[4];
    dVar3 = pdVar9[5];
    *pdVar13 = *pdVar10;
    pdVar9[4] = dVar2;
    pdVar9[5] = pdVar11[-1];
    *pdVar10 = dVar4;
    pdVar11[-2] = dVar5;
    pdVar11[-1] = dVar3;
    goto LAB_1482cbbd0;
  }
  dVar4 = *pdVar12;
  dVar5 = pdVar12[1];
  dVar3 = pdVar12[2];
  lVar6 = (longlong)pdVar10 + (-0x18 - (longlong)pdVar12);
  lStack_348._0_4_ = (int)lStack_348 + -1;
  lVar6 = lVar6 / 6 + (lVar6 >> 0x3f);
  *pdVar12 = *pdVar10;
  pdVar12[1] = dVar2;
  pdVar12[2] = pdVar11[-1];
  *pdVar10 = dVar4;
  pdVar11[-2] = dVar5;
  pdVar11[-1] = dVar3;
  if ((lVar6 >> 2) - (lVar6 >> 0x3f) < ((longlong)pdVar8 - (longlong)pdVar13) / 0x18) {
    if (pdVar13 < pdVar8) {
      *plVar14 = (longlong)pdVar13;
      plVar14[1] = (longlong)pdVar8;
      *(int *)(plVar14 + 2) = (int)lStack_348;
      plVar14 = plVar14 + 3;
    }
    if (pdVar10 <= pdVar12 + 3) goto LAB_1482cbd09;
    pdVar8 = pdVar11 + -6;
    pdVar13 = pdVar12;
  }
  else {
    if (pdVar12 + 3 < pdVar10) {
      *plVar14 = (longlong)pdVar12;
      plVar14[1] = (longlong)(pdVar11 + -6);
      *(int *)(plVar14 + 2) = (int)lStack_348;
      plVar14 = plVar14 + 3;
    }
    if (pdVar8 <= pdVar13) goto LAB_1482cbd09;
  }
  iVar7 = (int)(((longlong)pdVar8 - (longlong)pdVar13) / 0x18) + 1;
  pdVar12 = pdVar13;
  if ((int)lStack_348 == 0) goto LAB_1482cbcfa;
  goto LAB_1482cbb80;
}

