/* 1481d25e0 ?StartPatternWithMediaSync@UBeatSpawnerManager@@QEAAXAEBUFBeatPattern@@NHPEAVUMediaPlaybackController@@MMN@Z */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _StartPatternWithMediaSync_UBeatSpawnerManager__QEAAXAEBUFBeatPattern__NHPEAVUMediaPlaybackController__MMN_Z
               (longlong *param_1,undefined8 param_2,double param_3,undefined4 param_4,
               longlong param_5,undefined4 param_6,undefined4 param_7,longlong param_8)

{
  longlong *plVar1;
  longlong *plVar2;
  code *pcVar3;
  double dVar4;
  double dVar5;
  int iVar6;
  char cVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined *puVar10;
  longlong *plVar11;
  longlong lVar12;
  longlong *plStackX_8;
  undefined8 uStackX_10;
  undefined8 in_stack_ffffffffffffff38;
  undefined4 uVar13;
  longlong lStack_b8;
  longlong *plStack_b0;
  ulonglong uStack_a8;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  longlong lStack_88;
  int iStack_80;
  undefined4 uStack_7c;
  undefined8 uStack_78;
  undefined1 uStack_70;
  
  uStackX_10 = param_2;
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf77f90);
  }
  lVar8 = (**(code **)(*param_1 + 0x188))(param_1);
  if ((lVar8 == 0) || ((*(byte *)(lVar8 + 0x13d) & 0x40) != 0)) {
    if (DAT_14eab53c8 < 3) {
      return;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78048);
    return;
  }
  param_1[0x34] = (longlong)param_3;
  param_1[0xd] = param_5;
  func_0x0001481cf600(param_1 + 0x2b,param_2);
  _StopSequence_UBeatSpawnerManager__QEAAXXZ(param_1);
  plStack_b0 = (longlong *)0x0;
  uStack_a8 = 0;
  uVar9 = _GetPrivateStaticClass_UPreciseBeatWidget__CAPEAVUClass__XZ();
  func_0x000145c85650(lVar8,&plStack_b0,uVar9,0);
  iVar6 = (int)uStack_a8;
  plVar1 = plStack_b0 + (int)uStack_a8;
  plVar11 = plStack_b0;
  while( true ) {
    if ((int)uStack_a8 != iVar6) {
      plStackX_8 = (longlong *)((ulonglong)plStackX_8 & 0xffffffffffffff00);
      cVar7 = func_0x00014bba1d40(&plStackX_8);
      if (cVar7 != '\0') {
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
    }
    uVar13 = (undefined4)((ulonglong)in_stack_ffffffffffffff38 >> 0x20);
    if (plVar11 == plVar1) break;
    plVar2 = (longlong *)*plVar11;
    if (plVar2 != (longlong *)0x0) {
      lVar8 = _GetPrivateStaticClass_UPreciseBeatWidget__CAPEAVUClass__XZ();
      if ((*(int *)(lVar8 + 0x38) <= *(int *)(plVar2[2] + 0x38)) &&
         (*(longlong *)(*(longlong *)(plVar2[2] + 0x30) + (longlong)*(int *)(lVar8 + 0x38) * 8) ==
          lVar8 + 0x30)) {
        (**(code **)(*plVar2 + 0x2d8))(plVar2);
      }
    }
    plVar11 = plVar11 + 1;
  }
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78108,uStack_a8 & 0xffffffff);
  }
  (*_DAT_14bcab420)(&lStack_b8);
  param_1[0x1a] = (longlong)((double)lStack_b8 * _DAT_14ea7a5f8 + _DAT_14bcefa28);
  param_1[0x1b] = 0;
  if ((param_1[6] == 0) || (cVar7 = func_0x0001481a1bd0(), cVar7 == '\0')) {
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78240);
    }
  }
  else {
    lVar8 = param_1[6];
    uStack_a0 = *(undefined4 *)(lVar8 + 800);
    uStack_9c = *(undefined4 *)(lVar8 + 0x324);
    fStack_98 = *(float *)(lVar8 + 0x328);
    uStack_94 = *(undefined4 *)(lVar8 + 0x32c);
    uStack_90 = *(undefined4 *)(lVar8 + 0x330);
    plStackX_8 = &lStack_88;
    lStack_88 = 0;
    iStack_80 = *(int *)(lVar8 + 0x340);
    lVar12 = (longlong)iStack_80;
    uVar9 = *(undefined8 *)(lVar8 + 0x338);
    if (iStack_80 == 0) {
      uStack_7c = 0;
    }
    else {
      func_0x000140ca39a0(&lStack_88,iStack_80,0);
      func_0x00014b89502e(lStack_88,uVar9,lVar12 * 2);
    }
    uStack_78 = *(undefined8 *)(lVar8 + 0x348);
    uStack_70 = *(undefined1 *)(lVar8 + 0x350);
    dVar5 = (double)fStack_98;
    if (lStack_88 != 0) {
      func_0x000140e282f0();
    }
    dVar4 = dVar5 * _DAT_14bcfdb30;
    param_1[0x1b] = (longlong)dVar4;
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78168,SUB84(dVar5,0),dVar4);
    }
  }
  if (param_5 == 0) {
    if (DAT_14eab53c8 < 2) goto LAB_1481d2af0;
    puVar10 = &UNK_14cf78920;
  }
  else {
    if ((1 < DAT_14eab53c8) &&
       (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf782d0), 1 < DAT_14eab53c8)) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78340,param_3);
    }
    _SetBeatInterval_UMediaPlaybackController__QEAAXM_Z(param_5,(float)param_3);
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf783c0);
    }
    _SetSyncStartTime_UMediaPlaybackController__QEAAXNN_Z(param_5,param_1[0x1a],(int)param_1[0x1b]);
    if (*(char *)(param_5 + 0x30) == '\0') {
      if (1 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf785d0);
      }
      lVar8 = param_1[0x1a];
      _SyncToBeat_UMediaPlaybackController__QEAAXNNN_Z(param_5,param_8,(int)lVar8,0);
      if (((((DAT_14eab53c8 < 2) ||
            (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78658), DAT_14eab53c8 < 2)) ||
           (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf786c0,(int)param_8), DAT_14eab53c8 < 2)) ||
          ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78738,(int)lVar8), DAT_14eab53c8 < 2 ||
           (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78790,0), DAT_14eab53c8 < 2)))) ||
         (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf787e8), DAT_14eab53c8 < 2))
      goto LAB_1481d2af0;
      puVar10 = &UNK_14cf78808;
    }
    else {
      *(undefined8 *)(param_5 + 0x38) = 0;
      *(undefined1 *)(param_5 + 0x30) = 0;
      if (((DAT_14eab53c8 < 2) ||
          (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78418), DAT_14eab53c8 < 2)) ||
         ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78470,*(undefined8 *)(param_5 + 0x40)),
          DAT_14eab53c8 < 2 ||
          (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf784f0), DAT_14eab53c8 < 2))))
      goto LAB_1481d2af0;
      puVar10 = &UNK_14cf78568;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,puVar10);
    if (DAT_14eab53c8 < 2) goto LAB_1481d2af0;
    puVar10 = &UNK_14cf788b0;
  }
  func_0x000140f24ba0(&DAT_14eab53c8,puVar10);
LAB_1481d2af0:
  _BuildBeatQueue_UBeatSpawnerManager__AEAAXAEBUFBeatPattern__NHMN_Z
            (param_1,uStackX_10,SUB84(param_3,0),param_4,CONCAT44(uVar13,param_6),param_8);
  *(undefined4 *)((longlong)param_1 + 0x104) = param_4;
  *(undefined4 *)((longlong)param_1 + 0x10c) = param_6;
  *(undefined4 *)((longlong)param_1 + 0x114) = param_7;
  param_1[0x2a] = param_8;
  *(undefined1 *)(param_1 + 0x21) = 1;
  *(undefined4 *)(param_1 + 0x22) = 0;
  *(undefined4 *)(param_1 + 0x23) = 0;
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78998,(int)param_1[0x1e],param_1[0x1a],param_1[0x1b]
                       );
  }
  if (plStack_b0 != (longlong *)0x0) {
    func_0x000140e282f0();
  }
  return;
}




/* Resolved referenced strings:
{}
*/
