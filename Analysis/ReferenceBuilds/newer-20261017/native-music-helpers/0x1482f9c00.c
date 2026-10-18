// Newer reference PDB symbol: HandleSongComplete_UMusicModeManager
// Address: 0x1482f9c00
// Static inferred pseudocode; external calls/types may be unresolved.


/* Matched newer-build PDB public symbol: HandleSongComplete_UMusicModeManager */

void FUN_1482f9c00(longlong param_1)

{
  bool bVar1;
  char cVar2;
  
  if (((*(char *)(param_1 + 0x4e9) == '\0') || (*(int *)(param_1 + 0x4f0) < 1)) ||
     ((*(char *)(param_1 + 0x4eb) == '\0' &&
      (*(int *)(param_1 + 0x4ec) <= *(int *)(param_1 + 0x4f0))))) {
    bVar1 = false;
    FUN_148315400();
    func_0x0001481d29c0(param_1 + 0x170);
  }
  else {
    bVar1 = true;
    if (*(byte *)(param_1 + 0x4f8) < 2) {
      cVar2 = FUN_148304130();
    }
    else {
      cVar2 = *(char *)(param_1 + 0x456);
      *(undefined1 *)(param_1 + 0x4ea) = 1;
    }
    FUN_148315400(param_1);
    func_0x0001481d29c0(param_1 + 0x170);
    if ((cVar2 == '\0') && (*(byte *)(param_1 + 0x4f8) < 2)) {
      if (2 < DAT_14edc6208) {
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d20e668,*(byte *)(param_1 + 0x4f8));
      }
      goto LAB_1482f9cec;
    }
  }
  if (*(char *)(param_1 + 0x4e9) == '\0') {
    return;
  }
  if (bVar1) {
    return;
  }
LAB_1482f9cec:
  func_0x0001481d29c0(param_1 + 0x1d0);
  FUN_1482ddc30(param_1);
  return;
}

