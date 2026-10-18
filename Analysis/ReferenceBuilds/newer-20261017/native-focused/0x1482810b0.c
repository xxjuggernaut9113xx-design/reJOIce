// Newer reference PDB symbol: GetFavoriteFrenzyCardCount_UMediaPlaybackController
// Address: 0x1482810b0
// Static inferred pseudocode; external calls/types may be unresolved.


/* Matched newer-build PDB public symbol: GetFavoriteFrenzyCardCount_UMediaPlaybackController */

undefined4 FUN_1482810b0(longlong param_1)

{
  int iVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  
  if (*(int *)(param_1 + 0x330) != *(int *)(param_1 + 0x35c)) {
    lVar4 = param_1 + 0x360;
    if (*(longlong *)(param_1 + 0x368) != 0) {
      lVar4 = *(longlong *)(param_1 + 0x368);
    }
    iVar1 = *(int *)(lVar4 + (ulonglong)(*(int *)(param_1 + 0x370) - 1U & 9) * 4);
    if (iVar1 != -1) {
      lVar4 = *(longlong *)(param_1 + 0x328);
      do {
        lVar3 = (longlong)iVar1 * 0x20;
        if (*(char *)(lVar3 + lVar4) == '\t') {
          lVar2 = lVar4 + lVar3 + 8;
          if (lVar4 + lVar3 == 0) {
            lVar2 = 0;
          }
          if (lVar2 == 0) {
            return 0;
          }
          return *(undefined4 *)(lVar2 + 8);
        }
        iVar1 = *(int *)(lVar3 + lVar4 + 0x18);
      } while (iVar1 != -1);
    }
  }
  return 0;
}

