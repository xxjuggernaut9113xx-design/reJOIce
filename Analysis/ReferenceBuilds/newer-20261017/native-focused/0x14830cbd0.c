// Newer reference PDB symbol: ResumePlayback_UMusicModeManager
// Address: 0x14830cbd0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matched newer-build PDB public symbol: ResumePlayback_UMusicModeManager */

void FUN_14830cbd0(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  longlong *plVar1;
  ulonglong *puVar2;
  ulonglong uVar3;
  char cVar4;
  undefined1 auVar5 [16];
  longlong lVar6;
  undefined8 *puVar7;
  longlong *plVar8;
  double dVar9;
  longlong lStackX_8;
  undefined8 *puStackX_10;
  undefined8 uStackX_18;
  undefined8 uStackX_20;
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined1 uStack_ac;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  longlong *plStack_90;
  longlong lStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 *puStack_68;
  undefined1 auStack_60 [16];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  longlong *plStack_40;
  
  if ((*(char *)(param_1 + 0x568) == '\0') || (*(char *)(param_1 + 0x569) == '\0')) {
    return;
  }
  QueryPerformanceCounter(&lStackX_8);
  dVar9 = (double)lStackX_8 * _DAT_14ed8b438 + _DAT_14bf2ec28;
  if (((*(char *)(param_1 + 0x649) == '\0') || (*(char *)(param_1 + 0x648) != '\0')) ||
     (*(double *)(param_1 + 0x650) <= 0.0)) {
    *(undefined1 *)(param_1 + 0x569) = 0;
    *(double *)(param_1 + 0x668) =
         (dVar9 - *(double *)(param_1 + 0x670)) + *(double *)(param_1 + 0x668);
    if (*(longlong *)(param_1 + 0x498) != 0) {
      FUN_14670a680(*(longlong *)(param_1 + 0x498),0);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x569) = 0;
    dVar9 = *(double *)(param_1 + 0x650) + dVar9;
    auVar5._8_4_ = SUB84(dVar9,0);
    auVar5._0_8_ = dVar9;
    auVar5._12_4_ = (int)((ulonglong)dVar9 >> 0x20);
    *(undefined1 (*) [16])(param_1 + 0x638) = auVar5;
    FUN_14830f660(param_1);
  }
  if (*(longlong *)(param_1 + 0x4b0) != 0) {
    FUN_148320930();
  }
  if (4 < DAT_14edc6208) {
    uStackX_18 = FUN_1482e9b40(param_1);
    puStackX_10 = (undefined8 *)&UNK_14d20e7e0;
    uStackX_20 = param_4;
    if (*_UNK_14d20e7f8 == '\0') {
      FUN_140f55110(&DAT_14edc6208,&UNK_14d20e7e0,uStackX_18);
    }
    if (DAT_14ed9a290 != '\0') {
      puStack_68 = &uStackX_18;
      FUN_140f62430(&uStack_50,puStackX_10);
      uStack_ac = 5;
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
      lVar6 = _DAT_14ed9a720;
      if (_DAT_14ed9a720 == 0) {
        lVar6 = FUN_140f2f7b0(&DAT_14ed9a720);
      }
      plVar8 = plStack_90;
      plStack_90 = plStack_40;
      uStack_a0 = uStack_50;
      uStack_9c = uStack_4c;
      uStack_98 = uStack_48;
      uStack_94 = uStack_44;
      lStack_88 = lVar6;
      if (plVar8 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar8 + 3;
        lVar6 = *plVar1;
        *plVar1 = *plVar1 + -1;
        UNLOCK();
        if (((uint)lVar6 & 0x3fffffff) == 1) {
          (**(code **)(*plVar8 + 0x10))(plVar8);
          plVar8[1] = 0;
          plVar8[2] = 0;
          LOCK();
          puVar2 = (ulonglong *)(plVar8 + 3);
          uVar3 = *puVar2;
          *puVar2 = *puVar2 - 0x40000000;
          UNLOCK();
          if (((uint)(uVar3 >> 0x1e) & 0x3fffffff) == 1) {
            (**(code **)*plVar8)(plVar8,1);
          }
        }
      }
      uStack_c0 = puStackX_10[1];
      uStack_b8 = *(undefined4 *)(puStackX_10 + 2);
      uStack_b4 = (undefined4)uRam000000014edc620c;
      uStack_b0 = (undefined4)((ulonglong)uRam000000014edc620c >> 0x20);
      uStack_ac = *(undefined *)((longlong)puStackX_10 + 0x14);
      puVar7 = (undefined8 *)FUN_14102a5b0(auStack_60);
      uStack_a8 = *puVar7;
      cVar4 = *(char *)((longlong)puStackX_10 + 0x14);
      if ((((cVar4 != '\x02') && (cVar4 != '\x03')) && ((cVar4 != '\x04' && (cVar4 != '@')))) ||
         (plVar8 = _DAT_14edbbaf0, _DAT_14edbbaf0 == (longlong *)0x0)) {
        plVar8 = (longlong *)FUN_141008de0();
      }
      (**(code **)(*plVar8 + 0x18))(plVar8,&puStack_c8);
      plVar8 = plStack_90;
      if (plStack_90 != (longlong *)0x0) {
        LOCK();
        plVar1 = plStack_90 + 3;
        lVar6 = *plVar1;
        *plVar1 = *plVar1 + -1;
        UNLOCK();
        if (((uint)lVar6 & 0x3fffffff) == 1) {
          (**(code **)(*plStack_90 + 0x10))(plStack_90);
          plVar8[1] = 0;
          plVar8[2] = 0;
          LOCK();
          puVar2 = (ulonglong *)(plVar8 + 3);
          uVar3 = *puVar2;
          *puVar2 = *puVar2 - 0x40000000;
          UNLOCK();
          if (((uint)(uVar3 >> 0x1e) & 0x3fffffff) == 1) {
            (**(code **)*plVar8)(plVar8,1);
          }
        }
      }
      return;
    }
    if (-1 < *(int *)(_DAT_14ec274a0 + 0x18)) {
      FUN_140f25530(puStackX_10,*puStackX_10,&uStackX_18);
    }
    FUN_140f4d420(puStackX_10[1],*(undefined4 *)(puStackX_10 + 2),0x14edc620c,
                  *(undefined *)((longlong)puStackX_10 + 0x14),*puStackX_10,&uStackX_18);
    return;
  }
  return;
}

