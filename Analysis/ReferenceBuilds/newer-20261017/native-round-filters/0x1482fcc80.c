// Selected newer-build routine; caller-supplied label: IsModifierIncompatibleWithObjective_URoundManager
// Address: 0x1482fcc80
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label:
   IsModifierIncompatibleWithObjective_URoundManager */

bool FUN_1482fcc80(undefined8 *param_1,byte param_2)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  longlong lStack_18;
  int iStack_10;
  
  FUN_140cf7e50(&lStack_18,&UNK_14d2183d0);
  iVar2 = *(int *)(param_1 + 1);
  if (iVar2 == iStack_10) {
    if (iVar2 < 2) {
      bVar3 = true;
    }
    else {
      iVar2 = func_0x000140d80e70(*param_1,lStack_18);
      bVar3 = iVar2 == 0;
    }
  }
  else {
    bVar3 = iVar2 + iStack_10 == 1;
  }
  if (lStack_18 != 0) {
    FUN_140e289f0();
  }
  if (bVar3) {
    return param_2 == 0;
  }
  FUN_140cf7e50(&lStack_18,&UNK_14d218470);
  iVar2 = *(int *)(param_1 + 1);
  if (iVar2 == iStack_10) {
    if (iVar2 < 2) {
      bVar3 = true;
    }
    else {
      iVar2 = func_0x000140d80e70(*param_1,lStack_18);
      bVar3 = iVar2 == 0;
    }
  }
  else {
    bVar3 = iVar2 + iStack_10 == 1;
  }
  if (lStack_18 != 0) {
    FUN_140e289f0();
  }
  if (!bVar3) {
    FUN_140cf7e50(&lStack_18,&UNK_14d218370);
    iVar2 = *(int *)(param_1 + 1);
    if (iVar2 == iStack_10) {
      if (iVar2 < 2) {
        bVar3 = true;
      }
      else {
        iVar2 = func_0x000140d80e70(*param_1,lStack_18);
        bVar3 = iVar2 == 0;
      }
    }
    else {
      bVar3 = iVar2 + iStack_10 == 1;
    }
    if (lStack_18 != 0) {
      FUN_140e289f0();
    }
    if (bVar3) {
      if ((1 < (byte)(param_2 - 6)) && (param_2 != 3)) {
        return true;
      }
    }
    else {
      FUN_140cf7e50(&lStack_18,&UNK_14d218350);
      iVar2 = *(int *)(param_1 + 1);
      if (iVar2 == iStack_10) {
        if (iVar2 < 2) {
          bVar3 = true;
        }
        else {
          iVar2 = func_0x000140d80e70(*param_1,lStack_18);
          bVar3 = iVar2 == 0;
        }
      }
      else {
        bVar3 = iVar2 + iStack_10 == 1;
      }
      if (lStack_18 != 0) {
        FUN_140e289f0();
      }
      if (!bVar3) {
        cVar1 = FUN_1483014d0(param_1,&UNK_14d218490);
        if ((cVar1 != '\0') || (cVar1 = FUN_1483014d0(param_1,&UNK_14d218388), cVar1 != '\0')) {
          return param_2 != 8;
        }
        cVar1 = FUN_1483014d0(param_1,&UNK_14d218448);
        if (cVar1 == '\0') {
          cVar1 = FUN_1483014d0(param_1,&UNK_14d2184d8);
          if (cVar1 == '\0') {
            return true;
          }
          return param_2 != 3;
        }
        if (8 < param_2) {
          return true;
        }
        if ((0x1aaU >> (param_2 & 0x1f) & 1) == 0) {
          return true;
        }
        return false;
      }
      if (8 < param_2) {
        return true;
      }
      if ((0x1a8U >> (param_2 & 0x1f) & 1) == 0) {
        return true;
      }
    }
    return false;
  }
  return (param_2 & 0xfd) == 0;
}

