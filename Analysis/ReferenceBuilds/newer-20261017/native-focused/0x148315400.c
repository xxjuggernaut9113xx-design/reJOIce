// Newer reference PDB symbol: StopPlayback_UMusicModeManager
// Address: 0x148315400
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matched newer-build PDB public symbol: StopPlayback_UMusicModeManager */

void FUN_148315400(longlong param_1)

{
  double dVar1;
  undefined4 uVar2;
  longlong lVar3;
  longlong lVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong unaff_GS_OFFSET;
  longlong lStackX_8;
  longlong lStackX_10;
  undefined *apuStack_68 [2];
  undefined8 uStack_58;
  undefined *puStack_48;
  undefined1 *apuStack_40 [3];
  undefined *puStack_28;
  undefined1 **ppuStack_20;
  
  if (*(char *)(param_1 + 0x568) != '\0') {
    if (4 < DAT_14edc6208) {
      if (*(char *)(param_1 + 0x569) == '\0') {
        if (*(char *)(param_1 + 0x648) == '\0') {
          if (*(char *)(param_1 + 0x649) == '\0') {
            dVar1 = 0.0;
          }
          else {
            apuStack_40[0] = (undefined1 *)0x14831546a;
            QueryPerformanceCounter(&lStackX_8);
            dVar1 = ((double)lStackX_8 * _DAT_14ed8b438 + _DAT_14bf2ec28) -
                    *(double *)(param_1 + 0x640);
          }
        }
        else {
          apuStack_40[0] = (undefined1 *)0x14831549e;
          QueryPerformanceCounter(&lStackX_10);
          dVar1 = ((((double)lStackX_10 * _DAT_14ed8b438 + _DAT_14bf2ec28) -
                   *(double *)(param_1 + 0x638)) - *(double *)(param_1 + 0x668)) +
                  *(double *)(param_1 + 0x678);
        }
      }
      else {
        dVar1 = *(double *)(param_1 + 0x660);
      }
      apuStack_40[0] = (undefined1 *)0x1483154f0;
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d20ea58,dVar1);
    }
    *(undefined2 *)(param_1 + 0x568) = 0;
    *(undefined1 *)(param_1 + 0x56a) = 0;
    *(undefined1 *)(param_1 + 0x648) = 0;
    *(undefined1 *)(param_1 + 0x649) = 0;
    *(undefined8 *)(param_1 + 0x650) = 0;
    *(undefined8 *)(param_1 + 0x640) = 0;
    if (*(longlong *)(param_1 + 0x4c0) != 0) {
      apuStack_40[0] = &LAB_14831553d;
      FUN_1482a3a00();
    }
    if (*(longlong *)(param_1 + 0x230) != 0) {
      apuStack_40[0] = (undefined1 *)0x14831554e;
      uVar5 = func_0x000147a1ed70();
      apuStack_40[0] = (undefined1 *)0x148315560;
      lVar6 = FUN_14789e810(uVar5,param_1 + 0x658);
      if (lVar6 != 0) {
        apuStack_40[0] = &LAB_148315574;
        FUN_1478cf910(uVar5,*(undefined8 *)(param_1 + 0x658));
      }
      *(undefined8 *)(param_1 + 0x658) = 0;
    }
    if (*(longlong **)(param_1 + 0x498) != (longlong *)0x0) {
      apuStack_40[0] = (undefined1 *)0x14831559a;
      (**(code **)(**(longlong **)(param_1 + 0x498) + 0x600))();
      apuStack_40[0] = (undefined1 *)0x1483155ac;
      (**(code **)(**(longlong **)(param_1 + 0x498) + 0x448))(*(longlong **)(param_1 + 0x498),0);
      *(undefined8 *)(param_1 + 0x498) = 0;
    }
    if (*(longlong *)(param_1 + 0x230) != 0) {
      apuStack_40[0] = (undefined1 *)0x1483155c4;
      lVar6 = FUN_1482caaf0();
      if (lVar6 != 0) {
        apuStack_40[0] = &LAB_1483155df;
        FUN_145d5d230(lVar6,*(undefined8 *)(param_1 + 0x230),*(undefined8 *)(param_1 + 0x488));
      }
    }
    *(undefined8 *)(param_1 + 0x490) = 0;
    if (*(longlong *)(param_1 + 0x4b0) != 0) {
      apuStack_40[0] = &LAB_1483155f7;
      FUN_148321e70();
    }
    *(undefined8 *)(param_1 + 0x6b0) = 0;
    *(undefined4 *)(param_1 + 0x6f8) = 0;
    apuStack_40[0] = (undefined1 *)0x14831560c;
    FUN_148309cd0(param_1);
    apuStack_40[0] = (undefined1 *)0x148315618;
    func_0x000140d0f3a0(param_1 + 0x6d8);
    apuStack_40[0] = (undefined1 *)0x148315624;
    func_0x000140d0f3a0(param_1 + 0x6e8);
    *(undefined4 *)(param_1 + 0x61c) = *(undefined4 *)(param_1 + 0x34);
    *(undefined8 *)(param_1 + 0x4b0) = 0;
    *(undefined8 *)(param_1 + 0x4b8) = 0;
    *(undefined8 *)(param_1 + 0x4c0) = 0;
    *(undefined8 *)(param_1 + 0x4a0) = 0;
    *(undefined1 *)(param_1 + 0x608) = 0;
    *(undefined4 *)(param_1 + 0x60c) = 0x469c4000;
    *(undefined4 *)(param_1 + 0x610) = 0x469c4000;
    *(undefined8 *)(param_1 + 0x614) = 0x469c4000;
    if ((*(longlong *)(param_1 + 0x498) != 0) &&
       ((*(uint *)(*(longlong *)(param_1 + 0x498) + 8) & 0x60000000) == 0)) {
      apuStack_40[0] = (undefined1 *)0x148315699;
      FUN_1467096e0(*(undefined8 *)(param_1 + 0x498),_DAT_14c4d1160);
      apuStack_40[0] = &LAB_1483156a7;
      FUN_1467094f0(*(undefined8 *)(param_1 + 0x498),0);
    }
    *(undefined4 *)(param_1 + 0x634) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined1 *)(param_1 + 0x620) = 0;
    *(undefined4 *)(param_1 + 0x624) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x628) = 0x3f800000;
    *(undefined8 *)(param_1 + 0x62c) = 0x3f800000;
    uVar2 = _DAT_14bf2ebec;
    if ((*(longlong *)(param_1 + 0x498) != 0) &&
       ((*(uint *)(*(longlong *)(param_1 + 0x498) + 8) & 0x60000000) == 0)) {
      lVar6 = *(longlong *)(param_1 + 0x498);
      *(undefined4 *)(lVar6 + 0x540) = _DAT_14bf2ebec;
      *(undefined4 *)(lVar6 + 0x514) = 0x3f800000;
      *(undefined4 *)(lVar6 + 0x510) = 0x3f800000;
      if (((*(byte *)(lVar6 + 0x8a) & 4) != 0) &&
         (lVar3 = (**(code **)(*(longlong *)(lVar6 + 0x2a0) + 0x88))(), lVar3 != 0)) {
        if ((*(int *)(*(longlong *)
                       (*(longlong *)(unaff_GS_OFFSET + 0x58) + (ulonglong)__tls_index * 8) + 0x90ac
                     ) < _DAT_14f067240) && (FUN_14b9fb4c4(&DAT_14f067240), _DAT_14f067240 == -1)) {
          if (_DAT_14f067238 == 0) {
            FUN_141155050(&DAT_14f067238,&UNK_14cc9d710,&UNK_14cc9d730,&UNK_14c9d05a8,&UNK_14bf275d0
                          ,&UNK_14c9d05c8,1,1,2,1,0,0);
          }
          FUN_14b9fb45c(&DAT_14f067240);
        }
        lVar4 = _DAT_14f067238;
        if (_DAT_14f067238 == 0) {
          lVar4 = FUN_141155050(&DAT_14f067238,&UNK_14cc9d710,&UNK_14cc9d730,&UNK_14c9d05a8,
                                &UNK_14bf275d0,&UNK_14c9d05c8,1,1,2,1,0,0);
        }
        puStack_48 = &UNK_14ccab330;
        uStack_58 = 0;
        apuStack_68[0] = &UNK_1466b0a60;
        apuStack_40[0] = (undefined1 *)CONCAT44(apuStack_40[0]._4_4_,uVar2);
        puStack_28 = &UNK_14cca9f68;
        ppuStack_20 = apuStack_40;
        FUN_1464ead90(lVar3,*(undefined8 *)(lVar6 + 0xc80),apuStack_68,lVar4);
      }
      return;
    }
  }
  return;
}

