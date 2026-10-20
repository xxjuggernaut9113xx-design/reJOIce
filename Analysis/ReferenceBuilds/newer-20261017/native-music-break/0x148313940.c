// Selected newer-build routine; caller-supplied label: StartBreak_UMusicModeManager
// Address: 0x148313940
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: StartBreak_UMusicModeManager */

void FUN_148313940(longlong param_1,float param_2,float param_3)

{
  undefined8 uVar1;
  float fVar2;
  float fVar3;
  
  if (((*(char *)(param_1 + 0x568) != '\0') && (*(char *)(param_1 + 0x569) == '\0')) &&
     (*(char *)(param_1 + 0x56a) == '\0')) {
    *(undefined1 *)(param_1 + 0x56a) = 1;
    if (param_2 <= 0.0) {
      param_2 = *(float *)(param_1 + 0x30);
    }
    if (param_3 < 0.0) {
      param_3 = *(float *)(param_1 + 0x34);
    }
    if (*(longlong *)(param_1 + 0x4b0) != 0) {
      FUN_14831d090();
    }
    fVar2 = param_2;
    if (param_2 <= 0.0) {
      fVar2 = *(float *)(param_1 + 0x30);
    }
    fVar3 = param_3;
    if (param_3 < 0.0) {
      fVar3 = *(float *)(param_1 + 0x34);
    }
    FUN_148313a50(param_1,fVar2,fVar3);
    if (4 < DAT_14edc6208) {
      uVar1 = FUN_1482e9b40(param_1);
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d20e860,uVar1,SUB84((double)param_2,0),(double)param_3);
    }
    func_0x0001481d29c0(param_1 + 0x70);
  }
  return;
}

