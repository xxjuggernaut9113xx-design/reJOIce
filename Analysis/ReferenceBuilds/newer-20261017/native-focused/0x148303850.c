// Newer reference PDB symbol: PausePlayback_UMusicModeManager
// Address: 0x148303850
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matched newer-build PDB public symbol: PausePlayback_UMusicModeManager */

void FUN_148303850(longlong param_1)

{
  longlong *plVar1;
  ulonglong *puVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  undefined8 uVar6;
  longlong lVar7;
  double dVar8;
  longlong lStackX_8;
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  char cStack_ac;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  longlong *plStack_90;
  longlong lStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined1 *puStack_68;
  undefined1 auStack_60 [16];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  longlong *plStack_40;
  
  if (*(char *)(param_1 + 0x568) == '\0') {
    return;
  }
  if (*(char *)(param_1 + 0x569) != '\0') {
    return;
  }
  uVar6 = FUN_1482e9b40();
  *(undefined8 *)(param_1 + 0x660) = uVar6;
  QueryPerformanceCounter(&lStackX_8);
  dVar8 = (double)lStackX_8 * _DAT_14ed8b438;
  *(undefined1 *)(param_1 + 0x569) = 1;
  dVar8 = dVar8 + _DAT_14bf2ec28;
  *(double *)(param_1 + 0x670) = dVar8;
  if ((((*(char *)(param_1 + 0x649) == '\0') || (*(char *)(param_1 + 0x648) != '\0')) ||
      (*(double *)(param_1 + 0x650) <= 0.0)) || (*(double *)(param_1 + 0x640) <= dVar8)) {
    if (*(longlong *)(param_1 + 0x498) != 0) {
      FUN_14670a680(*(longlong *)(param_1 + 0x498),1);
    }
  }
  else {
    dVar8 = *(double *)(param_1 + 0x640) - dVar8;
    if (dVar8 <= 0.0) {
      dVar8 = 0.0;
    }
    *(double *)(param_1 + 0x650) = dVar8;
    if (*(longlong *)(param_1 + 0x230) != 0) {
      uVar6 = func_0x000147a1ed70();
      lVar7 = FUN_14789e810(uVar6,param_1 + 0x658);
      if (lVar7 != 0) {
        FUN_1478cf910(uVar6,*(undefined8 *)(param_1 + 0x658));
      }
      *(undefined8 *)(param_1 + 0x658) = 0;
    }
  }
  if (*(longlong *)(param_1 + 0x4b0) != 0) {
    FUN_148320060();
  }
  if (DAT_14edc6208 < 5) {
    return;
  }
  if (*_UNK_14d20e770 == '\0') {
    FUN_140f55110();
  }
  if (DAT_14ed9a290 != '\0') {
    puStack_68 = &stack0x00000018;
    FUN_140f62430(&uStack_50,&UNK_14d20e758);
    cStack_ac = 5;
    uStack_b8 = 0;
    uStack_b4 = 0;
    puStack_c8 = (undefined *)0x0;
    uStack_c0 = 0;
    uStack_b0 = 0;
    uStack_a8 = 0;
    FUN_1410b69f0(&uStack_a0);
    plStack_90 = (longlong *)0x0;
    puStack_c8 = &UNK_14bf87cb8;
    lStack_88 = 0;
    uStack_80 = 0;
    uStack_78 = 0;
    lVar7 = _DAT_14ed9a720;
    if (_DAT_14ed9a720 == 0) {
      lVar7 = FUN_140f2f7b0(&DAT_14ed9a720);
    }
    plVar5 = plStack_90;
    plStack_90 = plStack_40;
    uStack_a0 = uStack_50;
    uStack_9c = uStack_4c;
    uStack_98 = uStack_48;
    uStack_94 = uStack_44;
    lStack_88 = lVar7;
    if (plVar5 != (longlong *)0x0) {
      LOCK();
      plVar1 = plVar5 + 3;
      lVar7 = *plVar1;
      *plVar1 = *plVar1 + -1;
      UNLOCK();
      if (((uint)lVar7 & 0x3fffffff) == 1) {
        (**(code **)(*plVar5 + 0x10))(plVar5);
        plVar5[1] = 0;
        plVar5[2] = 0;
        LOCK();
        puVar2 = (ulonglong *)(plVar5 + 3);
        uVar3 = *puVar2;
        *puVar2 = *puVar2 - 0x40000000;
        UNLOCK();
        if (((uint)(uVar3 >> 0x1e) & 0x3fffffff) == 1) {
          (**(code **)*plVar5)(plVar5,1);
        }
      }
    }
    uStack_c0 = _UNK_14d20e760;
    uStack_b8 = _UNK_14d20e768;
    uStack_b4 = (undefined4)uRam000000014edc620c;
    uStack_b0 = (undefined4)((ulonglong)uRam000000014edc620c >> 0x20);
    cStack_ac = UNK_14d20e76c;
    puVar4 = (undefined8 *)FUN_14102a5b0(auStack_60);
    uStack_a8 = *puVar4;
    if ((((UNK_14d20e76c != '\x02') && (UNK_14d20e76c != '\x03')) &&
        ((UNK_14d20e76c != '\x04' && (UNK_14d20e76c != '@')))) ||
       (plVar5 = _DAT_14edbbaf0, _DAT_14edbbaf0 == (longlong *)0x0)) {
      plVar5 = (longlong *)FUN_141008de0();
    }
    (**(code **)(*plVar5 + 0x18))(plVar5,&puStack_c8);
    plVar5 = plStack_90;
    if (plStack_90 != (longlong *)0x0) {
      LOCK();
      plVar1 = plStack_90 + 3;
      lVar7 = *plVar1;
      *plVar1 = *plVar1 + -1;
      UNLOCK();
      if (((uint)lVar7 & 0x3fffffff) == 1) {
        (**(code **)(*plStack_90 + 0x10))(plStack_90);
        plVar5[1] = 0;
        plVar5[2] = 0;
        LOCK();
        puVar2 = (ulonglong *)(plVar5 + 3);
        uVar3 = *puVar2;
        *puVar2 = *puVar2 - 0x40000000;
        UNLOCK();
        if (((uint)(uVar3 >> 0x1e) & 0x3fffffff) == 1) {
          (**(code **)*plVar5)(plVar5,1);
        }
      }
    }
    return;
  }
  if (-1 < *(int *)(_DAT_14ec274a0 + 0x18)) {
    FUN_140f25530(&UNK_14d20e758,_UNK_14d20e758,&stack0x00000018);
  }
  FUN_140f4d420(_UNK_14d20e760,_UNK_14d20e768,0x14edc620c,UNK_14d20e76c,_UNK_14d20e758,
                &stack0x00000018);
  return;
}

