// Selected newer-build routine; caller-supplied label: EndBreak_UMusicModeManager
// Address: 0x1482dda70
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: EndBreak_UMusicModeManager */

void FUN_1482dda70(longlong param_1,float param_2)

{
  code *pcVar1;
  double dVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  double dVar6;
  float fVar7;
  undefined8 unaff_retaddr;
  longlong in_stack_ffffffffffffffa0;
  undefined4 uVar8;
  
  if (*(char *)(param_1 + 0x56a) != '\0') {
    *(undefined1 *)(param_1 + 0x56a) = 0;
    if (param_2 < 0.0) {
      param_2 = *(float *)(param_1 + 0x34);
    }
    dVar6 = (double)FUN_1482e9b40();
    uVar8 = (undefined4)((ulonglong)in_stack_ffffffffffffffa0 >> 0x20);
    uVar5 = *(uint *)(param_1 + 0x6b0);
    dVar2 = dVar6 + *(double *)(param_1 + 0x6c0);
    if ((int)uVar5 < *(int *)(param_1 + 0x2a8)) {
      do {
        uVar4 = 0;
        if ((int)uVar5 < *(int *)(param_1 + 0x2a8)) {
          uVar4 = ~uVar5 >> 0x1f;
        }
        if (uVar4 == 0) {
          in_stack_ffffffffffffffa0 = (longlong)(int)uVar5;
          cVar3 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                                in_stack_ffffffffffffffa0,(longlong)*(int *)(param_1 + 0x2a8));
          if (cVar3 != '\0') {
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
        }
        uVar8 = (undefined4)((ulonglong)in_stack_ffffffffffffffa0 >> 0x20);
        if (dVar2 < *(double *)(*(longlong *)(param_1 + 0x2a0) + (longlong)(int)uVar5 * 0x18))
        break;
        uVar5 = *(int *)(param_1 + 0x6b0) + 1;
        *(uint *)(param_1 + 0x6b0) = uVar5;
      } while ((int)uVar5 < *(int *)(param_1 + 0x2a8));
    }
    if (*(longlong *)(param_1 + 0x4c0) != 0) {
      FUN_14826ef60(*(longlong *)(param_1 + 0x4c0),*(int *)(param_1 + 0x6b0) + 1);
    }
    fVar7 = param_2;
    if (param_2 < 0.0) {
      fVar7 = *(float *)(param_1 + 0x34);
    }
    FUN_148313a50(param_1,_DAT_14c4d1160,fVar7);
    if (4 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d20e940,dVar6,SUB84(dVar2,0),(double)param_2,
                    CONCAT44(uVar8,*(undefined4 *)(param_1 + 0x6b0)));
    }
    func_0x0001481d29c0(param_1 + 0x88);
  }
  return;
}

