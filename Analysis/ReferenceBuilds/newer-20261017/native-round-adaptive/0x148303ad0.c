// Selected newer-build routine; caller-supplied label: PickWeightedObjective_URoundManager
// Address: 0x148303ad0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: PickWeightedObjective_URoundManager */

ulonglong FUN_148303ad0(longlong param_1,undefined8 param_2,char param_3)

{
  char *pcVar1;
  int iVar2;
  code *pcVar3;
  int iVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  ulonglong uVar8;
  byte bVar9;
  uint uVar10;
  longlong lVar11;
  char *pcVar12;
  undefined8 unaff_retaddr;
  undefined1 auStackX_8 [8];
  char acStack_48 [8];
  char *pcStack_40;
  undefined8 uStack_38;
  
  pcStack_40 = (char *)0x0;
  uStack_38 = 0;
  pcVar12 = *(char **)(param_1 + 0x1a0);
  iVar2 = *(int *)(param_1 + 0x1a8);
  pcVar1 = pcVar12 + iVar2;
  while( true ) {
    if (*(int *)(param_1 + 0x1a8) != iVar2) {
      auStackX_8[0] = 0;
      cVar5 = FUN_14be5ba60(auStackX_8);
      if (cVar5 != '\0') {
        pcVar3 = (code *)swi(3);
        uVar8 = (*pcVar3)();
        return uVar8;
      }
    }
    iVar4 = (int)uStack_38;
    if (pcVar12 == pcVar1) break;
    acStack_48[0] = *pcVar12;
    if ((1 < (byte)(acStack_48[0] - 6U)) || (param_3 != '\0')) {
      if (pcStack_40 <= acStack_48) {
        if ((acStack_48 < pcStack_40 + (int)uStack_38._4_4_) &&
           (cVar5 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                  acStack_48,pcStack_40,(longlong)(int)uStack_38._4_4_,
                                  (longlong)(int)uStack_38,1), cVar5 != '\0')) {
          pcVar3 = (code *)swi(3);
          uVar8 = (*pcVar3)();
          return uVar8;
        }
      }
      uVar8 = uStack_38;
      lVar11 = (longlong)(int)uStack_38;
      uVar6 = (int)uStack_38 + 1;
      uStack_38 = CONCAT44(uStack_38._4_4_,uVar6);
      if (uStack_38._4_4_ < uVar6) {
        FUN_14830b750(&pcStack_40,uVar8 & 0xffffffff);
      }
      pcStack_40[lVar11] = acStack_48[0];
    }
    pcVar12 = pcVar12 + 1;
  }
  if ((int)uStack_38 == 0) {
    if (2 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d21af70);
    }
    bVar9 = 0;
  }
  else {
    uVar10 = (int)uStack_38 - 1;
    uVar6 = 0;
    if (0 < (int)uStack_38) {
      uVar6 = rand();
      uVar7 = (uint)((float)(uVar6 & 0x7fff) * (float)iVar4 * _DAT_14bf3cd14);
      uVar6 = uVar10;
      if ((int)uVar7 < (int)uVar10) {
        uVar6 = uVar7;
      }
    }
    uVar10 = 0;
    if ((int)uVar6 < (int)uStack_38) {
      uVar10 = ~uVar6 >> 0x1f;
    }
    if ((uVar10 == 0) &&
       (cVar5 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                              (longlong)(int)uVar6,(longlong)(int)uStack_38), cVar5 != '\0')) {
      pcVar3 = (code *)swi(3);
      uVar8 = (*pcVar3)();
      return uVar8;
    }
    bVar9 = pcStack_40[(int)uVar6];
  }
  if (pcStack_40 != (char *)0x0) {
    FUN_140e289f0();
  }
  return (ulonglong)bVar9;
}

