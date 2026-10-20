// Selected newer-build routine; caller-supplied label: ScaleLootWeights
// Address: 0x1482d21a0
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: ScaleLootWeights */

void FUN_1482d21a0(longlong *param_1,float param_2)

{
  longlong lVar1;
  float fVar2;
  int iVar3;
  longlong *plVar4;
  code *pcVar5;
  char cVar6;
  longlong lVar7;
  undefined1 auStackX_8 [8];
  undefined1 auStackX_10 [8];
  
  plVar4 = (longlong *)*param_1;
  if (param_2 <= 0.0) {
    param_2 = 0.0;
  }
  lVar7 = *plVar4;
  iVar3 = (int)plVar4[1];
  fVar2 = *(float *)param_1[1];
  lVar1 = lVar7 + (longlong)iVar3 * 8;
  if (0.0 < fVar2) {
    while( true ) {
      if ((int)plVar4[1] != iVar3) {
        auStackX_8[0] = 0;
        cVar6 = FUN_14be5be20(auStackX_8);
        if (cVar6 != '\0') {
          pcVar5 = (code *)swi(3);
          (*pcVar5)();
          return;
        }
      }
      if (lVar7 == lVar1) break;
      *(float *)(lVar7 + 4) = (param_2 / fVar2) * *(float *)(lVar7 + 4);
      lVar7 = lVar7 + 8;
    }
  }
  else {
    while( true ) {
      if ((int)plVar4[1] != iVar3) {
        auStackX_10[0] = 0;
        cVar6 = FUN_14be5be20(auStackX_10);
        if (cVar6 != '\0') {
          pcVar5 = (code *)swi(3);
          (*pcVar5)();
          return;
        }
      }
      if (lVar7 == lVar1) break;
      *(undefined4 *)(lVar7 + 4) = 0;
      lVar7 = lVar7 + 8;
    }
  }
  *(float *)param_1[1] = param_2;
  return;
}

