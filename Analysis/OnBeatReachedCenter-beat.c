/* 1481d15e0 ?OnBeatReachedCenter@UBeatSpawnerManager@@QEAAXAEBUFBeatEvent@@@Z */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _OnBeatReachedCenter_UBeatSpawnerManager__QEAAXAEBUFBeatEvent___Z
               (longlong *param_1,longlong param_2)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  undefined8 uVar4;
  undefined **ppuVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  int iVar9;
  undefined *puVar10;
  undefined1 auStack_168 [32];
  undefined1 uStack_148;
  undefined4 uStack_140;
  longlong *plStack_138;
  undefined8 uStack_130;
  undefined8 auStack_128 [2];
  undefined8 *puStack_118;
  int iStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  longlong alStack_e8 [2];
  undefined **ppuStack_d8;
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined *puStack_a8;
  undefined8 *puStack_a0;
  longlong lStack_98;
  undefined **ppuStack_88;
  undefined *puStack_78;
  undefined8 uStack_70;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined *puStack_58;
  undefined8 *puStack_50;
  ulonglong uStack_48;
  
  uStack_48 = _DAT_14ea60b28 ^ (ulonglong)auStack_168;
  if ((char)param_1[0x21] == '\0') {
    if ((1 < DAT_14eab53c8) &&
       (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79f00,*(undefined4 *)(param_2 + 0x20)),
       1 < DAT_14eab53c8)) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79fd8);
    }
  }
  else {
    lVar3 = (**(code **)(*param_1 + 0x188))();
    if ((lVar3 == 0) || ((*(byte *)(lVar3 + 0x13d) & 0x40) != 0)) {
      if (2 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a080);
      }
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
    else {
      if (1 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a130,*(undefined4 *)(param_2 + 0x20));
      }
      if ((param_1[0xd] != 0) && ((*(uint *)(param_1[0xd] + 8) & 0x60000000) == 0)) {
        _SyncToBeat_UMediaPlaybackController__QEAAXNNN_Z
                  (param_1[0xd],(int)*(undefined8 *)(param_2 + 0x18),*(undefined8 *)(param_2 + 8),0)
        ;
      }
      func_0x00014815f740(param_1 + 0x12,param_2);
      if (1 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a1d0,*(undefined4 *)(param_2 + 0x20),
                            *(undefined8 *)(param_2 + 0x18));
      }
      *(int *)(param_1 + 0x23) = (int)param_1[0x23] + 1;
      if (((((2 < DAT_14eab53c8) &&
            (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a260), 2 < DAT_14eab53c8)) &&
           (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a2b0,*(undefined4 *)(param_2 + 0x20)),
           2 < DAT_14eab53c8)) &&
          ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a308,(int)param_1[0x23]), 2 < DAT_14eab53c8
           && (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a380,
                                   *(undefined4 *)((longlong)param_1 + 0x104)), 2 < DAT_14eab53c8)))
          ) && (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a3a0,(int)param_1[0x22]),
               2 < DAT_14eab53c8)) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a3c0,(int)param_1[0x1e]);
      }
      iVar1 = (int)param_1[0x22];
      uStack_130 = CONCAT44(uStack_130._4_4_,(int)param_1[0x23]);
      iVar6 = iVar1 - (int)param_1[0x23];
      iVar2 = (int)param_1[0x1e];
      iVar8 = iVar2 - iVar1;
      iVar9 = *(int *)((longlong)param_1 + 0x104);
      plStack_138 = (longlong *)CONCAT44(plStack_138._4_4_,iVar9);
      if (((1 < DAT_14eab53c8) &&
          (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a3e0), 1 < DAT_14eab53c8)) &&
         ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a458,iVar6), 1 < DAT_14eab53c8 &&
          (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a4a0,iVar8), 1 < DAT_14eab53c8)))) {
        puVar10 = &UNK_14ca022f0;
        puVar7 = &UNK_14ca022f0;
        if ((int)plStack_138 <= (int)uStack_130) {
          puVar7 = &UNK_14ca022e8;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a4f0,puVar7);
        if (1 < DAT_14eab53c8) {
          puVar7 = &UNK_14ca022f0;
          if (iVar2 <= iVar1) {
            puVar7 = &UNK_14ca022e8;
          }
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a548,puVar7);
          if (1 < DAT_14eab53c8) {
            if (iVar6 < 1) {
              puVar10 = &UNK_14ca022e8;
            }
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a590,puVar10);
          }
        }
        iVar9 = (int)plStack_138;
      }
      if ((((int)uStack_130 < iVar9) || (iVar1 < iVar2)) || (0 < iVar6)) {
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a868);
        }
        if ((0 < iVar6) && (2 < DAT_14eab53c8)) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a900,iVar6);
        }
        if ((0 < iVar8) && (2 < DAT_14eab53c8)) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a978,iVar8);
        }
      }
      else {
        if ((1 < DAT_14eab53c8) &&
           (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a5e0,*(undefined4 *)(param_2 + 0x20)),
           1 < DAT_14eab53c8)) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a6a0);
        }
        lVar3 = (**(code **)(*param_1 + 0x188))(param_1);
        if ((lVar3 == 0) || ((*(byte *)(lVar3 + 0x13d) & 0x40) != 0)) {
          if (2 < DAT_14eab53c8) {
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a7d8);
          }
          _StopSequence_UBeatSpawnerManager__QEAAXXZ(param_1);
        }
        else {
          uStack_130 = 0;
          auStack_128[0] = 0;
          func_0x00014190e290(auStack_128,param_1);
          uVar4 = func_0x000147a1e670(lVar3);
          uStack_70 = auStack_128[0];
          puStack_78 = &UNK_14cf7c0b0;
          lStack_98 = 0x1481d0bc0;
          puStack_58 = &UNK_14cf7c068;
          puStack_a0 = &uStack_70;
          puStack_118 = (undefined8 *)0x0;
          iStack_110 = 0;
          uStack_108 = 0;
          uStack_100 = 0;
          uStack_f8 = 0;
          plStack_138 = alStack_e8;
          alStack_e8[0] = 0x1481d0bc0;
          ppuStack_d8 = (undefined **)0x0;
          ppuStack_88 = (undefined **)0x0;
          puStack_c8 = &UNK_14cf7c0b0;
          uStack_c0 = auStack_128[0];
          uStack_b8 = uStack_68;
          uStack_b4 = uStack_64;
          uStack_b0 = uStack_60;
          uStack_ac = uStack_5c;
          puStack_a8 = &UNK_14cf7c068;
          puStack_50 = puStack_a0;
          puStack_a0 = (undefined8 *)(*_DAT_14cf7c0b8)(&puStack_c8);
          lStack_98 = 0;
          uStack_140 = _DAT_14bd17874;
          uStack_148 = 0;
          func_0x0001478cf760(uVar4,&uStack_130,&puStack_118,_DAT_14bf058dc);
          if (alStack_e8[0] != 0) {
            ppuVar5 = &puStack_c8;
            if (ppuStack_d8 != (undefined **)0x0) {
              ppuVar5 = ppuStack_d8;
            }
            (**(code **)(*ppuVar5 + 0x10))();
          }
          puStack_a8 = &UNK_14d3ac0f0;
          func_0x000140c70210(&uStack_108);
          if ((iStack_110 != 0) && (puStack_118 != (undefined8 *)0x0)) {
            (**(code **)*puStack_118)(puStack_118,0);
            func_0x000140d20c70(&puStack_118,0,0,0x10);
            iStack_110 = 0;
          }
          if (puStack_118 != (undefined8 *)0x0) {
            func_0x000140e282f0();
          }
          if (lStack_98 != 0) {
            ppuVar5 = &puStack_78;
            if (ppuStack_88 != (undefined **)0x0) {
              ppuVar5 = ppuStack_88;
            }
            (**(code **)(*ppuVar5 + 0x10))();
          }
        }
      }
      if (1 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7a9f8,*(undefined4 *)(param_2 + 0x20));
      }
    }
  }
  func_0x00014b880380(uStack_48 ^ (ulonglong)auStack_168);
  return;
}



