// Newer reference PDB symbol: ScheduleDeferredAudioStart_UMusicModeManager
// Address: 0x14830f660
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matched newer-build PDB public symbol: ScheduleDeferredAudioStart_UMusicModeManager */

void FUN_14830f660(longlong param_1,double param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  longlong lVar3;
  undefined **ppuVar4;
  undefined1 auStack_148 [32];
  undefined1 uStack_128;
  undefined4 uStack_120;
  undefined8 uStack_118;
  code **ppcStack_110;
  undefined8 *puStack_108;
  int iStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  code *apcStack_d8 [2];
  undefined **ppuStack_c8;
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined *puStack_98;
  undefined8 *puStack_90;
  code *pcStack_88;
  undefined **ppuStack_78;
  undefined *puStack_68;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined *puStack_48;
  undefined8 *puStack_40;
  ulonglong uStack_38;
  
  uStack_38 = _DAT_14ed716f8 ^ (ulonglong)auStack_148;
  if (*(longlong *)(param_1 + 0x230) != 0) {
    uVar2 = func_0x000147a1ed70();
    puVar1 = (undefined8 *)(param_1 + 0x658);
    lVar3 = FUN_14789e810(uVar2,puVar1);
    if (lVar3 != 0) {
      FUN_1478cf910(uVar2,*puVar1);
    }
    *puVar1 = 0;
    if (0.0 < param_2) {
      uStack_118 = 0;
      FUN_14190e990(&uStack_118,param_1);
      uVar2 = func_0x000147a1ed70(*(undefined8 *)(param_1 + 0x230));
      uStack_60 = uStack_118;
      puStack_68 = &UNK_14d21cb80;
      pcStack_88 = FUN_1482d9410;
      puStack_48 = &UNK_14d21ca28;
      puStack_90 = &uStack_60;
      puStack_108 = (undefined8 *)0x0;
      iStack_100 = 0;
      uStack_f8 = 0;
      uStack_f0 = 0;
      uStack_e8 = 0;
      ppcStack_110 = apcStack_d8;
      apcStack_d8[0] = FUN_1482d9410;
      ppuStack_c8 = (undefined **)0x0;
      ppuStack_78 = (undefined **)0x0;
      puStack_b8 = &UNK_14d21cb80;
      uStack_b0 = uStack_118;
      uStack_a8 = uStack_58;
      uStack_a4 = uStack_54;
      uStack_a0 = uStack_50;
      uStack_9c = uStack_4c;
      puStack_98 = &UNK_14d21ca28;
      puStack_40 = puStack_90;
      puStack_90 = (undefined8 *)(*_DAT_14d21cb88)(&puStack_b8);
      pcStack_88 = (code *)0x0;
      uStack_120 = _DAT_14bf56a74;
      uStack_128 = 0;
      FUN_1478cfe60(uVar2,puVar1,&puStack_108,(float)param_2);
      if (apcStack_d8[0] != (code *)0x0) {
        ppuVar4 = &puStack_b8;
        if (ppuStack_c8 != (undefined **)0x0) {
          ppuVar4 = ppuStack_c8;
        }
        (**(code **)(*ppuVar4 + 0x10))();
      }
      puStack_98 = &UNK_14d6484c0;
      FUN_140c70910(&uStack_f8);
      if ((iStack_100 != 0) && (puStack_108 != (undefined8 *)0x0)) {
        (**(code **)*puStack_108)(puStack_108,0);
        FUN_140d21370(&puStack_108,0,0,0x10);
        iStack_100 = 0;
      }
      if (puStack_108 != (undefined8 *)0x0) {
        FUN_140e289f0();
      }
      if (pcStack_88 != (code *)0x0) {
        ppuVar4 = &puStack_68;
        if (ppuStack_78 != (undefined **)0x0) {
          ppuVar4 = ppuStack_78;
        }
        (**(code **)(*ppuVar4 + 0x10))();
      }
      goto LAB_14830f85b;
    }
  }
  FUN_1482d5610(param_1);
LAB_14830f85b:
  FUN_14b9fb8d0(uStack_38 ^ (ulonglong)auStack_148);
  return;
}

