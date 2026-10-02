/* 1481b49f0 ?CalculateSessionXP@UProgressionManager@@QEAAHAEBUFSessionStats@@@Z */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _CalculateSessionXP_UProgressionManager__QEAAHAEBUFSessionStats___Z
              (longlong param_1,int *param_2)

{
  float fVar1;
  int iVar2;
  undefined *puVar3;
  undefined8 *puVar4;
  int iVar5;
  undefined8 *puVar6;
  float fVar7;
  
  fVar1 = _DAT_14bcef9ec;
  fVar7 = (float)*param_2 * *(float *)(param_1 + 0x7c);
  iVar2 = (int)ROUND((fVar7 + fVar7) - _DAT_14bcfdb28) >> 1;
  fVar7 = (float)param_2[10] * _DAT_14bcfdb20 * *(float *)(param_1 + 0x78);
  iVar5 = *(int *)(param_1 + 0x8c);
  if (iVar2 < *(int *)(param_1 + 0x8c)) {
    iVar5 = iVar2;
  }
  iVar2 = *(int *)(param_1 + 0x90);
  if (param_2[3] + param_2[2] < *(int *)(param_1 + 0x90)) {
    iVar2 = param_2[3] + param_2[2];
  }
  iVar5 = (int)((float)(((int)ROUND((fVar7 + fVar7) - _DAT_14bcfdb28) >> 1) + iVar5 + iVar2) +
               (float)param_2[1] * *(float *)(param_1 + 0x84));
  if ((char)param_2[0xb] != '\0') {
    iVar5 = (int)((float)iVar5 + *(float *)(param_1 + 0x88));
  }
  puVar4 = *(undefined8 **)(param_2 + 0x10);
  puVar6 = puVar4 + (longlong)param_2[0x12] * 2;
  for (; fVar7 = fVar1, puVar4 != puVar6; puVar4 = puVar4 + 2) {
    if (*(int *)(puVar4 + 1) == 0) {
      puVar3 = &UNK_14bce4e94;
    }
    else {
      puVar3 = (undefined *)*puVar4;
    }
    iVar2 = func_0x000140d807c0(puVar3,"ironman");
    fVar7 = _DAT_14bd17818;
    if (iVar2 == 0) break;
  }
  puVar4 = *(undefined8 **)(param_2 + 0x10);
  puVar6 = puVar4 + (longlong)param_2[0x12] * 2;
  do {
    if (puVar4 == puVar6) {
LAB_1481b4b55:
      return (int)ROUND(((float)iVar5 * fVar7 + (float)iVar5 * fVar7) - _DAT_14bcfdb28) >> 1;
    }
    if (*(int *)(puVar4 + 1) == 0) {
      puVar3 = &UNK_14bce4e94;
    }
    else {
      puVar3 = (undefined *)*puVar4;
    }
    iVar2 = func_0x000140d807c0(puVar3,"hardcore");
    if (iVar2 == 0) {
      fVar7 = fVar7 + _DAT_14bd774a8;
      goto LAB_1481b4b55;
    }
    puVar4 = puVar4 + 2;
  } while( true );
}




/* Resolved referenced strings:
{}
*/
