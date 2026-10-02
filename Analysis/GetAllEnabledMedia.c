/* 1481d4820 ?GetAllEnabledMedia@UCHPackStoreController@@QEAA?AV?$TArray@UFCHPackMediaEntry@@V?$TSizedDefaultAllocator@$0CA@@@@@XZ */

longlong *
_GetAllEnabledMedia_UCHPackStoreController__QEAA_AV__TArray_UFCHPackMediaEntry__V__TSizedDefaultAllocator__0CA_____XZ
          (longlong param_1,longlong *param_2)

{
  char *pcVar1;
  undefined8 *puVar2;
  int iVar3;
  undefined8 uVar4;
  code *pcVar5;
  char cVar6;
  longlong *plVar7;
  int iVar8;
  ulonglong uVar9;
  undefined4 *puVar10;
  longlong *plVar11;
  char *pcVar12;
  longlong lVar13;
  undefined8 *puVar14;
  undefined4 *puVar15;
  undefined *puVar16;
  int iVar17;
  undefined8 unaff_retaddr;
  undefined1 auStackX_18 [8];
  uint uStackX_20;
  longlong lStack_68;
  int iStack_60;
  longlong lStack_58;
  uint uStack_50;
  
  *param_2 = 0;
  param_2[1] = 0;
  _GetAllPackInfos_UCHPackStoreController__QEAA_AV__TArray_UFCHPackInfo__V__TSizedDefaultAllocator__0CA_____XZ
            (param_1,&lStack_58);
  uVar9 = (ulonglong)(int)uStack_50;
  uStackX_20 = uStack_50;
  lVar13 = uVar9 * 0x110;
  pcVar12 = (char *)(lStack_58 + 0x55);
  while( true ) {
    if (uStack_50 != (uint)uVar9) {
      auStackX_18[0] = 0;
      cVar6 = func_0x00014bc1d460(auStackX_18);
      if (cVar6 != '\0') {
        pcVar5 = (code *)swi(3);
        plVar7 = (longlong *)(*pcVar5)();
        return plVar7;
      }
    }
    pcVar1 = pcVar12 + -0x55;
    if (pcVar1 == (char *)(lVar13 + lStack_58)) break;
    if ((pcVar12[-1] == '\0') || (*pcVar12 == '\0')) {
      if (2 < DAT_14eab53c8) {
        if (*(int *)(pcVar12 + -0x4d) == 0) {
          puVar16 = &UNK_14bce4e94;
        }
        else {
          puVar16 = *(undefined **)pcVar1;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7df60,puVar16,pcVar12[-1],*pcVar12);
      }
      pcVar12 = pcVar12 + 0x110;
      uVar9 = (ulonglong)uStackX_20;
    }
    else {
      _GetManifestMedia_UCHPackManager__QEAA_AV__TArray_UFCHPackMediaEntry__V__TSizedDefaultAllocator__0CA_____AEBVFString___Z
                (*(undefined8 *)(param_1 + 0x40),&lStack_68,pcVar1);
      if (2 < DAT_14eab53c8) {
        if (*(int *)(pcVar12 + -0x4d) == 0) {
          puVar16 = &UNK_14bce4e94;
        }
        else {
          puVar16 = *(undefined **)pcVar1;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7dff0,iStack_60,puVar16);
      }
      if (param_2 == &lStack_68) {
        cVar6 = func_0x000140f8dfd0(&UNK_14bce9610,&UNK_14cf27ac0,0x799,unaff_retaddr,&UNK_14bce4e94
                                   );
        if (cVar6 != '\0') {
          pcVar5 = (code *)swi(3);
          plVar7 = (longlong *)(*pcVar5)();
          return plVar7;
        }
      }
      iVar17 = iStack_60;
      if (iStack_60 != 0) {
        iVar8 = (int)param_2[1] + iStack_60;
        if (iVar8 < 0) {
          func_0x000140d14f00();
          pcVar5 = (code *)swi(3);
          plVar7 = (longlong *)(*pcVar5)();
          return plVar7;
        }
        if (*(int *)((longlong)param_2 + 0xc) < iVar8) {
          func_0x000148193a50(param_2,iVar8);
        }
        puVar14 = (undefined8 *)((longlong)(int)param_2[1] * 0x40 + *param_2);
        puVar15 = (undefined4 *)(lStack_68 + 0x28);
        puVar10 = (undefined4 *)((longlong)puVar14 + 0x1c);
        iVar8 = iVar17;
        do {
          *puVar14 = 0;
          iVar3 = puVar15[-8];
          uVar4 = *(undefined8 *)(puVar15 + -10);
          puVar10[-5] = iVar3;
          if (iVar3 == 0) {
            puVar10[-4] = 0;
          }
          else {
            func_0x000140ca39a0(puVar14,iVar3,0);
            func_0x00014b89502e(*puVar14,uVar4,(longlong)iVar3 * 2);
          }
          puVar2 = (undefined8 *)(puVar10 + -3);
          *puVar2 = 0;
          iVar3 = puVar15[-4];
          uVar4 = *(undefined8 *)(puVar15 + -6);
          puVar10[-1] = iVar3;
          if (iVar3 == 0) {
            *puVar10 = 0;
          }
          else {
            func_0x000140ca39a0(puVar2,iVar3,0);
            func_0x00014b89502e(*puVar2,uVar4,(longlong)iVar3 * 2);
          }
          *(undefined8 *)(puVar10 + 1) = 0;
          func_0x000140c64610(puVar10 + 1,*(undefined8 *)(puVar15 + -2),*puVar15,0);
          puVar2 = (undefined8 *)(puVar10 + 5);
          *puVar2 = 0;
          iVar3 = puVar15[4];
          uVar4 = *(undefined8 *)(puVar15 + 2);
          puVar10[7] = iVar3;
          if (iVar3 == 0) {
            puVar10[8] = 0;
          }
          else {
            func_0x000140ca39a0(puVar2,iVar3,0);
            func_0x00014b89502e(*puVar2,uVar4);
          }
          puVar14 = puVar14 + 8;
          puVar10 = puVar10 + 0x10;
          puVar15 = puVar15 + 0x10;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        *(int *)(param_2 + 1) = (int)param_2[1] + iVar17;
      }
      if (iStack_60 != 0) {
        plVar7 = (longlong *)(lStack_68 + 0x20);
        iVar17 = iStack_60;
        do {
          if (plVar7[2] != 0) {
            func_0x000140e282f0();
          }
          plVar11 = (longlong *)*plVar7;
          for (iVar8 = (int)plVar7[1]; iVar8 != 0; iVar8 = iVar8 + -1) {
            if (*plVar11 != 0) {
              func_0x000140e282f0();
            }
            plVar11 = plVar11 + 2;
          }
          if (*plVar7 != 0) {
            func_0x000140e282f0();
          }
          if (plVar7[-2] != 0) {
            func_0x000140e282f0();
          }
          if (plVar7[-4] != 0) {
            func_0x000140e282f0();
          }
          plVar7 = plVar7 + 8;
          iVar17 = iVar17 + -1;
        } while (iVar17 != 0);
      }
      if (lStack_68 != 0) {
        func_0x000140e282f0();
      }
      pcVar12 = pcVar12 + 0x110;
      uVar9 = (ulonglong)uStackX_20;
    }
  }
  func_0x000148141b60(&lStack_58);
  return param_2;
}




/* Resolved referenced strings:
{
  "14cf27ac0": "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Array.h",
  "14bce9610": "(void*)this != (void*)&Source"
}
*/
