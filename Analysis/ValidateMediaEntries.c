/* 1481953c0 ?ValidateMediaEntries@UCHPackManager@@SA?AV?$TArray@UFCHPackMediaEntry@@V?$TSizedDefaultAllocator@$0CA@@@@@AEBV2@@Z */

ulonglong *
_ValidateMediaEntries_UCHPackManager__SA_AV__TArray_UFCHPackMediaEntry__V__TSizedDefaultAllocator__0CA_____AEBV2__Z
          (ulonglong *param_1,ulonglong *param_2)

{
  int iVar1;
  ulonglong uVar2;
  code *pcVar3;
  ulonglong uVar4;
  char cVar5;
  ulonglong *puVar6;
  longlong *plVar7;
  ulonglong uVar8;
  int *piVar9;
  undefined *puVar10;
  int iVar11;
  ulonglong uVar12;
  undefined8 unaff_retaddr;
  undefined1 auStackX_10 [8];
  undefined4 uVar13;
  
  iVar11 = 0;
  *param_1 = 0;
  param_1[1] = 0;
  uVar13 = 1;
  uVar8 = *param_2;
  uVar4 = param_2[1];
  uVar12 = (longlong)(int)uVar4 * 0x40 + uVar8;
  piVar9 = (int *)(uVar8 + 0x38);
LAB_148195412:
  do {
    if ((int)param_2[1] != (int)uVar4) {
      auStackX_10[0] = 0;
      cVar5 = func_0x00014bc1ce50(auStackX_10);
      if (cVar5 != '\0') {
        pcVar3 = (code *)swi(3);
        puVar6 = (ulonglong *)(*pcVar3)();
        return puVar6;
      }
    }
    if (uVar8 == uVar12) {
      if ((0 < iVar11) && (2 < DAT_14eab53c8)) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf63418,iVar11,(int)param_1[1]);
      }
      return param_1;
    }
    if (1 < *piVar9) {
      plVar7 = (longlong *)func_0x000140db7220();
      if (*piVar9 == 0) {
        puVar10 = &UNK_14bce4e94;
      }
      else {
        puVar10 = *(undefined **)(piVar9 + -2);
      }
      cVar5 = (**(code **)(*plVar7 + 0x50))(plVar7,puVar10);
      if (cVar5 != '\0') {
        uVar2 = *param_1;
        if ((uVar2 <= uVar8) && (uVar8 < (longlong)*(int *)((longlong)param_1 + 0xc) * 0x40 + uVar2)
           ) {
          cVar5 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                      &UNK_14bce6d80,uVar8,uVar2,
                                      (longlong)*(int *)((longlong)param_1 + 0xc),
                                      (longlong)(int)param_1[1],0x40,uVar13);
          if (cVar5 != '\0') {
            pcVar3 = (code *)swi(3);
            puVar6 = (ulonglong *)(*pcVar3)();
            return puVar6;
          }
        }
        iVar1 = (int)param_1[1];
        *(uint *)(param_1 + 1) = iVar1 + 1U;
        if (*(uint *)((longlong)param_1 + 0xc) < iVar1 + 1U) {
          func_0x0001481939b0(param_1,iVar1);
        }
        func_0x00014818c660((longlong)iVar1 * 0x40 + *param_1,uVar8);
        uVar8 = uVar8 + 0x40;
        piVar9 = piVar9 + 0x10;
        goto LAB_148195412;
      }
    }
    iVar11 = iVar11 + 1;
    if (2 < DAT_14eab53c8) {
      if (*piVar9 == 0) {
        puVar10 = &UNK_14bce4e94;
      }
      else {
        puVar10 = *(undefined **)(piVar9 + -2);
      }
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf63398,puVar10);
    }
    uVar8 = uVar8 + 0x40;
    piVar9 = piVar9 + 0x10;
  } while( true );
}




/* Resolved referenced strings:
{
  "14cf27ac0": "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Array.h",
  "14bce6eb8": "Addr < GetData() || Addr >= (GetData() + ArrayMax)",
  "14bce6d80": "Attempting to use a container element (%p) which already comes from the container being modified (%p, ArrayMax: %lld, ArrayNum: %lld, SizeofElement: %d)!"
}
*/
