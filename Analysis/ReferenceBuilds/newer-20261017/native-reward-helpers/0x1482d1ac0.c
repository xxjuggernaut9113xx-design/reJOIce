// Selected newer-build routine; caller-supplied label: DispatchRewardCategory
// Address: 0x1482d1ac0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: DispatchRewardCategory */

undefined8 FUN_1482d1ac0(longlong *param_1,byte param_2,char param_3)

{
  longlong lVar1;
  ulonglong *puVar2;
  undefined1 *puVar3;
  code *pcVar4;
  char cVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  longlong *plVar8;
  undefined1 uVar9;
  int iVar10;
  float fVar11;
  undefined8 unaff_retaddr;
  undefined1 uStack_18;
  undefined2 uStack_17;
  undefined1 uStack_15;
  int iStack_14;
  
  switch((ulonglong)param_2) {
  default:
    goto LAB_1482d1c79;
  case 1:
    lVar1 = *param_1;
    fVar11 = *(float *)(lVar1 + 0x244);
    if (*(char *)param_1[1] == '\0') {
      if (param_3 == '\0') {
        fVar11 = *(float *)(lVar1 + 0x238);
      }
      else {
        fVar11 = *(float *)(lVar1 + 0x23c);
      }
    }
    else if (*(char *)param_1[1] == '\x02') {
      fVar11 = *(float *)(lVar1 + 0x254);
    }
    else if (param_3 != '\0') {
      fVar11 = *(float *)(lVar1 + 0x248);
    }
    plVar8 = (longlong *)param_1[2];
    uVar9 = 0;
    iVar10 = (int)ROUND((float)*(int *)param_1[3] * (fVar11 + fVar11) + _DAT_14bf3cd28) >> 1;
    goto code_r0x0001482d2f30;
  case 2:
    uVar9 = 1;
    plVar8 = (longlong *)param_1[2];
    iVar10 = *(int *)param_1[4];
code_r0x0001482d2f30:
    cVar5 = FUN_1482d2ce0(plVar8[1]);
    if (cVar5 != '\0') {
      return 0;
    }
    uStack_17 = 0x1608;
    if (iVar10 < 1) {
      iVar10 = 1;
    }
    puVar2 = (ulonglong *)*plVar8;
    puVar3 = (undefined1 *)*puVar2;
    uStack_18 = uVar9;
    iStack_14 = iVar10;
    if (((puVar3 <= &uStack_18) &&
        (&uStack_18 < puVar3 + (longlong)*(int *)((longlong)puVar2 + 0xc) * 8)) &&
       (cVar5 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                              &uStack_18,puVar3,(longlong)*(int *)((longlong)puVar2 + 0xc),
                              (longlong)(int)puVar2[1],8), cVar5 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar7 = (*pcVar4)();
      return uVar7;
    }
    iVar10 = (int)puVar2[1];
    *(uint *)(puVar2 + 1) = iVar10 + 1U;
    if (*(uint *)((longlong)puVar2 + 0xc) < iVar10 + 1U) {
      FUN_14830b210(puVar2,iVar10);
    }
    *(ulonglong *)(*puVar2 + (longlong)iVar10 * 8) =
         CONCAT44(iStack_14,CONCAT13(uStack_15,CONCAT21(uStack_17,uStack_18)));
    return 1;
  case 3:
    uVar6 = func_0x0001482d1a40(param_1[5]);
    cVar5 = FUN_1482d0ec0(param_1[6],3,param_1[7],uVar6);
    if (cVar5 != '\0') {
      return 1;
    }
    cVar5 = FUN_1482d11b0(param_1[8],param_1[9]);
    break;
  case 4:
    cVar5 = FUN_1482d0ec0(param_1[6],
                          CONCAT71((int7)((ulonglong)
                                          (IMAGE_DOS_HEADER_140000000.e_magic +
                                          *(uint *)(&UNK_1482d1c84 + (ulonglong)param_2 * 4)) >> 8),
                                   2),param_1[10],1);
    if (cVar5 != '\0') {
      return 1;
    }
    uVar6 = func_0x0001482d1a40(param_1[5]);
    cVar5 = FUN_1482d0ec0(param_1[6],3,param_1[7],uVar6);
    if (cVar5 != '\0') {
      return 1;
    }
    cVar5 = FUN_1482d11b0(param_1[8],param_1[9]);
    goto code_r0x0001482d1bc2;
  case 5:
    cVar5 = FUN_1482d11b0(param_1[8],param_1[9]);
    if (cVar5 != '\0') {
      return 1;
    }
    uVar6 = func_0x0001482d1a40(param_1[5]);
    cVar5 = FUN_1482d0ec0(param_1[6],3,param_1[7],uVar6);
  }
  if (cVar5 == '\0') {
    cVar5 = FUN_1482d0ec0(param_1[6],2,param_1[10],1);
code_r0x0001482d1bc2:
    if (((cVar5 == '\0') &&
        (cVar5 = FUN_1482d2f30(param_1[2],1,*(undefined4 *)param_1[4]), cVar5 == '\0')) &&
       (cVar5 = FUN_1482d2f30(param_1[2],0,*(undefined4 *)param_1[3]), cVar5 == '\0')) {
LAB_1482d1c79:
      return 0;
    }
  }
  return 1;
}

