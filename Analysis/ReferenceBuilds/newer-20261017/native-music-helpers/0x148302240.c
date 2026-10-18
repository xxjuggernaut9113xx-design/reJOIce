// Newer reference PDB symbol: OnQuartzPlaybackStarted_UMusicModeManager
// Address: 0x148302240
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matched newer-build PDB public symbol: OnQuartzPlaybackStarted_UMusicModeManager */

void FUN_148302240(longlong param_1,char param_2,undefined8 param_3,undefined8 param_4)

{
  longlong *plVar1;
  ulonglong *puVar2;
  ulonglong uVar3;
  double dVar4;
  code *pcVar5;
  undefined1 auVar6 [16];
  double dVar7;
  char cVar8;
  longlong lVar9;
  undefined8 *puVar10;
  longlong *plVar11;
  undefined8 uVar12;
  undefined8 unaff_retaddr;
  undefined8 uStackX_18;
  longlong lStackX_20;
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
  undefined1 *puStack_70;
  undefined8 *puStack_68;
  undefined1 auStack_60 [16];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  longlong *plStack_40;
  longlong lStack_38;
  
  if (param_2 == '\x04') {
    dVar4 = *(double *)(param_1 + 0x638);
    puStack_70 = (undefined1 *)0x148302272;
    QueryPerformanceCounter();
    dVar7 = (double)lStackX_20 * _DAT_14ed8b438;
    *(undefined2 *)(param_1 + 0x648) = 1;
    *(undefined8 *)(param_1 + 0x650) = 0;
    dVar7 = dVar7 + _DAT_14bf2ec28;
    auVar6._8_4_ = SUB84(dVar7,0);
    auVar6._0_8_ = dVar7;
    auVar6._12_4_ = (int)((ulonglong)dVar7 >> 0x20);
    *(undefined1 (*) [16])(param_1 + 0x638) = auVar6;
    if (2 < DAT_14edc6208) {
      uVar12 = _DAT_14bf683b8;
      if (0 < *(int *)(param_1 + 0x2a8)) {
        if (*(int *)(param_1 + 0x2a8) < 1) {
          plStack_40 = (longlong *)0x0;
          uStack_48 = &UNK_14bf260f0;
          puStack_70 = (undefined1 *)0x148302309;
          lStack_38 = (longlong)*(int *)(param_1 + 0x2a8);
          cVar8 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr);
          if (cVar8 != '\0') {
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
        }
        uVar12 = **(undefined8 **)(param_1 + 0x2a0);
      }
      puStack_70 = &LAB_14830234c;
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d20f4e8,(dVar7 - dVar4) * _DAT_14bf2ec10,uVar12);
    }
  }
  else if ((param_2 == '\0') && (1 < DAT_14edc6208)) {
    uStackX_18 = param_3;
    lStackX_20 = param_4;
    if (*_UNK_14d20f5f8 == '\0') {
      FUN_140f55110();
    }
    if (DAT_14ed9a290 != '\0') {
      puStack_68 = &uStackX_18;
      FUN_140f62430(&uStack_50,&UNK_14d20f5e0);
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
      lVar9 = _DAT_14ed9a720;
      if (_DAT_14ed9a720 == 0) {
        lVar9 = FUN_140f2f7b0(&DAT_14ed9a720);
      }
      plVar11 = plStack_90;
      plStack_90 = plStack_40;
      uStack_a0 = uStack_50;
      uStack_9c = uStack_4c;
      uStack_98 = (undefined4)uStack_48;
      uStack_94 = uStack_48._4_4_;
      lStack_88 = lVar9;
      if (plVar11 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar11 + 3;
        lVar9 = *plVar1;
        *plVar1 = *plVar1 + -1;
        UNLOCK();
        if (((uint)lVar9 & 0x3fffffff) == 1) {
          (**(code **)(*plVar11 + 0x10))(plVar11);
          plVar11[1] = 0;
          plVar11[2] = 0;
          LOCK();
          puVar2 = (ulonglong *)(plVar11 + 3);
          uVar3 = *puVar2;
          *puVar2 = *puVar2 - 0x40000000;
          UNLOCK();
          if (((uint)(uVar3 >> 0x1e) & 0x3fffffff) == 1) {
            (**(code **)*plVar11)(plVar11,1);
          }
        }
      }
      uStack_c0 = _UNK_14d20f5e8;
      uStack_b8 = _UNK_14d20f5f0;
      uStack_b4 = (undefined4)uRam000000014edc620c;
      uStack_b0 = (undefined4)((ulonglong)uRam000000014edc620c >> 0x20);
      cStack_ac = UNK_14d20f5f4;
      puVar10 = (undefined8 *)FUN_14102a5b0(auStack_60);
      uStack_a8 = *puVar10;
      if (((((UNK_14d20f5f4 != '\x02') && (UNK_14d20f5f4 != '\x03')) && (UNK_14d20f5f4 != '\x04'))
          && (UNK_14d20f5f4 != '@')) ||
         (plVar11 = _DAT_14edbbaf0, _DAT_14edbbaf0 == (longlong *)0x0)) {
        plVar11 = (longlong *)FUN_141008de0();
      }
      (**(code **)(*plVar11 + 0x18))(plVar11,&puStack_c8);
      plVar11 = plStack_90;
      if (plStack_90 != (longlong *)0x0) {
        LOCK();
        plVar1 = plStack_90 + 3;
        lVar9 = *plVar1;
        *plVar1 = *plVar1 + -1;
        UNLOCK();
        if (((uint)lVar9 & 0x3fffffff) == 1) {
          (**(code **)(*plStack_90 + 0x10))(plStack_90);
          plVar11[1] = 0;
          plVar11[2] = 0;
          LOCK();
          puVar2 = (ulonglong *)(plVar11 + 3);
          uVar3 = *puVar2;
          *puVar2 = *puVar2 - 0x40000000;
          UNLOCK();
          if (((uint)(uVar3 >> 0x1e) & 0x3fffffff) == 1) {
            (**(code **)*plVar11)(plVar11,1);
          }
        }
      }
      return;
    }
    if (-1 < *(int *)(_DAT_14ec274a0 + 0x18)) {
      FUN_140f25530(&UNK_14d20f5e0,_UNK_14d20f5e0,&uStackX_18);
    }
    FUN_140f4d420(_UNK_14d20f5e8,_UNK_14d20f5f0,0x14edc620c,UNK_14d20f5f4,_UNK_14d20f5e0,&uStackX_18
                 );
    return;
  }
  return;
}

