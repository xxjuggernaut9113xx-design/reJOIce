// Newer reference PDB symbol: OnAudioPlaybackPercent_UMusicModeManager
// Address: 0x1483020e0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matched newer-build PDB public symbol: OnAudioPlaybackPercent_UMusicModeManager */

void FUN_1483020e0(longlong param_1,undefined8 param_2,float param_3,undefined8 param_4)

{
  longlong *plVar1;
  ulonglong *puVar2;
  ulonglong uVar3;
  char cVar4;
  undefined1 auVar5 [16];
  double dVar6;
  double dVar7;
  longlong lVar8;
  undefined8 *puVar9;
  longlong *plVar10;
  longlong lStackX_8;
  undefined8 *puStackX_10;
  double dStackX_18;
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
  double *pdStack_68;
  undefined1 auStack_60 [16];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  longlong *plStack_40;
  
  *(float *)(param_1 + 0x688) = param_3;
  *(undefined1 *)(param_1 + 0x68c) = 1;
  if (((*(char *)(param_1 + 0x568) != '\0') && (*(char *)(param_1 + 0x569) == '\0')) &&
     (*(longlong *)(param_1 + 0x4a0) != 0)) {
    dVar7 = (double)(param_3 * *(float *)(*(longlong *)(param_1 + 0x4a0) + 0x100));
    if (*(char *)(param_1 + 0x648) == '\0') {
      plStack_40 = (longlong *)0x14830214a;
      QueryPerformanceCounter();
      dVar6 = (double)lStackX_8 * _DAT_14ed8b438;
      *(undefined2 *)(param_1 + 0x648) = 1;
      *(undefined8 *)(param_1 + 0x650) = 0;
      dVar6 = (dVar6 + _DAT_14bf2ec28) - dVar7;
      auVar5._8_4_ = SUB84(dVar6,0);
      auVar5._0_8_ = dVar6;
      auVar5._12_4_ = (int)((ulonglong)dVar6 >> 0x20);
      *(undefined1 (*) [16])(param_1 + 0x638) = auVar5;
      if (2 < DAT_14edc6208) {
        puStackX_10 = (undefined8 *)&UNK_14d20f970;
        dStackX_18 = dVar7;
        uStackX_20 = param_4;
        if (*_UNK_14d20f988 == '\0') {
          FUN_140f55110(&DAT_14edc6208,&UNK_14d20f970,SUB84(dVar7,0));
        }
        if (DAT_14ed9a290 != '\0') {
          pdStack_68 = &dStackX_18;
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
          lVar8 = _DAT_14ed9a720;
          if (_DAT_14ed9a720 == 0) {
            lVar8 = FUN_140f2f7b0(&DAT_14ed9a720);
          }
          plVar10 = plStack_90;
          plStack_90 = plStack_40;
          uStack_a0 = uStack_50;
          uStack_9c = uStack_4c;
          uStack_98 = uStack_48;
          uStack_94 = uStack_44;
          lStack_88 = lVar8;
          if (plVar10 != (longlong *)0x0) {
            LOCK();
            plVar1 = plVar10 + 3;
            lVar8 = *plVar1;
            *plVar1 = *plVar1 + -1;
            UNLOCK();
            if (((uint)lVar8 & 0x3fffffff) == 1) {
              (**(code **)(*plVar10 + 0x10))(plVar10);
              plVar10[1] = 0;
              plVar10[2] = 0;
              LOCK();
              puVar2 = (ulonglong *)(plVar10 + 3);
              uVar3 = *puVar2;
              *puVar2 = *puVar2 - 0x40000000;
              UNLOCK();
              if (((uint)(uVar3 >> 0x1e) & 0x3fffffff) == 1) {
                (**(code **)*plVar10)(plVar10,1);
              }
            }
          }
          uStack_c0 = puStackX_10[1];
          uStack_b8 = *(undefined4 *)(puStackX_10 + 2);
          uStack_b4 = (undefined4)uRam000000014edc620c;
          uStack_b0 = (undefined4)((ulonglong)uRam000000014edc620c >> 0x20);
          uStack_ac = *(undefined *)((longlong)puStackX_10 + 0x14);
          puVar9 = (undefined8 *)FUN_14102a5b0(auStack_60);
          uStack_a8 = *puVar9;
          cVar4 = *(char *)((longlong)puStackX_10 + 0x14);
          if ((((cVar4 != '\x02') && (cVar4 != '\x03')) && ((cVar4 != '\x04' && (cVar4 != '@')))) ||
             (plVar10 = _DAT_14edbbaf0, _DAT_14edbbaf0 == (longlong *)0x0)) {
            plVar10 = (longlong *)FUN_141008de0();
          }
          (**(code **)(*plVar10 + 0x18))(plVar10,&puStack_c8);
          plVar10 = plStack_90;
          if (plStack_90 != (longlong *)0x0) {
            LOCK();
            plVar1 = plStack_90 + 3;
            lVar8 = *plVar1;
            *plVar1 = *plVar1 + -1;
            UNLOCK();
            if (((uint)lVar8 & 0x3fffffff) == 1) {
              (**(code **)(*plStack_90 + 0x10))(plStack_90);
              plVar10[1] = 0;
              plVar10[2] = 0;
              LOCK();
              puVar2 = (ulonglong *)(plVar10 + 3);
              uVar3 = *puVar2;
              *puVar2 = *puVar2 - 0x40000000;
              UNLOCK();
              if (((uint)(uVar3 >> 0x1e) & 0x3fffffff) == 1) {
                (**(code **)*plVar10)(plVar10,1);
              }
            }
          }
          return;
        }
        if (-1 < *(int *)(_DAT_14ec274a0 + 0x18)) {
          FUN_140f25530(puStackX_10,*puStackX_10,&dStackX_18);
        }
        FUN_140f4d420(puStackX_10[1],*(undefined4 *)(puStackX_10 + 2),0x14edc620c,
                      *(undefined *)((longlong)puStackX_10 + 0x14),*puStackX_10,&dStackX_18);
        return;
      }
    }
    else {
      plStack_40 = (longlong *)0x1483021bf;
      QueryPerformanceCounter(&lStackX_8);
      dVar7 = dVar7 - ((((double)lStackX_8 * _DAT_14ed8b438 + _DAT_14bf2ec28) -
                       *(double *)(param_1 + 0x638)) - *(double *)(param_1 + 0x668));
      *(double *)(param_1 + 0x680) = dVar7 * _DAT_14bf2ec10;
      *(double *)(param_1 + 0x678) =
           (dVar7 - *(double *)(param_1 + 0x678)) * _DAT_14bf2ec00 + *(double *)(param_1 + 0x678);
    }
  }
  return;
}

