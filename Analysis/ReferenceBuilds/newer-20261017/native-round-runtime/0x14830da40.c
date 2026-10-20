// Selected newer-build routine; caller-supplied label: RollObjectiveParam_URoundManager
// Address: 0x14830da40
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: RollObjectiveParam_URoundManager */

ulonglong FUN_14830da40(longlong param_1,char param_2,int param_3)

{
  longlong *plVar1;
  uint uVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  uint uVar6;
  int iVar7;
  ulonglong uVar8;
  undefined *puVar9;
  int iVar10;
  longlong *plVar11;
  longlong unaff_GS_OFFSET;
  undefined1 auStackX_8 [8];
  longlong *plStack_28;
  undefined8 uStack_20;
  
  if (*(longlong *)(param_1 + 0x200) == 0) {
    if (2 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d21b590);
    }
    uVar8 = 0;
  }
  else {
    if ((*(int *)(*(longlong *)(*(longlong *)(unaff_GS_OFFSET + 0x58) + (ulonglong)__tls_index * 8)
                 + 0x90ac) < _DAT_14f0d3528) &&
       (FUN_14b9fb4c4(&DAT_14f0d3528), _DAT_14f0d3528 == -1)) {
      FUN_140cf7e50(&DAT_14f0d3518,&UNK_14d21b6b0);
      FUN_14b9fb19c(FUN_14bca8b80);
      FUN_14b9fb45c(&DAT_14f0d3528);
    }
    plStack_28 = (longlong *)0x0;
    uStack_20 = 0;
    puVar9 = &UNK_14bf24094;
    if (_DAT_14f0d3520 != 0) {
      puVar9 = _DAT_14f0d3518;
    }
    FUN_1482c9a70(*(undefined8 *)(param_1 + 0x200),puVar9,&plStack_28);
    iVar10 = (int)uStack_20;
    plVar1 = plStack_28 + (int)uStack_20;
    plVar11 = plStack_28;
    while( true ) {
      if ((int)uStack_20 != iVar10) {
        auStackX_8[0] = 0;
        cVar5 = FUN_14be5bbf0(auStackX_8);
        if (cVar5 != '\0') {
          pcVar4 = (code *)swi(3);
          uVar8 = (*pcVar4)();
          return uVar8;
        }
      }
      if (plVar11 == plVar1) {
        uVar8 = 0;
        if (2 < DAT_14edc6208) {
          FUN_140f252a0(&DAT_14edc6208,&UNK_14d21b620,param_2,param_3);
          uVar8 = 0;
        }
        goto LAB_14830db9b;
      }
      lVar3 = *plVar11;
      if (((lVar3 != 0) && (*(char *)(lVar3 + 8) == param_2)) && (*(int *)(lVar3 + 0xc) == param_3))
      break;
      plVar11 = plVar11 + 1;
    }
    uVar2 = *(uint *)(lVar3 + 0x10);
    iVar10 = *(int *)(lVar3 + 0x14) - uVar2;
    if (iVar10 + 1 < 1) {
      uVar8 = (ulonglong)uVar2;
    }
    else {
      uVar6 = rand();
      iVar7 = (int)((float)(uVar6 & 0x7fff) * (float)(iVar10 + 1) * _DAT_14bf3cd14);
      if (iVar7 < iVar10) {
        iVar10 = iVar7;
      }
      uVar8 = (ulonglong)(iVar10 + uVar2);
    }
LAB_14830db9b:
    if (plStack_28 != (longlong *)0x0) {
      FUN_140e289f0();
    }
  }
  return uVar8;
}

