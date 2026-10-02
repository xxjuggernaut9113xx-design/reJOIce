/* 1481af4e0 ?UpdateSpeedItemMultiplier@UMediaPlaybackController@@QEAAXM@Z */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _UpdateSpeedItemMultiplier_UMediaPlaybackController__QEAAXM_Z(longlong param_1,float param_2)

{
  undefined *puVar1;
  
  if (_DAT_14bcfdb5c <= param_2) {
    param_2 = _DAT_14bcfdb5c;
  }
  if (param_2 <= _DAT_14bd4dc7c) {
    param_2 = _DAT_14bd4dc7c;
  }
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6daf0,(double)*(float *)(param_1 + 0x248),
                        (double)param_2);
  }
  *(float *)(param_1 + 0x248) = param_2;
  if (*(char *)(param_1 + 0x24c) == '\0') {
    if (DAT_14eab53c8 < 3) {
      return;
    }
    puVar1 = &UNK_14cf6dc20;
  }
  else {
    if (DAT_14eab53c8 < 3) {
      return;
    }
    puVar1 = &UNK_14cf6db68;
  }
  func_0x000140f24ba0(&DAT_14eab53c8,puVar1);
  return;
}




/* Resolved referenced strings:
{}
*/
