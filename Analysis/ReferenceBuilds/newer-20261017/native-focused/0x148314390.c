// Newer reference PDB symbol: StartPlayback_UMusicModeManager
// Address: 0x148314390
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matched newer-build PDB public symbol: StartPlayback_UMusicModeManager */

void FUN_148314390(longlong *param_1,longlong param_2,longlong param_3,longlong param_4,
                  longlong param_5,undefined1 param_6)

{
  int iVar1;
  code *pcVar2;
  undefined1 auVar3 [16];
  double dVar4;
  longlong lVar5;
  char cVar6;
  longlong lVar7;
  longlong lVar8;
  undefined *puVar9;
  longlong lVar10;
  undefined8 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined8 unaff_retaddr;
  undefined1 auStackX_8 [8];
  ulonglong in_stack_fffffffffffffeb8;
  code *pcStack_128;
  ulonglong uStack_120;
  longlong *plStack_118;
  longlong lStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  int iStack_e0;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  float fStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  longlong lStack_c0;
  int iStack_b8;
  undefined4 uStack_b4;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined4 uStack_a0;
  undefined1 uStack_9c;
  longlong lStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined8 uStack_80;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined1 auStack_68 [24];
  undefined1 uStack_50;
  
  if ((char)param_1[0x5e] == '\0') {
    if (DAT_14edc6208 < 2) {
      return;
    }
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d20df60);
    return;
  }
  if (param_1[0x46] == 0) {
    lVar7 = (**(code **)(*param_1 + 0x188))();
    param_1[0x46] = lVar7;
  }
  if (param_1[0x46] == 0) {
    if (DAT_14edc6208 < 2) {
      return;
    }
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d20e000);
    return;
  }
  if (param_2 == 0) {
    if (DAT_14edc6208 < 2) {
      return;
    }
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d20e118);
    return;
  }
  param_1[0x96] = param_2;
  param_1[0x97] = param_3;
  param_1[0x98] = param_4;
  param_1[0xd8] = param_5;
  *(undefined1 *)((longlong)param_1 + 0x56b) = param_6;
  param_1[0x99] = param_2;
  param_1[0x9a] = param_3;
  param_1[0x9b] = param_4;
  param_1[0x9c] = param_5;
  *(undefined1 *)(param_1 + 0x9d) = param_6;
  if (*(char *)((longlong)param_1 + 0x4e9) != '\0') {
    if ((int)param_1[0x9e] < 1) {
      *(undefined4 *)(param_1 + 0x9e) = 1;
    }
    *(undefined1 *)((longlong)param_1 + 0x4ea) = 0;
    if (1 < (int)param_1[0x5b]) {
      FUN_140d392c0(param_1 + 0xa3,auStackX_8,param_1 + 0x5a,0);
    }
    iVar1 = (int)param_1[0x9e];
    if ((((*(char *)((longlong)param_1 + 0x4e9) == '\0') ||
         (*(char *)((longlong)param_1 + 0x4eb) != '\0')) || (iVar1 < 1)) ||
       (iVar1 < *(int *)((longlong)param_1 + 0x4ec))) {
      uVar11 = 0;
    }
    else {
      uVar11 = 1;
    }
    FUN_1481d2de0(param_1 + 0x34,iVar1,uVar11);
  }
  if (param_1[0x98] != 0) {
    *(undefined1 *)(param_1[0x98] + 0x4c) = 1;
    FUN_1482a3a00(param_1[0x98]);
  }
  param_1[0xd6] = 0;
  *(undefined4 *)(param_1 + 0xdf) = 0;
  FUN_148309cd0(param_1);
  lStack_110 = 0;
  uStack_108 = 0;
  FUN_140cf9980(param_1 + 0xdb,&lStack_110);
  if (lStack_110 != 0) {
    FUN_140e289f0();
  }
  pcStack_128 = (code *)0x0;
  uStack_120 = 0;
  FUN_140cf9980(param_1 + 0xdd,&pcStack_128);
  if (pcStack_128 != (code *)0x0) {
    FUN_140e289f0();
  }
  param_1[0xcc] = 0;
  param_1[0xcd] = 0;
  param_1[0xcf] = 0;
  param_1[0xd0] = 0;
  *(undefined4 *)(param_1 + 0xd1) = 0;
  *(undefined1 *)((longlong)param_1 + 0x68c) = 0;
  *(undefined2 *)(param_1 + 0xc9) = 0;
  param_1[0xca] = 0;
  param_1[200] = 0;
  param_1[0xd9] = 0;
  if ((param_1[0x97] != 0) && (cVar6 = func_0x000148283d80(), cVar6 != '\0')) {
    lVar7 = param_1[0x97];
    uStack_d8 = *(undefined4 *)(lVar7 + 800);
    uStack_d4 = *(undefined4 *)(lVar7 + 0x324);
    fStack_d0 = *(float *)(lVar7 + 0x328);
    uStack_cc = *(undefined4 *)(lVar7 + 0x32c);
    uStack_c8 = *(undefined4 *)(lVar7 + 0x330);
    plStack_118 = &lStack_c0;
    lStack_c0 = 0;
    iStack_b8 = *(int *)(lVar7 + 0x340);
    lVar10 = (longlong)iStack_b8;
    uVar11 = *(undefined8 *)(lVar7 + 0x338);
    if (iStack_b8 == 0) {
      uStack_b4 = 0;
    }
    else {
      FUN_140ca40a0(&lStack_c0,iStack_b8,0);
      func_0x00014ba120de(lStack_c0,uVar11,lVar10 * 2);
    }
    uStack_b0 = *(undefined8 *)(lVar7 + 0x348);
    uStack_a8 = *(undefined1 *)(lVar7 + 0x350);
    dVar4 = (double)fStack_d0 * _DAT_14bf3cd30;
    param_1[0xd9] = (longlong)dVar4;
    if (4 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d20e1d0,(double)fStack_d0,dVar4);
    }
    if (lStack_c0 != 0) {
      FUN_140e289f0();
    }
  }
  FUN_1482483f0(&puStack_e8,param_1 + 0x58,param_1 + 0x4f);
  lVar7 = FUN_1482fd4e0(param_1,&puStack_e8);
  param_1[0x94] = lVar7;
  if (lVar7 == 0) {
    if (1 < DAT_14edc6208) {
      puVar9 = &UNK_14bf24094;
      if (iStack_e0 != 0) {
        puVar9 = puStack_e8;
      }
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d20e260,puVar9);
    }
    goto LAB_148314ae1;
  }
  lVar7 = FUN_1482caaf0(param_1[0x46]);
  if (lVar7 == 0) {
    if (1 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d20e2d8);
    }
    goto LAB_148314ae1;
  }
  lStack_98 = 0;
  uStack_90 = 0;
  uStack_88 = 0;
  uStack_a0 = 4;
  uStack_9c = 1;
  FUN_146166e20(auStack_68,&uStack_a0);
  uStack_50 = uStack_88;
  in_stack_fffffffffffffeb8 = in_stack_fffffffffffffeb8 & 0xffffffffffffff00;
  lVar7 = FUN_145d5a640(lVar7,param_1[0x46],param_1[0x91],auStack_68,in_stack_fffffffffffffeb8,1);
  param_1[0x92] = lVar7;
  if (lVar7 == 0) {
    if (1 < DAT_14edc6208) {
      puVar9 = &UNK_14d20e368;
LAB_148314ac5:
      FUN_140f252a0(&DAT_14edc6208,puVar9);
    }
  }
  else {
    lVar7 = FUN_146a99fa0(param_1[0x46],param_1[0x94],(int)param_1[0x95],_DAT_14bf2ebec,
                          in_stack_fffffffffffffeb8 & 0xffffffff00000000,0,0,0);
    param_1[0x93] = lVar7;
    if (lVar7 == 0) {
      if (1 < DAT_14edc6208) {
        puVar9 = &UNK_14d20e4a0;
        goto LAB_148314ac5;
      }
    }
    else {
      lVar8 = func_0x00014ba1210e(&UNK_14d20e610,&UNK_14bfe8f4c);
      lVar10 = 0;
      while (lVar5 = lVar8, lVar5 != 0) {
        lVar8 = func_0x00014ba1210e(lVar5 + 2,&UNK_14bfe8f4c);
        lVar10 = lVar5;
      }
      if (((lVar10 == 0) || (*(short *)(lVar10 + 4) == 0x30)) &&
         (cVar6 = FUN_140f8e6d0(&UNK_14c81bb48,&UNK_14d1d2510,0x1da,unaff_retaddr,&UNK_14c81baf0,
                                &UNK_14d20e610), cVar6 != '\0')) {
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      FUN_1411a8280(&uStack_80,lVar10 + 4,1);
      pcStack_128 = FUN_1483020e0;
      uStack_6c = (undefined4)(uStack_120 >> 0x20);
      uStack_120 = uStack_120 & 0xffffffff00000000;
      uStack_100 = 0;
      uStack_f8 = 0;
      uStack_f0 = 0;
      uStack_78 = 0x483020e0;
      uStack_74 = 1;
      uStack_70 = 0;
      FUN_1482cd850(&uStack_100,param_1,&uStack_78,uStack_80);
      FUN_145f15ce0(lVar7 + 0xba0,&uStack_100);
      FUN_140c70910(&uStack_100);
      dVar4 = (double)param_1[8];
      uVar12 = SUB84(dVar4,0);
      uVar13 = (undefined4)((ulonglong)dVar4 >> 0x20);
      if (dVar4 <= 0.0) {
        uVar12 = 0;
        uVar13 = 0;
      }
      QueryPerformanceCounter(&plStack_118);
      dVar4 = (double)(longlong)plStack_118 * _DAT_14ed8b438 + _DAT_14bf2ec28 +
              (double)CONCAT44(uVar13,uVar12);
      auVar3._8_4_ = SUB84(dVar4,0);
      auVar3._0_8_ = dVar4;
      auVar3._12_4_ = (int)((ulonglong)dVar4 >> 0x20);
      *(undefined1 (*) [16])(param_1 + 199) = auVar3;
      *(undefined1 *)(param_1 + 0xc9) = 0;
      *(bool *)((longlong)param_1 + 0x649) =
           0.0 <= (double)CONCAT44(uVar13,uVar12) && (double)CONCAT44(uVar13,uVar12) != 0.0;
      param_1[0xca] = CONCAT44(uVar13,uVar12);
      FUN_148309be0(param_1);
      func_0x000148309c70(param_1);
      if (4 < DAT_14edc6208) {
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d20e3f8,CONCAT44(uVar13,uVar12));
      }
      if (param_1[0x98] == 0) {
        FUN_148321290(param_1[0x96],param_1,(int)param_1[0xd8]);
      }
      else {
        FUN_1483213f0();
      }
      *(undefined2 *)(param_1 + 0xad) = 1;
      FUN_14830f660(param_1,param_1[0xca]);
      if (4 < DAT_14edc6208) {
        if ((int)param_1[0x48] == 0) {
          puVar9 = &UNK_14bf24094;
        }
        else {
          puVar9 = (undefined *)param_1[0x47];
        }
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d20e528,puVar9,param_1[0x52],param_1[0x51],param_1[0xd8]
                     );
      }
    }
  }
  if (lStack_98 != 0) {
    FUN_140e289f0();
  }
LAB_148314ae1:
  if (puStack_e8 != (undefined *)0x0) {
    FUN_140e289f0();
  }
  return;
}

