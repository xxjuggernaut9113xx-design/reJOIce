// Selected newer-build routine; caller-supplied label: AdvanceRound_URoundManager
// Address: 0x1482d3e70
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: AdvanceRound_URoundManager */

void FUN_1482d3e70(longlong param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  undefined *puVar5;
  undefined1 auStack_18 [16];
  
  iVar1 = *(int *)(param_1 + 0xb8);
  if (((*(char *)(param_1 + 0xc0) == '\0') && (0 < iVar1)) && (*(int *)(param_1 + 0xbc) <= iVar1)) {
    if (4 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d219b20,iVar1,*(undefined4 *)(param_1 + 0xbc));
    }
    if (*(char *)(param_1 + 0xc1) != '\a') {
      *(undefined1 *)(param_1 + 0xc1) = 7;
      FUN_1481f7370(param_1 + 0x28,7);
    }
    FUN_1481f7390(param_1 + 0xa0,param_1 + 0xb8);
  }
  else {
    iVar3 = *(int *)(param_1 + 0x168) + -1;
    *(int *)(param_1 + 0x168) = iVar3;
    if ((((*(char *)(param_1 + 0xc0) == '\0') && (0 < iVar1)) && (*(int *)(param_1 + 0xbc) <= iVar1)
        ) || (0 < iVar3)) {
      if (*(char *)(param_1 + 0xc1) != '\x02') {
        *(undefined1 *)(param_1 + 0xc1) = 2;
        FUN_1481f7370(param_1 + 0x28,2);
      }
      FUN_1482e1440(param_1,auStack_18,param_2,param_3);
      FUN_1481f43d0(auStack_18);
    }
    else {
      uVar4 = rand();
      bVar2 = (float)(uVar4 & 0x7fff) * _DAT_14bf3cd14 < *(float *)(param_1 + 0x220);
      if (*(char *)(param_1 + 0xc1) != '\x05') {
        *(undefined1 *)(param_1 + 0xc1) = 5;
        FUN_1481f7370(param_1 + 0x28,5);
      }
      FUN_1481f75a0(param_1 + 0x88,bVar2);
      if (4 < DAT_14edc6208) {
        puVar5 = &UNK_14d219e88;
        if (bVar2) {
          puVar5 = &UNK_14d219e70;
        }
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d219e00,puVar5,*(undefined4 *)(param_1 + 0xb8));
      }
    }
  }
  return;
}

