/* 1481d1c90 ?RebuildQueueFromCurrentState@UBeatSpawnerManager@@AEAAXAEBUFBeatPattern@@MH@Z */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _RebuildQueueFromCurrentState_UBeatSpawnerManager__AEAAXAEBUFBeatPattern__MH_Z
               (longlong param_1,longlong param_2,float param_3,uint param_4)

{
  undefined8 *puVar1;
  float fVar2;
  uint uVar3;
  double *pdVar4;
  ulonglong uVar5;
  code *pcVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  char cVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  ulonglong uVar14;
  int iVar15;
  longlong lVar16;
  int iVar17;
  ulonglong *puVar18;
  undefined8 unaff_retaddr;
  double dStack_b8;
  double dStack_b0;
  uint uStack_a8;
  undefined4 uStack_a4;
  double dStack_a0;
  int iStack_98;
  float fStack_94;
  
  uVar14 = (ulonglong)param_4;
  if (((*(char *)(param_1 + 0x108) == '\0') || (*(int *)(param_1 + 0xf0) == 0)) ||
     (*(int *)(param_2 + 0x18) == 0)) {
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf798f8);
    }
  }
  else {
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf799a0,*(undefined4 *)(param_1 + 0x110),uVar14,
                          (double)param_3,*(undefined8 *)(param_1 + 0x1a0));
    }
    dVar8 = (double)_GetMasterTimelinePosition_UBeatSpawnerManager__QEBANXZ(param_1);
    uVar3 = *(uint *)(param_1 + 0x110);
    uVar13 = 0;
    if ((-1 < (int)uVar3) && ((int)uVar3 < *(int *)(param_1 + 0xf0))) {
      uVar13 = 0;
      if ((int)uVar3 < *(int *)(param_1 + 0xf0)) {
        uVar13 = ~uVar3 >> 0x1f;
      }
      if ((uVar13 == 0) &&
         (cVar10 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                       &UNK_14bce6ef0,(longlong)(int)uVar3,
                                       (longlong)*(int *)(param_1 + 0xf0)), cVar10 != '\0')) {
        pcVar6 = (code *)swi(3);
        (*pcVar6)();
        return;
      }
      uVar13 = *(uint *)(*(longlong *)(param_1 + 0xe8) + 0x10 + (longlong)(int)uVar3 * 0x28);
    }
    puVar18 = (ulonglong *)(param_1 + 0xe8);
    iVar17 = *(int *)(param_1 + 0x110);
    iVar15 = *(int *)(param_1 + 0xf0) - iVar17;
    if (iVar15 != 0) {
      iVar11 = (*(int *)(param_1 + 0xf0) - iVar17) - iVar15;
      if (iVar11 != 0) {
        func_0x00014b89503a(*puVar18 + (longlong)iVar17 * 0x28,
                            *puVar18 + (longlong)*(int *)(param_1 + 0xf0) * 0x28,
                            (longlong)iVar11 * 0x28);
      }
      *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) - iVar15;
      func_0x0001481d21b0(puVar18);
    }
    uVar3 = _DAT_14bd17880;
    iVar17 = *(int *)(param_1 + 0x110);
    iVar15 = *(int *)(param_2 + 0x18);
    dVar8 = dVar8 + _DAT_14bd774b8;
    if (0 < (int)param_4) {
      dVar9 = _DAT_14bce5180 / (double)param_3;
      do {
        iVar17 = iVar17 + 1;
        if (((int)uVar13 < 0) || (*(int *)(param_2 + 0x18) <= (int)uVar13)) {
          if (1 < DAT_14eab53c8) {
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79aa8,uVar13,iVar15);
          }
          uVar13 = 0;
        }
        uVar12 = 0;
        if ((int)uVar13 < *(int *)(param_2 + 0x18)) {
          uVar12 = ~uVar13 >> 0x1f;
        }
        if ((uVar12 == 0) &&
           (cVar10 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                         &UNK_14bce6ef0,(longlong)(int)uVar13,
                                         (longlong)*(int *)(param_2 + 0x18)), cVar10 != '\0')) {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        fVar2 = *(float *)(*(longlong *)(param_2 + 0x10) + (longlong)(int)uVar13 * 4);
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79b58,(double)fVar2,uVar13);
        }
        pdVar4 = (double *)*puVar18;
        dStack_b0 = dVar8 + *(double *)(param_1 + 0x150);
        dVar7 = (double)(float)((uint)fVar2 & uVar3) * *(double *)(param_1 + 0x1a0) * dVar9;
        if (dVar7 <= *(double *)(param_1 + 0xe0)) {
          dVar7 = *(double *)(param_1 + 0xe0);
        }
        dStack_b8 = dVar8;
        uStack_a8 = uVar13;
        dStack_a0 = dVar7;
        iStack_98 = iVar17;
        fStack_94 = fVar2;
        if (((pdVar4 <= &dStack_b8) &&
            (&dStack_b8 < pdVar4 + (longlong)*(int *)(param_1 + 0xf4) * 5)) &&
           (cVar10 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                         &UNK_14bce6d80,&dStack_b8,pdVar4,
                                         (longlong)*(int *)(param_1 + 0xf4),
                                         (longlong)*(int *)(param_1 + 0xf0),0x28), cVar10 != '\0'))
        {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        iVar11 = *(int *)(param_1 + 0xf0);
        lVar16 = (longlong)iVar11;
        *(uint *)(param_1 + 0xf0) = iVar11 + 1U;
        if (*(uint *)(param_1 + 0xf4) < iVar11 + 1U) {
          func_0x0001481d2100(puVar18,iVar11);
        }
        uVar5 = *puVar18;
        dVar8 = dVar8 + dVar7;
        pdVar4 = (double *)(uVar5 + lVar16 * 0x28);
        *pdVar4 = dStack_b8;
        pdVar4[1] = dStack_b0;
        puVar1 = (undefined8 *)(uVar5 + 0x10 + lVar16 * 0x28);
        *puVar1 = CONCAT44(uStack_a4,uStack_a8);
        puVar1[1] = dStack_a0;
        *(ulonglong *)(uVar5 + 0x20 + lVar16 * 0x28) = CONCAT44(fStack_94,iStack_98);
        uVar13 = (int)(uVar13 + 1) % iVar15;
        uVar14 = uVar14 - 1;
      } while (uVar14 != 0);
    }
    *(float *)(param_1 + 0x10c) = param_3;
  }
  return;
}



