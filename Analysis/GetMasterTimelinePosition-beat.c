/* 1481d12e0 ?GetMasterTimelinePosition@UBeatSpawnerManager@@QEBANXZ */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

double _GetMasterTimelinePosition_UBeatSpawnerManager__QEBANXZ(longlong param_1)

{
  longlong alStackX_8 [4];
  
  if (*(char *)(param_1 + 0x108) == '\0') {
    return *(double *)(param_1 + 0xd8);
  }
  (*_DAT_14bcab420)(alStackX_8);
  return (((double)alStackX_8[0] * _DAT_14ea7a5f8 + _DAT_14bcefa28) - *(double *)(param_1 + 0xd0)) +
         *(double *)(param_1 + 0xd8);
}



