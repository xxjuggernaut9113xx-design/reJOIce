// Analyst label for direct call target: BeatmapEventComparator
// Address: 0x1482d2c40
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Direct call target from the newer event sorter; analyst-assigned label. */

bool FUN_1482d2c40(undefined8 param_1,double *param_2,double *param_3)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  double dVar4;
  
  dVar4 = *param_2 - *param_3;
  if (_DAT_14bf8cef0 <
      (double)CONCAT44((uint)((ulonglong)dVar4 >> 0x20) & _UNK_14bf56a94,
                       SUB84(dVar4,0) & _DAT_14bf56a90)) {
    return *param_2 < *param_3;
  }
  cVar1 = *(char *)(param_2 + 1);
  uVar2 = 3;
  if (cVar1 == '\0') {
    uVar3 = 0;
  }
  else if (cVar1 == '\x05') {
    uVar3 = 2;
  }
  else if (cVar1 == '\x06') {
    uVar3 = 1;
  }
  else {
    uVar3 = 3;
  }
  cVar1 = *(char *)(param_3 + 1);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    if (cVar1 == '\x05') {
      return uVar3 < 2;
    }
    if (cVar1 == '\x06') {
      return uVar3 == 0;
    }
  }
  return uVar3 < uVar2;
}

