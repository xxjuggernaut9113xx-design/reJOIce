// Selected newer-build routine; caller-supplied label: GenerateDraftDifficultyChoices_URoundManager
// Address: 0x1482e0480
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: GenerateDraftDifficultyChoices_URoundManager
    */

void FUN_1482e0480(undefined8 param_1,int param_2,ulonglong *param_3,ulonglong *param_4)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  int *piVar4;
  ulonglong uVar5;
  bool bVar6;
  bool bVar7;
  code *pcVar8;
  float fVar9;
  char cVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  longlong lVar16;
  float fVar17;
  undefined8 unaff_retaddr;
  undefined1 uStack_58;
  undefined1 uStack_57;
  undefined1 auStack_56 [2];
  int iStack_54;
  int iStack_50;
  int aiStack_4c [5];
  
  *(undefined4 *)(param_3 + 1) = 0;
  if (*(int *)((longlong)param_3 + 0xc) < 0) {
    FUN_140d23fc0(param_3,0);
  }
  *(undefined4 *)(param_4 + 1) = 0;
  if (*(int *)((longlong)param_4 + 0xc) < 0) {
    FUN_14830c280(param_4,0);
  }
  if (*(int *)((longlong)param_3 + 0xc) < 3) {
    FUN_140d23fc0(param_3,3);
  }
  if (*(int *)((longlong)param_4 + 0xc) < 3) {
    FUN_14830c280(param_4,3);
  }
  iVar15 = 5;
  if (param_2 < 5) {
    iVar15 = param_2;
  }
  iVar14 = 1;
  if (1 < iVar15) {
    iVar14 = iVar15;
  }
  uVar11 = rand();
  fVar9 = _DAT_14bf3cd14;
  bVar6 = _DAT_14c144af0 <= (float)(uVar11 & 0x7fff) * _DAT_14bf3cd14;
  uVar11 = rand();
  fVar17 = (float)(uVar11 & 0x7fff) * fVar9;
  if (_DAT_14bfe47a8 <= fVar17) {
    uVar11 = (uint)(_DAT_14bfe47ac <= fVar17);
  }
  else {
    uVar11 = 0xffffffff;
  }
  uVar12 = rand();
  puVar3 = (undefined1 *)*param_4;
  uStack_58 = 0;
  bVar7 = _DAT_14c144af0 <= (float)(uVar12 & 0x7fff) * fVar9;
  if (((puVar3 <= &uStack_58) && (&uStack_58 < puVar3 + *(int *)((longlong)param_4 + 0xc))) &&
     (cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                             &uStack_58,puVar3,(longlong)*(int *)((longlong)param_4 + 0xc),
                             (longlong)(int)param_4[1],1), cVar10 != '\0')) {
    pcVar8 = (code *)swi(3);
    (*pcVar8)();
    return;
  }
  iVar15 = (int)param_4[1];
  *(uint *)(param_4 + 1) = iVar15 + 1U;
  if (*(uint *)((longlong)param_4 + 0xc) < iVar15 + 1U) {
    FUN_14830b6b0(param_4,iVar15);
  }
  *(undefined1 *)((longlong)iVar15 + *param_4) = uStack_58;
  piVar4 = (int *)*param_3;
  iVar13 = iVar14 - (bVar6 + 1);
  iVar15 = 5;
  if (iVar13 < 5) {
    iVar15 = iVar13;
  }
  iStack_54 = 1;
  if (1 < iVar15) {
    iStack_54 = iVar15;
  }
  if (((piVar4 <= &iStack_54) && (&iStack_54 < piVar4 + *(int *)((longlong)param_3 + 0xc))) &&
     (cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                             &iStack_54,piVar4,(longlong)*(int *)((longlong)param_3 + 0xc),
                             (longlong)(int)param_3[1],4), cVar10 != '\0')) {
    pcVar8 = (code *)swi(3);
    (*pcVar8)();
    return;
  }
  iVar15 = (int)param_3[1];
  *(uint *)(param_3 + 1) = iVar15 + 1U;
  if (*(uint *)((longlong)param_3 + 0xc) < iVar15 + 1U) {
    FUN_140d21b90(param_3,iVar15);
  }
  uStack_57 = 1;
  *(int *)(*param_3 + (longlong)iVar15 * 4) = iStack_54;
  puVar3 = (undefined1 *)*param_4;
  if (((puVar3 <= &uStack_57) && (&uStack_57 < puVar3 + *(int *)((longlong)param_4 + 0xc))) &&
     (cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                             &uStack_57,puVar3,(longlong)*(int *)((longlong)param_4 + 0xc),
                             (longlong)(int)param_4[1],1), cVar10 != '\0')) {
    pcVar8 = (code *)swi(3);
    (*pcVar8)();
    return;
  }
  iVar15 = (int)param_4[1];
  *(uint *)(param_4 + 1) = iVar15 + 1U;
  if (*(uint *)((longlong)param_4 + 0xc) < iVar15 + 1U) {
    FUN_14830b6b0(param_4,iVar15);
  }
  *(undefined1 *)((longlong)iVar15 + *param_4) = uStack_57;
  piVar4 = (int *)*param_3;
  iVar15 = 5;
  if ((int)(uVar11 + iVar14) < 5) {
    iVar15 = uVar11 + iVar14;
  }
  iStack_50 = 1;
  if (1 < iVar15) {
    iStack_50 = iVar15;
  }
  if (((piVar4 <= &iStack_50) && (&iStack_50 < piVar4 + *(int *)((longlong)param_3 + 0xc))) &&
     (cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                             &iStack_50,piVar4,(longlong)*(int *)((longlong)param_3 + 0xc),
                             (longlong)(int)param_3[1],4), cVar10 != '\0')) {
    pcVar8 = (code *)swi(3);
    (*pcVar8)();
    return;
  }
  iVar15 = (int)param_3[1];
  *(uint *)(param_3 + 1) = iVar15 + 1U;
  if (*(uint *)((longlong)param_3 + 0xc) < iVar15 + 1U) {
    FUN_140d21b90(param_3,iVar15);
  }
  auStack_56[0] = 2;
  *(int *)(*param_3 + (longlong)iVar15 * 4) = iStack_50;
  puVar3 = (undefined1 *)*param_4;
  if (((puVar3 <= auStack_56) && (auStack_56 < puVar3 + *(int *)((longlong)param_4 + 0xc))) &&
     (cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                             auStack_56,puVar3,(longlong)*(int *)((longlong)param_4 + 0xc),
                             (longlong)(int)param_4[1],1), cVar10 != '\0')) {
    pcVar8 = (code *)swi(3);
    (*pcVar8)();
    return;
  }
  iVar15 = (int)param_4[1];
  *(uint *)(param_4 + 1) = iVar15 + 1U;
  if (*(uint *)((longlong)param_4 + 0xc) < iVar15 + 1U) {
    FUN_14830b6b0(param_4,iVar15);
  }
  *(undefined1 *)((longlong)iVar15 + *param_4) = auStack_56[0];
  piVar4 = (int *)*param_3;
  iVar14 = bVar7 + 1 + iVar14;
  iVar15 = 5;
  if (iVar14 < 5) {
    iVar15 = iVar14;
  }
  aiStack_4c[0] = 1;
  if (1 < iVar15) {
    aiStack_4c[0] = iVar15;
  }
  if (((piVar4 <= aiStack_4c) && (aiStack_4c < piVar4 + *(int *)((longlong)param_3 + 0xc))) &&
     (cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                             aiStack_4c,piVar4,(longlong)*(int *)((longlong)param_3 + 0xc),
                             (longlong)(int)param_3[1],4), cVar10 != '\0')) {
    pcVar8 = (code *)swi(3);
    (*pcVar8)();
    return;
  }
  iVar15 = (int)param_3[1];
  *(uint *)(param_3 + 1) = iVar15 + 1U;
  if (*(uint *)((longlong)param_3 + 0xc) < iVar15 + 1U) {
    FUN_140d21b90(param_3,iVar15);
  }
  *(int *)(*param_3 + (longlong)iVar15 * 4) = aiStack_4c[0];
  iVar15 = (int)param_3[1] + -1;
  if (0 < iVar15) {
    lVar16 = (longlong)iVar15;
    do {
      if (iVar15 + 1 < 1) {
        iVar14 = 0;
      }
      else {
        uVar11 = rand();
        iVar13 = (int)((float)(uVar11 & 0x7fff) * fVar9 * (float)(iVar15 + 1));
        iVar14 = iVar15;
        if (iVar13 < iVar15) {
          iVar14 = iVar13;
        }
      }
      if (((iVar15 < 0) || (iVar14 < 0)) &&
         (cVar10 = FUN_140f8e6d0(&UNK_14bf3c4e0,&UNK_14d166cc0,0xab4,unaff_retaddr,&UNK_14bf24094),
         cVar10 != '\0')) {
        pcVar8 = (code *)swi(3);
        (*pcVar8)();
        return;
      }
      if ((((int)param_3[1] <= iVar15) || ((int)param_3[1] <= iVar14)) &&
         (cVar10 = FUN_140f8e6d0(&UNK_14bf3c520,&UNK_14d166cc0,0xab5,unaff_retaddr,&UNK_14bf24094),
         cVar10 != '\0')) {
        pcVar8 = (code *)swi(3);
        (*pcVar8)();
        return;
      }
      if (iVar15 != iVar14) {
        uVar5 = *param_3;
        uVar2 = *(undefined4 *)(uVar5 + lVar16 * 4);
        *(undefined4 *)(uVar5 + lVar16 * 4) = *(undefined4 *)(uVar5 + (longlong)iVar14 * 4);
        *(undefined4 *)(uVar5 + (longlong)iVar14 * 4) = uVar2;
      }
      if (((iVar15 < 0) || (iVar14 < 0)) &&
         (cVar10 = FUN_140f8e6d0(&UNK_14bf3c4e0,&UNK_14d166cc0,0xab4,unaff_retaddr,&UNK_14bf24094),
         cVar10 != '\0')) {
        pcVar8 = (code *)swi(3);
        (*pcVar8)();
        return;
      }
      if ((((int)param_4[1] <= iVar15) || ((int)param_4[1] <= iVar14)) &&
         (cVar10 = FUN_140f8e6d0(&UNK_14bf3c520,&UNK_14d166cc0,0xab5,unaff_retaddr,&UNK_14bf24094),
         cVar10 != '\0')) {
        pcVar8 = (code *)swi(3);
        (*pcVar8)();
        return;
      }
      if (iVar15 != iVar14) {
        uVar5 = *param_4;
        uVar1 = *(undefined1 *)(uVar5 + lVar16);
        *(undefined1 *)(uVar5 + lVar16) = *(undefined1 *)((longlong)iVar14 + uVar5);
        *(undefined1 *)((longlong)iVar14 + uVar5) = uVar1;
      }
      iVar15 = iVar15 + -1;
      lVar16 = lVar16 + -1;
    } while (0 < iVar15);
  }
  return;
}

