/* 1481d2dc0 ?Tick@UBeatSpawnerManager@@UEAAXM@Z */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _Tick_UBeatSpawnerManager__UEAAXM_Z(longlong param_1)

{
  uint *puVar1;
  double *pdVar2;
  double dVar3;
  double dVar4;
  longlong lVar5;
  code *pcVar6;
  char cVar7;
  uint uVar8;
  longlong lVar9;
  uint uVar10;
  double dVar11;
  undefined8 unaff_retaddr;
  
  lVar9 = (**(code **)(*(longlong *)(param_1 + -0x28) + 0x188))(param_1 + -0x28);
  if (((lVar9 == 0) || ((*(byte *)(lVar9 + 0x13d) & 0x40) != 0)) || (DAT_14eab53f9 != '\0')) {
    *(undefined1 *)(param_1 + 0xe0) = 0;
    return;
  }
  if ((*(char *)(param_1 + 0xe0) != '\0') && (*(int *)(param_1 + 200) != 0)) {
    dVar11 = (double)_GetMasterTimelinePosition_UBeatSpawnerManager__QEBANXZ(param_1 + -0x28);
    puVar1 = (uint *)(param_1 + 0xe8);
    if ((_DAT_14bce5180 < dVar11 - _DAT_14edbffe0) || (uVar10 = *puVar1, uVar10 != _DAT_14e9f1224))
    {
      uVar10 = *puVar1;
      lVar9 = (longlong)(int)uVar10;
      if ((int)uVar10 < *(int *)(param_1 + 200)) {
        uVar8 = 0;
        if ((int)uVar10 < *(int *)(param_1 + 200)) {
          uVar8 = ~uVar10 >> 0x1f;
        }
        if ((uVar8 == 0) &&
           (cVar7 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                        &UNK_14bce6ef0,lVar9,(longlong)*(int *)(param_1 + 200)),
           cVar7 != '\0')) {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        lVar5 = *(longlong *)(param_1 + 0xc0);
        dVar3 = *(double *)(lVar5 + lVar9 * 0x28);
        if ((((2 < DAT_14eab53c8) &&
             (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b938), 2 < DAT_14eab53c8)) &&
            (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b988,SUB84(dVar11,0)), 2 < DAT_14eab53c8))
           && (((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b9d0,*puVar1,
                                     *(undefined4 *)(param_1 + 200)), 2 < DAT_14eab53c8 &&
                (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7ba18,SUB84(dVar3 - dVar11,0)),
                2 < DAT_14eab53c8)) &&
               (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7ba88,
                                    (double)*(float *)(lVar5 + 0x24 + lVar9 * 0x28)),
               2 < DAT_14eab53c8)))) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7bae8,
                              *(undefined8 *)(lVar5 + 0x18 + lVar9 * 0x28));
        }
      }
      uVar10 = *puVar1;
      _DAT_14e9f1224 = uVar10;
      _DAT_14edbffe0 = dVar11;
    }
    dVar3 = _DAT_14bcefa10;
    if ((int)uVar10 < *(int *)(param_1 + 200)) {
      do {
        uVar8 = 0;
        if ((int)uVar10 < *(int *)(param_1 + 200)) {
          uVar8 = ~uVar10 >> 0x1f;
        }
        if ((uVar8 == 0) &&
           (cVar7 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                        &UNK_14bce6ef0,(longlong)(int)uVar10,
                                        (longlong)*(int *)(param_1 + 200)), cVar7 != '\0')) {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        if (dVar11 < *(double *)(*(longlong *)(param_1 + 0xc0) + (longlong)(int)uVar10 * 0x28)) {
          return;
        }
        lVar9 = (**(code **)(*(longlong *)(param_1 + -0x28) + 0x188))(param_1 + -0x28);
        if ((lVar9 == 0) || ((*(byte *)(lVar9 + 0x13d) & 0x40) != 0)) {
          *(undefined1 *)(param_1 + 0xe0) = 0;
          return;
        }
        uVar10 = *puVar1;
        uVar8 = 0;
        if ((int)uVar10 < *(int *)(param_1 + 200)) {
          uVar8 = ~uVar10 >> 0x1f;
        }
        if ((uVar8 == 0) &&
           (cVar7 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                        &UNK_14bce6ef0,(longlong)(int)uVar10,
                                        (longlong)*(int *)(param_1 + 200)), cVar7 != '\0')) {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        pdVar2 = (double *)(*(longlong *)(param_1 + 0xc0) + (longlong)(int)uVar10 * 0x28);
        dVar4 = *pdVar2;
        if (((1 < DAT_14eab53c8) &&
            (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7bb40), 1 < DAT_14eab53c8)) &&
           (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7bb90,*puVar1,
                                (double)*(float *)((longlong)pdVar2 + 0x24),pdVar2[3]),
           1 < DAT_14eab53c8)) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7bc10,*pdVar2,SUB84(dVar11,0),dVar11 - dVar4,
                              (dVar11 - dVar4) * dVar3);
        }
        if (*(float *)((longlong)pdVar2 + 0x24) < 0.0) {
          if (2 < DAT_14eab53c8) {
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7bd48,*puVar1,
                                (double)*(float *)((longlong)pdVar2 + 0x24));
          }
        }
        else {
          func_0x00014815f700(param_1 + 0x50,pdVar2);
          _CreateTestBeatWidget_UBeatSpawnerManager__AEAAXAEBUFBeatEvent___Z(param_1 + -0x28,pdVar2)
          ;
          if (2 < DAT_14eab53c8) {
            uVar10 = *(int *)(param_1 + 0xdc) - *(int *)(param_1 + 0xf0);
            if ((int)uVar10 < 0) {
              uVar10 = 0;
            }
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7bca8,*puVar1,uVar10);
          }
        }
        uVar10 = *puVar1 + 1;
        *puVar1 = uVar10;
      } while ((int)uVar10 < *(int *)(param_1 + 200));
    }
  }
  return;
}



