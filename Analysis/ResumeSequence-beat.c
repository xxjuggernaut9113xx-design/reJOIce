/* 1481d2310 ?ResumeSequence@UBeatSpawnerManager@@QEAAXXZ */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ResumeSequence_UBeatSpawnerManager__QEAAXXZ(longlong param_1)

{
  longlong alStackX_8 [4];
  
  if ((*(char *)(param_1 + 0x108) == '\0') && (*(int *)(param_1 + 0xf0) != 0)) {
    *(undefined1 *)(param_1 + 0x108) = 1;
    (*_DAT_14bcab420)(alStackX_8);
    *(double *)(param_1 + 0xd0) = (double)alStackX_8[0] * _DAT_14ea7a5f8 + _DAT_14bcefa28;
  }
  return;
}



