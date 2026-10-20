// Selected newer-build routine; caller-supplied label: GetDifficultyProgressForRound_URoundManager
// Address: 0x1482ef930
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: GetDifficultyProgressForRound_URoundManager
    */

float FUN_1482ef930(longlong param_1,int param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if (*(char *)(param_1 + 0xc0) != '\0') {
    fVar3 = *(float *)(param_1 + 0x334);
    fVar4 = *(float *)(param_1 + 0x338);
    if (_DAT_14bf2ebec <= *(float *)(param_1 + 0x338)) {
      fVar4 = _DAT_14bf2ebec;
    }
    if (fVar3 <= 0.0) {
      fVar3 = 0.0;
    }
    iVar1 = 0;
    if (0 < param_2 + -1) {
      iVar1 = param_2 + -1;
    }
    if (fVar4 <= 0.0) {
      fVar4 = 0.0;
    }
    fVar2 = (float)iVar1 * fVar3;
    if (fVar4 <= (float)iVar1 * fVar3) {
      fVar2 = fVar4;
    }
    if (fVar2 <= 0.0) {
      fVar2 = 0.0;
    }
    return fVar2;
  }
  if (*(int *)(param_1 + 0xbc) < 2) {
    return 0.0;
  }
  fVar3 = (float)(param_2 + -1) / (float)(*(int *)(param_1 + 0xbc) + -1);
  if (_DAT_14bf2ebec <= fVar3) {
    fVar3 = _DAT_14bf2ebec;
  }
  if (fVar3 <= 0.0) {
    fVar3 = 0.0;
  }
  return fVar3;
}

