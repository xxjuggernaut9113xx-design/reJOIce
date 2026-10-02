/* 1481d1210 ?GetBeatsRemaining@UBeatSpawnerManager@@QEBAHXZ */

int _GetBeatsRemaining_UBeatSpawnerManager__QEBAHXZ(longlong param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x104) - *(int *)(param_1 + 0x118);
  if (iVar1 < 0) {
    iVar1 = 0;
  }
  return iVar1;
}



