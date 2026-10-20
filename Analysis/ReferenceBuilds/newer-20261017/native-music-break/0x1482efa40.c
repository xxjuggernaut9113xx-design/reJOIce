// Selected newer-build routine; caller-supplied label: GetEffectiveBreakDuration_UMusicModeManager
// Address: 0x1482efa40
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Removing unreachable block (ram,0x0001482f8edf) */
/* WARNING: Removing unreachable block (ram,0x0001482f8ed5) */
/* WARNING: Removing unreachable block (ram,0x0001482f8eda) */
/* WARNING: Removing unreachable block (ram,0x0001482f8ef4) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: GetEffectiveBreakDuration_UMusicModeManager
    */

double FUN_1482efa40(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  longlong *plVar9;
  longlong unaff_GS_OFFSET;
  double dVar10;
  undefined1 auStackX_18 [8];
  longlong *plStack_48;
  undefined8 uStack_40;
  
  iVar6 = 5;
  if (*(int *)(param_1 + 0x468) < 5) {
    iVar6 = *(int *)(param_1 + 0x468);
  }
  iVar8 = 1;
  if (1 < iVar6) {
    iVar8 = iVar6;
  }
  iVar6 = 5;
  if (iVar8 < 5) {
    iVar6 = iVar8;
  }
  iVar8 = 1;
  if (1 < iVar6) {
    iVar8 = iVar6;
  }
  if (*(longlong *)(param_1 + 0x130) == 0) goto LAB_1482f8ebd;
  if ((*(int *)(*(longlong *)(*(longlong *)(unaff_GS_OFFSET + 0x58) + (ulonglong)__tls_index * 8) +
               0x90ac) < _DAT_14f0d33b8) && (FUN_14b9fb4c4(&DAT_14f0d33b8), _DAT_14f0d33b8 == -1)) {
    FUN_140cf7e50(&DAT_14f0d33a8,&UNK_14d20caa0);
    FUN_14b9fb19c(FUN_14bca8af0);
    FUN_14b9fb45c(&DAT_14f0d33b8);
  }
  plStack_48 = (longlong *)0x0;
  uStack_40 = 0;
  puVar7 = &UNK_14bf24094;
  if (_DAT_14f0d33b0 != 0) {
    puVar7 = _DAT_14f0d33a8;
  }
  FUN_1482c96f0(*(undefined8 *)(param_1 + 0x130),puVar7,&plStack_48);
  iVar6 = (int)uStack_40;
  plVar1 = plStack_48 + (int)uStack_40;
  plVar9 = plStack_48;
  while( true ) {
    if ((int)uStack_40 != iVar6) {
      auStackX_18[0] = 0;
      cVar4 = FUN_14be5bba0(auStackX_18);
      if (cVar4 != '\0') {
        pcVar3 = (code *)swi(3);
        dVar10 = (double)(*pcVar3)();
        return dVar10;
      }
    }
    if (plVar9 == plVar1) {
      if (plStack_48 != (longlong *)0x0) {
        FUN_140e289f0();
      }
      goto LAB_1482f8ebd;
    }
    lVar2 = *plVar9;
    if ((lVar2 != 0) && (*(char *)(lVar2 + 8) == '\0')) break;
    plVar9 = plVar9 + 1;
  }
  if (plStack_48 != (longlong *)0x0) {
    FUN_140e289f0();
  }
  iVar6 = 5;
  if (iVar8 < 5) {
    iVar6 = iVar8;
  }
  iVar5 = 1;
  if (1 < iVar6) {
    iVar5 = iVar6;
  }
  if (iVar5 == 1) {
LAB_1482f8ea0:
    dVar10 = *(double *)(lVar2 + 0x10);
  }
  else if (iVar5 == 2) {
    dVar10 = *(double *)(lVar2 + 0x18);
  }
  else if (iVar5 == 3) {
    dVar10 = *(double *)(lVar2 + 0x20);
  }
  else if (iVar5 == 4) {
    dVar10 = *(double *)(lVar2 + 0x28);
  }
  else {
    if (iVar5 != 5) goto LAB_1482f8ea0;
    dVar10 = *(double *)(lVar2 + 0x30);
  }
  if (0.0 < dVar10) {
    return dVar10;
  }
LAB_1482f8ebd:
  iVar6 = 5;
  if (iVar8 < 5) {
    iVar6 = iVar8;
  }
  iVar8 = 1;
  if (1 < iVar6) {
    iVar8 = iVar6;
  }
  return *(double *)(&UNK_14d20cad0 + (longlong)iVar8 * 8);
}

