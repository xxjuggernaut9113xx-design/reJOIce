// Selected newer-build routine; caller-supplied label: SelectRoundOption_URoundManager
// Address: 0x148310680
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: SelectRoundOption_URoundManager */

void FUN_148310680(longlong param_1,int param_2)

{
  longlong *plVar1;
  ulonglong *puVar2;
  ulonglong uVar3;
  undefined1 *puVar4;
  code *pcVar5;
  char cVar6;
  undefined1 uVar7;
  int iVar8;
  longlong lVar9;
  undefined8 *puVar10;
  longlong *plVar11;
  undefined8 unaff_retaddr;
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
  undefined1 *puStack_68;
  undefined1 auStack_60 [16];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  longlong *plStack_40;
  undefined8 uStack_38;
  
  if ((param_2 < 0) || (*(int *)(param_1 + 0x1f0) <= param_2)) {
    if (2 < DAT_14edc6208) {
      if (*_UNK_14d219cb0 == '\0') {
        FUN_140f55110();
      }
      if (DAT_14ed9a290 == '\0') {
        if (-1 < *(int *)(_DAT_14ec274a0 + 0x18)) {
          FUN_140f25530(&UNK_14d219c98,_UNK_14d219c98,&stack0x00000018);
        }
        FUN_140f4d420(_UNK_14d219ca0,_UNK_14d219ca8,0x14edc620c,UNK_14d219cac,_UNK_14d219c98,
                      &stack0x00000018);
        return;
      }
      puStack_68 = &stack0x00000018;
      FUN_140f62430(&uStack_50,&UNK_14d219c98);
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
      uStack_c0 = _UNK_14d219ca0;
      uStack_b8 = _UNK_14d219ca8;
      uStack_b4 = (undefined4)uRam000000014edc620c;
      uStack_b0 = (undefined4)((ulonglong)uRam000000014edc620c >> 0x20);
      cStack_ac = UNK_14d219cac;
      puVar10 = (undefined8 *)FUN_14102a5b0(auStack_60);
      uStack_a8 = *puVar10;
      if (((((UNK_14d219cac != '\x02') && (UNK_14d219cac != '\x03')) && (UNK_14d219cac != '\x04'))
          && (UNK_14d219cac != '@')) ||
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
  }
  else {
    if (*(int *)(param_1 + 0x1f0) <= param_2) {
      uStack_48 = &UNK_14bf260f0;
      puStack_70 = (undefined1 *)0x1483106ee;
      plStack_40 = (longlong *)(longlong)param_2;
      uStack_38 = (undefined1 *)(longlong)*(int *)(param_1 + 0x1f0);
      cVar6 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr);
      if (cVar6 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    puVar10 = (undefined8 *)(param_1 + 200);
    lVar9 = *(longlong *)(param_1 + 0x1e8) + (longlong)param_2 * 0x48;
    puStack_70 = (undefined1 *)0x148310715;
    FUN_140cf99e0(puVar10,lVar9);
    *(undefined1 *)(param_1 + 0xd8) = *(undefined1 *)(lVar9 + 0x10);
    puStack_70 = (undefined1 *)0x14831072a;
    FUN_140f82850(param_1 + 0xe0,lVar9 + 0x18);
    puStack_70 = (undefined1 *)0x148310737;
    FUN_1481f5120(param_1 + 0xf0,lVar9 + 0x28);
    *(undefined1 *)(param_1 + 0x100) = *(undefined1 *)(lVar9 + 0x38);
    *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(lVar9 + 0x3c);
    *(undefined4 *)(param_1 + 0x108) = *(undefined4 *)(lVar9 + 0x40);
    iVar8 = *(int *)(param_1 + 0xb8) + 1;
    *(int *)(param_1 + 0xb8) = iVar8;
    if (((*(char *)(param_1 + 0xc0) == '\0') && (0 < iVar8)) && (*(int *)(param_1 + 0xbc) <= iVar8))
    {
      uVar7 = 1;
    }
    else {
      uVar7 = 0;
    }
    *(undefined1 *)(param_1 + 0x16c) = uVar7;
    puStack_70 = (undefined1 *)0x148310787;
    FUN_148316e30(param_1,puVar10);
    uVar7 = *(undefined1 *)(param_1 + 0xd8);
    puVar2 = (ulonglong *)(param_1 + 0x368);
    puVar4 = (undefined1 *)*puVar2;
    if ((puVar4 <= &stack0xffffffffffffffe8) &&
       (&stack0xffffffffffffffe8 < puVar4 + *(int *)(param_1 + 0x374))) {
      plStack_40 = (longlong *)&stack0xffffffffffffffe8;
      uStack_48 = &UNK_14bf25f80;
      puStack_70 = (undefined1 *)0x148310808;
      uStack_38 = puVar4;
      cVar6 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr);
      if (cVar6 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar8 = *(int *)(param_1 + 0x370);
    *(uint *)(param_1 + 0x370) = iVar8 + 1U;
    if (*(uint *)(param_1 + 0x374) < iVar8 + 1U) {
      puStack_70 = &LAB_148310827;
      FUN_14830b750(puVar2,iVar8);
    }
    *(undefined1 *)((longlong)iVar8 + *puVar2) = uVar7;
    iVar8 = *(int *)(param_1 + 0x370);
    while (3 < iVar8) {
      iVar8 = *(int *)(param_1 + 0x370) + -1;
      if (iVar8 != 0) {
        puStack_70 = &LAB_148310858;
        func_0x00014ba120ea(*puVar2,*puVar2 + 1,(longlong)iVar8);
      }
      *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + -1;
      puStack_70 = (undefined1 *)0x148310863;
      FUN_14830bbc0(puVar2);
      iVar8 = *(int *)(param_1 + 0x370);
    }
    if (4 < DAT_14edc6208) {
      if (*(int *)(param_1 + 0xd0) == 0) {
        plStack_40 = (longlong *)&UNK_14bf24094;
      }
      else {
        plStack_40 = (longlong *)*puVar10;
      }
      uVar3 = (ulonglong)uStack_38 >> 0x20;
      uStack_38 = (undefined1 *)CONCAT44((int)uVar3,(uint)*(byte *)(param_1 + 0xd8));
      uStack_48._4_4_ = (undefined4)((ulonglong)uStack_48 >> 0x20);
      uStack_48 = (undefined *)CONCAT44(uStack_48._4_4_,*(undefined4 *)(param_1 + 0xbc));
      puStack_70 = &LAB_1483108ce;
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d219d30,param_2,*(undefined4 *)(param_1 + 0xb8));
    }
  }
  return;
}

