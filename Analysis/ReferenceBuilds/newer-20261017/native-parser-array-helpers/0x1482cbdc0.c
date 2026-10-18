// Analyst label for direct call target: ParseEventArrayPostprocess
// Address: 0x1482cbdc0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Direct call target from the newer parser; analyst-assigned label. */

void FUN_1482cbdc0(longlong param_1,int param_2,undefined1 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  char cVar7;
  longlong lVar8;
  int iVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  undefined8 *puVar13;
  undefined8 *puVar14;
  longlong *plVar15;
  int iVar16;
  float fVar17;
  undefined1 auStack_388 [48];
  longlong lStack_358;
  longlong lStack_348;
  longlong lStack_340;
  undefined4 uStack_338;
  undefined1 auStack_330 [744];
  ulonglong uStack_48;
  
  uStack_48 = _DAT_14ed716f8 ^ (ulonglong)auStack_388;
  if (1 < param_2) {
    lStack_340 = param_1 + -0x28 + (longlong)param_2 * 0x28;
    lStack_348 = param_1;
    fVar17 = (float)func_0x00014ba122b2();
    uStack_338 = (undefined4)(longlong)(fVar17 + fVar17);
    func_0x00014ba120f6(auStack_330,0,0x2e8);
    plVar15 = &lStack_348;
    do {
      puVar10 = (undefined8 *)plVar15[1];
      puVar12 = (undefined8 *)*plVar15;
      lStack_358 = plVar15[2];
      iVar9 = (int)(((longlong)puVar10 - (longlong)puVar12) / 0x28) + 1;
      puVar11 = puVar12;
      iVar16 = (int)lStack_358;
      if ((int)lStack_358 != 0) {
LAB_1482cbea0:
        if (8 < iVar9) {
          uVar2 = puVar11[1];
          puVar13 = puVar10 + 5;
          lVar8 = (longlong)(iVar9 / 2);
          uVar3 = puVar11[lVar8 * 5];
          uVar4 = (puVar11 + lVar8 * 5)[1];
          uVar5 = puVar11[lVar8 * 5 + 2];
          uVar6 = (puVar11 + lVar8 * 5 + 2)[1];
          uVar1 = puVar11[lVar8 * 5 + 4];
          puVar11[lVar8 * 5] = *puVar11;
          (puVar11 + lVar8 * 5)[1] = uVar2;
          uVar2 = puVar11[3];
          puVar11[lVar8 * 5 + 2] = puVar11[2];
          (puVar11 + lVar8 * 5 + 2)[1] = uVar2;
          puVar11[lVar8 * 5 + 4] = puVar11[4];
          *puVar11 = uVar3;
          puVar11[1] = uVar4;
          puVar11[2] = uVar5;
          puVar11[3] = uVar6;
          puVar11[4] = uVar1;
          puVar12 = puVar11;
LAB_1482cbef4:
          puVar12 = puVar12 + 5;
          if (puVar12 <= puVar10) goto code_r0x0001482cbefd;
          goto LAB_1482cbf10;
        }
        for (; puVar13 = puVar11, puVar12 = puVar11, puVar11 < puVar10; puVar10 = puVar10 + -5) {
          while (puVar14 = puVar13, puVar12 = puVar12 + 5, puVar12 <= puVar10) {
            cVar7 = func_0x0001482d2c40(param_4,puVar14,puVar12);
            puVar13 = puVar12;
            if (cVar7 == '\0') {
              puVar13 = puVar14;
            }
          }
          uVar2 = *puVar14;
          uVar3 = puVar14[1];
          uVar1 = puVar14[4];
          uVar4 = puVar14[2];
          uVar5 = puVar14[3];
          uVar6 = puVar10[1];
          *puVar14 = *puVar10;
          puVar14[1] = uVar6;
          uVar6 = puVar10[3];
          puVar14[2] = puVar10[2];
          puVar14[3] = uVar6;
          puVar14[4] = puVar10[4];
          *puVar10 = uVar2;
          puVar10[1] = uVar3;
          puVar10[2] = uVar4;
          puVar10[3] = uVar5;
          puVar10[4] = uVar1;
        }
        goto LAB_1482cc05e;
      }
LAB_1482cc04f:
      FUN_1482cad80(puVar12,iVar9,param_3,param_4);
LAB_1482cc05e:
      plVar15 = plVar15 + -3;
    } while (&lStack_348 <= plVar15);
  }
  FUN_14b9fb8d0(uStack_48 ^ (ulonglong)auStack_388);
  return;
code_r0x0001482cbefd:
  cVar7 = func_0x0001482d2c40(param_4,puVar11,puVar12);
  if (cVar7 == '\0') goto LAB_1482cbef4;
LAB_1482cbf10:
  do {
    puVar13 = puVar13 + -5;
    if (puVar13 <= puVar11) break;
    cVar7 = func_0x0001482d2c40(param_4,puVar13,puVar11);
  } while (cVar7 == '\0');
  uVar1 = puVar13[1];
  if (puVar12 <= puVar13) {
    uVar3 = *puVar12;
    uVar4 = puVar12[1];
    uVar5 = puVar12[2];
    uVar6 = puVar12[3];
    uVar2 = puVar12[4];
    *puVar12 = *puVar13;
    puVar12[1] = uVar1;
    uVar1 = puVar13[3];
    puVar12[2] = puVar13[2];
    puVar12[3] = uVar1;
    puVar12[4] = puVar13[4];
    *puVar13 = uVar3;
    puVar13[1] = uVar4;
    puVar13[2] = uVar5;
    puVar13[3] = uVar6;
    puVar13[4] = uVar2;
    goto LAB_1482cbef4;
  }
  uVar3 = *puVar11;
  uVar4 = puVar11[1];
  uVar5 = puVar11[2];
  uVar6 = puVar11[3];
  iVar16 = iVar16 + -1;
  uVar2 = puVar11[4];
  *puVar11 = *puVar13;
  puVar11[1] = uVar1;
  uVar1 = puVar13[3];
  puVar11[2] = puVar13[2];
  puVar11[3] = uVar1;
  puVar11[4] = puVar13[4];
  *puVar13 = uVar3;
  puVar13[1] = uVar4;
  puVar13[2] = uVar5;
  puVar13[3] = uVar6;
  puVar13[4] = uVar2;
  if (((longlong)puVar13 + (-0x28 - (longlong)puVar11)) / 0x28 <
      ((longlong)puVar10 - (longlong)puVar12) / 0x28) {
    if (puVar12 < puVar10) {
      *plVar15 = (longlong)puVar12;
      plVar15[1] = (longlong)puVar10;
      *(int *)(plVar15 + 2) = iVar16;
      plVar15 = plVar15 + 3;
    }
    if (puVar13 <= puVar11 + 5) goto LAB_1482cc05e;
    puVar10 = puVar13 + -5;
    puVar12 = puVar11;
  }
  else {
    if (puVar11 + 5 < puVar13) {
      *plVar15 = (longlong)puVar11;
      plVar15[1] = (longlong)(puVar13 + -5);
      *(int *)(plVar15 + 2) = iVar16;
      plVar15 = plVar15 + 3;
    }
    if (puVar10 <= puVar12) goto LAB_1482cc05e;
  }
  iVar9 = (int)(((longlong)puVar10 - (longlong)puVar12) / 0x28) + 1;
  puVar11 = puVar12;
  if (iVar16 == 0) goto LAB_1482cc04f;
  goto LAB_1482cbea0;
}

