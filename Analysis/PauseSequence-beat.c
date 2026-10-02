/* 1481d1c10 ?PauseSequence@UBeatSpawnerManager@@QEAAXXZ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _PauseSequence_UBeatSpawnerManager__QEAAXXZ(longlong param_1)

{
  double dVar1;
  double dVar2;
  longlong alStackX_8 [4];
  
  if (*(char *)(param_1 + 0x108) != '\0') {
    *(undefined1 *)(param_1 + 0x108) = 0;
    (*_DAT_14bcab420)(alStackX_8);
    dVar2 = (double)alStackX_8[0] * _DAT_14ea7a5f8 + _DAT_14bcefa28;
    dVar1 = *(double *)(param_1 + 0xd0);
    *(double *)(param_1 + 0xd0) = dVar2;
    *(double *)(param_1 + 0xd8) = (dVar2 - dVar1) + *(double *)(param_1 + 0xd8);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  return;
}



