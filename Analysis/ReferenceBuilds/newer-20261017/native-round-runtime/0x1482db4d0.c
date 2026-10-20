// Selected newer-build routine; caller-supplied label: CompleteRound_URoundManager
// Address: 0x1482db4d0
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: CompleteRound_URoundManager */

undefined8 *
FUN_1482db4d0(longlong param_1,undefined8 *param_2,ulonglong param_3,undefined8 param_4)

{
  char *pcVar1;
  char cVar2;
  undefined1 uVar3;
  uint uVar4;
  ulonglong uVar5;
  char *pcVar6;
  char cVar7;
  
  cVar7 = (char)param_3;
  *param_2 = 0;
  param_2[1] = 0;
  uVar4 = *(uint *)(param_1 + 0xb8);
  uVar5 = (ulonglong)uVar4;
  if ((int)uVar4 < (int)*(uint *)(param_1 + 0x170)) {
    uVar4 = *(uint *)(param_1 + 0x170);
  }
  *(uint *)(param_1 + 0x170) = uVar4;
  *(char *)(param_1 + 0x178) = cVar7;
  if (cVar7 == '\0') {
    *(int *)(param_1 + 0x174) = *(int *)(param_1 + 0x174) + 1;
  }
  else {
    FUN_1481f5120(param_2,param_1 + 0xf0,param_3,param_4,1);
    pcVar6 = (char *)*param_2;
    pcVar1 = pcVar6 + (longlong)*(int *)(param_2 + 1) * 8;
    for (; pcVar6 != pcVar1; pcVar6 = pcVar6 + 8) {
      if ((*pcVar6 == '\x02') && (pcVar6[1] != '\b')) {
        FUN_1482d52b0(param_1,param_2);
        if (pcVar6 != (char *)0x0) goto LAB_1482db56d;
        goto LAB_1482db587;
      }
    }
    FUN_1482d52b0(param_1,param_2);
LAB_1482db587:
    cVar2 = FUN_1482f9da0(param_1,param_1 + 0x118);
    if (cVar2 == '\0') {
LAB_1482db56d:
      *(undefined4 *)(param_1 + 400) = 0;
      uVar5 = (ulonglong)*(uint *)(param_1 + 0xb8);
    }
    else {
      *(int *)(param_1 + 400) = *(int *)(param_1 + 400) + 1;
      uVar5 = (ulonglong)*(uint *)(param_1 + 0xb8);
    }
  }
  if ((((*(char *)(param_1 + 0xc0) == '\0') && (0 < (int)uVar5)) &&
      (*(int *)(param_1 + 0xbc) <= (int)uVar5)) &&
     ((cVar7 != '\0' && (*(int *)(param_1 + 0x174) == 0)))) {
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  *(undefined1 *)(param_1 + 0x179) = uVar3;
  if (*(char *)(param_1 + 0xc1) != '\x04') {
    *(undefined1 *)(param_1 + 0xc1) = 4;
    FUN_1481f7370(param_1 + 0x28,CONCAT71((int7)(uVar5 >> 8),4));
  }
  FUN_1481f71e0(param_1 + 0x70,*(undefined4 *)(param_1 + 0xb8),param_3 & 0xff,param_2);
  return param_2;
}

