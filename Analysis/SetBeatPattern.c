/* 1481ae230 ?SetBeatPattern@UMediaPlaybackController@@QEAAXAEBUFBeatPattern@@MM@Z */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _SetBeatPattern_UMediaPlaybackController__QEAAXAEBUFBeatPattern__MM_Z
               (longlong param_1,undefined8 *param_2,float param_3,float param_4)

{
  longlong *plVar1;
  float fVar2;
  undefined8 uVar3;
  longlong lVar4;
  code *pcVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  char cVar9;
  int iVar10;
  uint uVar11;
  undefined *puVar12;
  wchar_t *pwVar13;
  ulonglong uVar14;
  uint uVar15;
  ulonglong uVar16;
  int iVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined8 unaff_retaddr;
  undefined *puStack_a8;
  undefined8 uStack_a0;
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined *puStack_88;
  undefined8 uStack_80;
  
  uVar14 = 0;
  if ((2 < DAT_14eab53c8) && (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d538), 2 < DAT_14eab53c8)
     ) {
    if (*(int *)(param_2 + 1) == 0) {
      puVar12 = &UNK_14bce4e94;
    }
    else {
      puVar12 = (undefined *)*param_2;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d590,puVar12);
    if (((2 < DAT_14eab53c8) &&
        (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d5d0,(double)param_3), 2 < DAT_14eab53c8)) &&
       (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d630,(double)param_4), 2 < DAT_14eab53c8)) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d688,*(undefined4 *)(param_2 + 3));
    }
  }
  plVar1 = (longlong *)(param_1 + 0x1c8);
  if (plVar1 != param_2 + 2) {
    iVar17 = *(int *)(param_2 + 3);
    lVar4 = param_2[2];
    *(int *)(param_1 + 0x1d0) = iVar17;
    if ((iVar17 == 0) && (*(int *)(param_1 + 0x1d4) == 0)) {
      *(undefined4 *)(param_1 + 0x1d4) = 0;
    }
    else {
      func_0x000141ff9420(plVar1,iVar17);
      if (iVar17 != 0) {
        func_0x00014b89502e(*plVar1,lVar4,(longlong)iVar17 << 2);
      }
    }
  }
  *(double *)(param_1 + 0x1d8) = (double)param_3;
  *(float *)(param_1 + 0x248) = param_4;
  *(undefined4 *)(param_1 + 0x294) = 0;
  if (*(char *)(param_1 + 0xbc) == '\0') {
    uVar3 = *(undefined8 *)(param_1 + 0x90);
    uVar18 = (undefined4)uVar3;
    uVar19 = (undefined4)((ulonglong)uVar3 >> 0x20);
    *(undefined8 *)(param_1 + 0x298) = uVar3;
    if (DAT_14eab53c8 < 3) goto LAB_1481ae412;
    puVar12 = &UNK_14cf6d6d8;
  }
  else {
    if (DAT_14eab53c8 < 3) goto LAB_1481ae412;
    puVar12 = &UNK_14cf6d748;
    uVar18 = (undefined4)*(undefined8 *)(param_1 + 0x298);
    uVar19 = (undefined4)((ulonglong)*(undefined8 *)(param_1 + 0x298) >> 0x20);
  }
  func_0x000140f24ba0(&DAT_14eab53c8,puVar12,CONCAT44(uVar19,uVar18));
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d7f8);
  }
LAB_1481ae412:
  fVar8 = _DAT_14cf708e0;
  fVar7 = _DAT_14bd4dcfc;
  fVar6 = _DAT_14bcef9ec;
  iVar17 = *(int *)(param_1 + 0x1d0);
  iVar10 = iVar17;
  if (0x14 < iVar17) {
    iVar10 = 0x14;
  }
  uVar16 = uVar14;
  if (0 < iVar10) {
    do {
      uVar15 = (uint)uVar16;
      uVar11 = 0;
      if ((int)uVar15 < *(int *)(param_1 + 0x1d0)) {
        uVar11 = ~uVar15 >> 0x1f;
      }
      if ((uVar11 == 0) &&
         (cVar9 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                      &UNK_14bce6ef0,(longlong)(int)uVar15,
                                      (longlong)*(int *)(param_1 + 0x1d0)), cVar9 != '\0')) {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
      fVar2 = *(float *)(uVar14 + *plVar1);
      puStack_a8 = (undefined *)0x0;
      uStack_a0 = 0;
      if (0.0 <= fVar2) {
        if (fVar7 <= fVar2) {
          if (fVar2 <= fVar8) {
            pwVar13 = L"NORMAL";
            goto LAB_1481ae57d;
          }
          func_0x000140d169d0(&puStack_88,L"SLOW (%.1fx)",(double)fVar2);
          if (puStack_a8 != (undefined *)0x0) {
            func_0x000140e282f0();
          }
          puStack_a8 = puStack_88;
          puStack_88 = (undefined *)0x0;
          uStack_a0 = uStack_80;
          uStack_80 = 0;
        }
        else {
          func_0x000140d169d0(&puStack_98,L"FAST (%.1fx)",(double)(fVar6 / fVar2));
          if (puStack_a8 != (undefined *)0x0) {
            func_0x000140e282f0();
          }
          puStack_a8 = puStack_98;
          puStack_98 = (undefined *)0x0;
          uStack_a0 = uStack_90;
          uStack_90 = 0;
        }
      }
      else {
        pwVar13 = L"REST";
LAB_1481ae57d:
        func_0x000140cf9360(&puStack_a8,pwVar13);
      }
      if (2 < DAT_14eab53c8) {
        puVar12 = &UNK_14bce4e94;
        if ((int)uStack_a0 != 0) {
          puVar12 = puStack_a8;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d848,uVar16,(double)fVar2,puVar12);
      }
      if (puStack_a8 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      uVar14 = uVar14 + 4;
      iVar17 = *(int *)(param_1 + 0x1d0);
      iVar10 = iVar17;
      if (0x14 < iVar17) {
        iVar10 = 0x14;
      }
      uVar16 = (ulonglong)(uVar15 + 1);
    } while ((int)(uVar15 + 1) < iVar10);
  }
  if ((0x14 < iVar17) && (2 < DAT_14eab53c8)) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d898,iVar17 + -0x14);
  }
  if (*(char *)(param_1 + 0x2d4) == '\x02') {
    *(undefined1 *)(param_1 + 0x24c) = 1;
    if (DAT_14eab53c8 < 3) {
      return;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d8e0);
  }
  else {
    *(undefined1 *)(param_1 + 0x24c) = 0;
    if (DAT_14eab53c8 < 3) {
      return;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d960,*(char *)(param_1 + 0x2d4));
  }
  if (2 < DAT_14eab53c8) {
    puVar12 = &UNK_14bcf1e58;
    if (*(char *)(param_1 + 0x24c) != '\0') {
      puVar12 = &UNK_14bcf1e48;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf6d9f8,puVar12);
  }
  return;
}




/* Resolved referenced strings:
{
  "14cf27ac0": "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Array.h",
  "14bcf1e58": "false",
  "14bcf1e48": "true",
  "14bce6f68": "(Index >= 0) & (Index < ArrayNum)",
  "14bce6ef0": "Array index out of bounds: %lld from an array of size %lld"
}
*/
