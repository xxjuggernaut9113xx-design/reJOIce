// Selected newer-build routine; caller-supplied label: RecordSessionMetric_UProgressionManager
// Address: 0x1483070c0
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: RecordSessionMetric_UProgressionManager */

void FUN_1483070c0(longlong param_1,byte param_2,int param_3)

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
    *(int *)(param_1 + 0x29c) = *(int *)(param_1 + 0x29c) + param_3;
    return;
  case 0x1a:
    *(int *)(param_1 + 0x2a0) = *(int *)(param_1 + 0x2a0) + param_3;
    return;
  case 0x1b:
    *(int *)(param_1 + 0x2a4) = *(int *)(param_1 + 0x2a4) + param_3;
    return;
  case 0x1c:
    *(int *)(param_1 + 0x2a8) = *(int *)(param_1 + 0x2a8) + param_3;
    return;
  case 0x1d:
    *(int *)(param_1 + 0x2ac) = *(int *)(param_1 + 0x2ac) + param_3;
    return;
  case 0x1e:
    *(int *)(param_1 + 0x2b0) = *(int *)(param_1 + 0x2b0) + param_3;
    return;
  case 0x1f:
    *(int *)(param_1 + 0x2b4) = *(int *)(param_1 + 0x2b4) + param_3;
    return;
  case 0x20:
    *(int *)(param_1 + 0x2b8) = *(int *)(param_1 + 0x2b8) + param_3;
    return;
  case 0x21:
    *(int *)(param_1 + 700) = *(int *)(param_1 + 700) + param_3;
    return;
  case 0x22:
    *(int *)(param_1 + 0x2c0) = *(int *)(param_1 + 0x2c0) + param_3;
    return;
  case 0x23:
    *(int *)(param_1 + 0x2c4) = *(int *)(param_1 + 0x2c4) + param_3;
    return;
  case 0x24:
    *(int *)(param_1 + 0x2c8) = *(int *)(param_1 + 0x2c8) + param_3;
    return;
  case 0x25:
    *(int *)(param_1 + 0x2cc) = *(int *)(param_1 + 0x2cc) + param_3;
    return;
  case 0x26:
    *(int *)(param_1 + 0x2d0) = *(int *)(param_1 + 0x2d0) + param_3;
    return;
  case 0x27:
    *(int *)(param_1 + 0x2d4) = *(int *)(param_1 + 0x2d4) + param_3;
    return;
  case 0x28:
    *(int *)(param_1 + 0x298) = *(int *)(param_1 + 0x298) + param_3;
    return;
  case 0x29:
    *(int *)(param_1 + 0x2d8) = *(int *)(param_1 + 0x2d8) + param_3;
    return;
  case 0x2a:
    iVar7 = param_3;
    if (param_3 < *(int *)(param_1 + 0x2dc)) {
      iVar7 = *(int *)(param_1 + 0x2dc);
    }
    *(int *)(param_1 + 0x2dc) = iVar7;
    break;
  case 0x2b:
    iVar7 = param_3;
    if (param_3 < *(int *)(param_1 + 0x2e0)) {
      iVar7 = *(int *)(param_1 + 0x2e0);
    }
    *(int *)(param_1 + 0x2e0) = iVar7;
    break;
  case 0x2c:
    *(int *)(param_1 + 0x2e4) = *(int *)(param_1 + 0x2e4) + param_3;
    return;
  case 0x2d:
    *(int *)(param_1 + 0x2e8) = *(int *)(param_1 + 0x2e8) + param_3;
    return;
  case 0x2e:
    *(int *)(param_1 + 0x2ec) = *(int *)(param_1 + 0x2ec) + param_3;
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
            goto code_r0x000148318a21;
          }
          break;
        }
        iVar7 = *(int *)(pbVar1 + 8);
      } while (iVar7 != -1);
    }
  }
  pbStack_38 = abStackX_10;
  piStack_30 = aiStackX_18;
  FUN_1482c7a40(param_1 + 400,auStackX_8,&pbStack_38,0);
code_r0x000148318a21:
  iVar7 = aiStackX_18[0];
  bVar3 = abStackX_10[0];
  if (2 < bRam000000014edc6208) {
    lVar5 = FUN_1481e2a90();
    if ((lVar5 == 0) &&
       (cVar4 = FUN_140f8e6d0(&UNK_14c1b5c88,&UNK_14d167280,0x94f,unaff_retaddr,&UNK_14bf24094),
       cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    FUN_141691f30(lVar5,auStackX_20,bVar3);
    FUN_1411de7e0(auStackX_20,&puStack_48);
    puVar8 = &UNK_14bf24094;
    if (iStack_40 != 0) {
      puVar8 = puStack_48;
    }
    FUN_140f252a0(0x14edc6208,&UNK_14d2138a8,puVar8,iVar7);
    if (puStack_48 != (undefined *)0x0) {
      FUN_140e289f0();
    }
  }
  FUN_14830f490(param_1);
  return;
}

