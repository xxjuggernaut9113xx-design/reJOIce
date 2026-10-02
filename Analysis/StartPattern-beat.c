/* 1481d2400 ?StartPattern@UBeatSpawnerManager@@QEAAXAEBUFBeatPattern@@NHMMN@Z */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _StartPattern_UBeatSpawnerManager__QEAAXAEBUFBeatPattern__NHMMN_Z
               (longlong *param_1,undefined8 param_2,longlong param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,longlong param_7)

{
  longlong lVar1;
  undefined *puVar2;
  double dVar3;
  longlong lStackX_8;
  
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf77ca0);
  }
  lVar1 = (**(code **)(*param_1 + 0x188))(param_1);
  if ((lVar1 == 0) || ((*(byte *)(lVar1 + 0x13d) & 0x40) != 0)) {
    if (DAT_14eab53c8 < 3) {
      return;
    }
    puVar2 = &UNK_14cf77d18;
  }
  else {
    _StopSequence_UBeatSpawnerManager__QEAAXXZ(param_1);
    param_1[0x34] = param_3;
    (*_DAT_14bcab420)(&lStackX_8);
    dVar3 = (double)lStackX_8 * _DAT_14ea7a5f8;
    param_1[0x1b] = 0;
    param_1[0x1a] = (longlong)(dVar3 + _DAT_14bcefa28);
    func_0x0001481cf600(param_1 + 0x2b,param_2);
    _BuildBeatQueue_UBeatSpawnerManager__AEAAXAEBUFBeatPattern__NHMN_Z
              (param_1,param_2,(int)param_3,param_4,param_5,param_7);
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf77db8,(int)param_1[0x1e]);
    }
    *(undefined4 *)((longlong)param_1 + 0x10c) = param_5;
    param_1[0x2a] = param_7;
    *(undefined4 *)((longlong)param_1 + 0x114) = param_6;
    *(undefined4 *)((longlong)param_1 + 0x104) = param_4;
    *(undefined1 *)(param_1 + 0x21) = 1;
    *(undefined4 *)(param_1 + 0x22) = 0;
    *(undefined4 *)(param_1 + 0x23) = 0;
    if (DAT_14eab53c8 < 3) {
      return;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf77e50,param_1[0x1a]);
    if (DAT_14eab53c8 < 3) {
      return;
    }
    puVar2 = &UNK_14cf77ee0;
  }
  func_0x000140f24ba0(&DAT_14eab53c8,puVar2);
  return;
}



