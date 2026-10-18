// Newer reference PDB symbol: LoadBeatmap_UMusicModeManager
// Address: 0x1482fdff0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matched newer-build PDB public symbol: LoadBeatmap_UMusicModeManager */

undefined8 FUN_1482fdff0(longlong param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  char cVar3;
  longlong *plVar4;
  longlong *plVar5;
  undefined8 uVar6;
  longlong lVar7;
  int iVar8;
  undefined *puVar9;
  undefined *puVar10;
  longlong lStack_e8;
  undefined8 uStack_e0;
  longlong alStack_d8 [12];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined8 uStack_68;
  longlong lStack_60;
  ulonglong uStack_58;
  longlong lStack_50;
  ulonglong uStack_48;
  longlong alStack_38 [2];
  
  alStack_d8[0] = 0;
  alStack_d8[1] = 0;
  puVar10 = &UNK_14bf24094;
  if (*(int *)(param_2 + 1) == 0) {
    puVar9 = &UNK_14bf24094;
  }
  else {
    puVar9 = (undefined *)*param_2;
  }
  cVar3 = FUN_141010f00(alStack_d8,puVar9,0,0);
  if (cVar3 == '\0') {
    if (1 < DAT_14edc6208) {
      if (*(int *)(param_2 + 1) != 0) {
        puVar10 = (undefined *)*param_2;
      }
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d20b6d0,puVar10);
    }
    uVar6 = 0;
  }
  else {
    FUN_140cf99e0(param_1 + 0x2d0,param_2);
    plVar4 = (longlong *)FUN_141072b80(alStack_38,param_2);
    plVar5 = (longlong *)(param_1 + 0x2c0);
    if (plVar5 != plVar4) {
      if (*plVar5 != 0) {
        FUN_140e289f0();
      }
      *plVar5 = *plVar4;
      *plVar4 = 0;
      *(int *)(param_1 + 0x2c8) = (int)plVar4[1];
      *(undefined4 *)(param_1 + 0x2cc) = *(undefined4 *)((longlong)plVar4 + 0xc);
      plVar4[1] = 0;
    }
    if (alStack_38[0] != 0) {
      FUN_140e289f0();
    }
    if (*(int *)(param_1 + 0x2e8) < 2) {
      FUN_148280a70(&lStack_e8);
      plVar5 = (longlong *)(param_1 + 0x2e0);
      if (plVar5 != &lStack_e8) {
        if (*plVar5 != 0) {
          FUN_140e289f0();
        }
        *plVar5 = lStack_e8;
        lStack_e8 = 0;
        *(undefined4 *)(param_1 + 0x2e8) = (undefined4)uStack_e0;
        *(undefined4 *)(param_1 + 0x2ec) = uStack_e0._4_4_;
        uStack_e0 = 0;
      }
      if (lStack_e8 != 0) {
        FUN_140e289f0();
      }
    }
    alStack_d8[2] = 0;
    alStack_d8[3] = 0;
    alStack_d8[4] = 0;
    alStack_d8[5] = 0;
    alStack_d8[6] = 0;
    alStack_d8[7] = 0;
    alStack_d8[8] = 0;
    alStack_d8[9] = 0;
    alStack_d8[10] = 0;
    alStack_d8[0xb] = 0;
    uStack_78 = _DAT_14d1a2040;
    uStack_74 = _UNK_14d1a2044;
    uStack_70 = _UNK_14d1a2048;
    uStack_6c = _UNK_14d1a204c;
    uStack_68 = 0;
    lStack_60 = 0;
    uStack_58 = 0;
    lStack_50 = 0;
    uStack_48 = 0;
    cVar3 = FUN_148302440(param_1,alStack_d8,alStack_d8 + 2);
    if (cVar3 == '\0') {
      if (1 < DAT_14edc6208) {
        if (*(int *)(param_2 + 1) != 0) {
          puVar10 = (undefined *)*param_2;
        }
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d20b758,puVar10);
      }
      uVar6 = 0;
    }
    else {
      puVar1 = (undefined8 *)(param_1 + 0x238);
      FUN_1481d1550(puVar1,alStack_d8 + 2);
      lVar2 = lStack_60;
      plVar5 = (longlong *)(param_1 + 0x2a0);
      if (plVar5 != &lStack_60) {
        iVar8 = (int)uStack_58;
        lVar7 = (longlong)(int)uStack_58;
        *(int *)(param_1 + 0x2a8) = (int)uStack_58;
        if (((int)uStack_58 == 0) && (*(int *)(param_1 + 0x2ac) == 0)) {
          *(undefined4 *)(param_1 + 0x2ac) = 0;
        }
        else {
          FUN_1481d3d50(plVar5,uStack_58 & 0xffffffff);
          if (iVar8 != 0) {
            func_0x00014ba120de(*plVar5,lVar2,lVar7 * 0x18);
          }
        }
      }
      plVar5 = (longlong *)(param_1 + 0x2b0);
      if (plVar5 != &lStack_50) {
        iVar8 = *(int *)(param_1 + 0x2b8);
        if (iVar8 != 0) {
          plVar4 = (longlong *)(*plVar5 + 0x10);
          do {
            if (*plVar4 != 0) {
              FUN_140e289f0();
            }
            plVar4 = plVar4 + 5;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
        FUN_1481cfc50(plVar5,lStack_50,uStack_48 & 0xffffffff,*(undefined4 *)(param_1 + 700));
      }
      *(undefined1 *)(param_1 + 0x2f0) = 1;
      FUN_1483075a0(param_1);
      FUN_148309cd0(param_1);
      if (4 < DAT_14edc6208) {
        if (*(int *)(param_1 + 0x260) == 0) {
          puVar9 = &UNK_14bf24094;
        }
        else {
          puVar9 = *(undefined **)(param_1 + 600);
        }
        if (*(int *)(param_1 + 0x240) != 0) {
          puVar10 = (undefined *)*puVar1;
        }
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d20b7f8,puVar10,puVar9,*(undefined4 *)(param_1 + 0x2a8),
                      *(undefined4 *)(param_1 + 0x2b8),*(undefined8 *)(param_1 + 0x288),
                      *(undefined8 *)(param_1 + 0x290));
      }
      FUN_1481d2890(param_1 + 0x188,puVar1);
      uVar6 = 1;
    }
    if ((int)uStack_48 != 0) {
      plVar5 = (longlong *)(lStack_50 + 0x10);
      iVar8 = (int)uStack_48;
      do {
        if (*plVar5 != 0) {
          FUN_140e289f0();
        }
        plVar5 = plVar5 + 5;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    if (lStack_50 != 0) {
      FUN_140e289f0();
    }
    if (lStack_60 != 0) {
      FUN_140e289f0();
    }
    if (alStack_d8[10] != 0) {
      FUN_140e289f0();
    }
    if (alStack_d8[8] != 0) {
      FUN_140e289f0();
    }
    if (alStack_d8[6] != 0) {
      FUN_140e289f0();
    }
    if (alStack_d8[4] != 0) {
      FUN_140e289f0();
    }
    if (alStack_d8[2] != 0) {
      FUN_140e289f0();
    }
  }
  if (alStack_d8[0] != 0) {
    FUN_140e289f0();
  }
  return uVar6;
}

