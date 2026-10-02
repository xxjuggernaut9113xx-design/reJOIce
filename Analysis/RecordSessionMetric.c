/* 1481c8fd0 ?RecordSessionMetric@UProgressionManager@@QEAAXW4EMetricType@@H@Z */

void _RecordSessionMetric_UProgressionManager__QEAAXW4EMetricType__H_Z
               (longlong param_1,byte param_2,int param_3)

{
  byte *pbVar1;
  code *pcVar2;
  byte bVar3;
  char cVar4;
  longlong lVar5;
  int *piVar6;
  int iVar7;
  undefined *puVar8;
  undefined8 unaff_retaddr;
  undefined1 auStackX_8 [8];
  byte abStackX_10 [8];
  int aiStackX_18 [2];
  undefined1 auStackX_20 [8];
  undefined *puStack_48;
  int iStack_40;
  byte *pbStack_38;
  int *piStack_30;
  
  switch(param_2) {
  case 0:
    *(int *)(param_1 + 0x230) = *(int *)(param_1 + 0x230) + param_3;
    return;
  case 1:
    *(int *)(param_1 + 0x234) = *(int *)(param_1 + 0x234) + param_3;
    return;
  case 2:
    *(int *)(param_1 + 0x238) = *(int *)(param_1 + 0x238) + param_3;
    return;
  case 3:
    *(int *)(param_1 + 0x23c) = *(int *)(param_1 + 0x23c) + param_3;
    return;
  case 4:
    iVar7 = param_3;
    if (param_3 < *(int *)(param_1 + 0x240)) {
      iVar7 = *(int *)(param_1 + 0x240);
    }
    *(int *)(param_1 + 0x240) = iVar7;
    break;
  default:
    return;
  case 6:
    *(int *)(param_1 + 0x244) = *(int *)(param_1 + 0x244) + param_3;
    return;
  case 7:
    *(int *)(param_1 + 0x248) = *(int *)(param_1 + 0x248) + param_3;
    return;
  case 8:
    *(int *)(param_1 + 0x24c) = *(int *)(param_1 + 0x24c) + param_3;
    return;
  case 10:
    *(int *)(param_1 + 0x250) = *(int *)(param_1 + 0x250) + param_3;
    return;
  case 0xb:
    *(int *)(param_1 + 0x254) = *(int *)(param_1 + 0x254) + param_3;
    return;
  case 0xc:
    *(int *)(param_1 + 600) = *(int *)(param_1 + 600) + param_3;
    return;
  case 0xd:
    *(int *)(param_1 + 0x264) = *(int *)(param_1 + 0x264) + param_3;
    return;
  case 0xe:
    *(int *)(param_1 + 0x260) = *(int *)(param_1 + 0x260) + param_3;
    return;
  case 0x10:
    *(int *)(param_1 + 0x294) = *(int *)(param_1 + 0x294) + param_3;
    return;
  case 0x11:
    iVar7 = param_3;
    if (param_3 < *(int *)(param_1 + 0x280)) {
      iVar7 = *(int *)(param_1 + 0x280);
    }
    *(int *)(param_1 + 0x280) = iVar7;
    break;
  case 0x12:
    iVar7 = param_3;
    if (param_3 < *(int *)(param_1 + 0x284)) {
      iVar7 = *(int *)(param_1 + 0x284);
    }
    *(int *)(param_1 + 0x284) = iVar7;
    break;
  case 0x13:
    *(int *)(param_1 + 0x290) = *(int *)(param_1 + 0x290) + param_3;
    return;
  case 0x16:
    *(int *)(param_1 + 0x268) = *(int *)(param_1 + 0x268) + param_3;
    return;
  case 0x17:
    *(int *)(param_1 + 0x288) = *(int *)(param_1 + 0x288) + param_3;
    return;
  case 0x18:
    *(int *)(param_1 + 0x28c) = param_3;
    return;
  case 0x19:
    *(int *)(param_1 + 0x298) = *(int *)(param_1 + 0x298) + param_3;
    return;
  case 0x1a:
    *(int *)(param_1 + 0x29c) = *(int *)(param_1 + 0x29c) + param_3;
    return;
  case 0x1b:
    *(int *)(param_1 + 0x2a0) = *(int *)(param_1 + 0x2a0) + param_3;
    return;
  case 0x1c:
    *(int *)(param_1 + 0x2a4) = *(int *)(param_1 + 0x2a4) + param_3;
    return;
  case 0x1d:
    *(int *)(param_1 + 0x2a8) = *(int *)(param_1 + 0x2a8) + param_3;
    return;
  }
  abStackX_10[0] = param_2;
  aiStackX_18[0] = param_3;
  if (*(int *)(param_1 + 0x198) != *(int *)(param_1 + 0x1c4)) {
    lVar5 = param_1 + 0x1c8;
    if (*(longlong *)(param_1 + 0x1d0) != 0) {
      lVar5 = *(longlong *)(param_1 + 0x1d0);
    }
    iVar7 = *(int *)(lVar5 + ((ulonglong)(*(int *)(param_1 + 0x1d8) - 1) & (ulonglong)param_2) * 4);
    if (iVar7 != -1) {
      do {
        pbVar1 = (byte *)((longlong)iVar7 * 0x10 + *(longlong *)(param_1 + 400));
        if (*pbVar1 == param_2) {
          lVar5 = *(longlong *)(param_1 + 400) + (longlong)iVar7 * 0x10;
          piVar6 = (int *)(lVar5 + 4);
          if (lVar5 == 0) {
            piVar6 = (int *)0x0;
          }
          if (piVar6 != (int *)0x0) {
            if (param_3 <= *piVar6) {
              return;
            }
            *piVar6 = param_3;
            goto LAB_1481ce121;
          }
          break;
        }
        iVar7 = *(int *)(pbVar1 + 8);
      } while (iVar7 != -1);
    }
  }
  pbStack_38 = abStackX_10;
  piStack_30 = aiStackX_18;
  func_0x0001481b0b00(param_1 + 400,auStackX_8,&pbStack_38,0);
LAB_1481ce121:
  iVar7 = aiStackX_18[0];
  bVar3 = abStackX_10[0];
  if (2 < DAT_14eab53c8) {
    lVar5 = func_0x000148150aa0();
    if ((lVar5 == 0) &&
       (cVar4 = func_0x000140f8dfd0(&UNK_14bf76a88,&UNK_14cf28080,0x94f,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    func_0x000141691830(lVar5,auStackX_20,bVar3);
    func_0x0001411de0e0(auStackX_20,&puStack_48);
    puVar8 = &UNK_14bce4e94;
    if (iStack_40 != 0) {
      puVar8 = puStack_48;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf72928,puVar8,iVar7);
    if (puStack_48 != (undefined *)0x0) {
      func_0x000140e282f0();
    }
  }
  _SaveProgress_UProgressionManager__QEAAXXZ(param_1);
  return;
}




/* Resolved referenced strings:
{
  "14cf28080": "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\Class.h",
  "14bf76a88": "EnumClass != nullptr"
}
*/
