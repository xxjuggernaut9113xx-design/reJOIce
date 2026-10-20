// Selected newer-build routine; caller-supplied label: SetSessionMetric_UProgressionManager
// Address: 0x148312540
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: SetSessionMetric_UProgressionManager */

void FUN_148312540(longlong param_1,undefined1 param_2,int param_3)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  int iVar4;
  undefined *puVar5;
  undefined8 unaff_retaddr;
  undefined1 auStackX_20 [8];
  undefined *puStack_38;
  int iStack_30;
  
  switch(param_2) {
  case 0:
    *(int *)(param_1 + 0x230) = param_3;
    break;
  case 1:
    *(int *)(param_1 + 0x234) = param_3;
    break;
  case 2:
    *(int *)(param_1 + 0x238) = param_3;
    break;
  case 3:
    *(int *)(param_1 + 0x23c) = param_3;
    break;
  case 4:
    iVar4 = param_3;
    if (param_3 < *(int *)(param_1 + 0x240)) {
      iVar4 = *(int *)(param_1 + 0x240);
    }
    *(int *)(param_1 + 0x240) = iVar4;
    break;
  case 5:
  case 9:
  case 0xf:
  case 0x14:
  case 0x15:
    break;
  case 6:
    *(int *)(param_1 + 0x244) = param_3;
    break;
  case 7:
    *(int *)(param_1 + 0x248) = param_3;
    break;
  case 8:
    *(int *)(param_1 + 0x24c) = param_3;
    break;
  case 10:
    *(int *)(param_1 + 0x250) = param_3;
    break;
  case 0xb:
    *(int *)(param_1 + 0x254) = param_3;
    break;
  case 0xc:
    *(int *)(param_1 + 600) = param_3;
    break;
  case 0xd:
    *(int *)(param_1 + 0x264) = param_3;
    break;
  case 0xe:
    *(int *)(param_1 + 0x260) = param_3;
    break;
  case 0x10:
    *(int *)(param_1 + 0x294) = param_3;
    break;
  case 0x11:
    iVar4 = param_3;
    if (param_3 < *(int *)(param_1 + 0x280)) {
      iVar4 = *(int *)(param_1 + 0x280);
    }
    *(int *)(param_1 + 0x280) = iVar4;
    break;
  case 0x12:
    iVar4 = param_3;
    if (param_3 < *(int *)(param_1 + 0x284)) {
      iVar4 = *(int *)(param_1 + 0x284);
    }
    *(int *)(param_1 + 0x284) = iVar4;
    break;
  case 0x13:
    *(int *)(param_1 + 0x290) = param_3;
    break;
  case 0x16:
    *(int *)(param_1 + 0x268) = param_3;
    break;
  case 0x17:
    *(int *)(param_1 + 0x288) = param_3;
    break;
  case 0x18:
    *(int *)(param_1 + 0x28c) = param_3;
    break;
  case 0x19:
    *(int *)(param_1 + 0x29c) = param_3;
    break;
  case 0x1a:
    *(int *)(param_1 + 0x2a0) = param_3;
    break;
  case 0x1b:
    *(int *)(param_1 + 0x2a4) = param_3;
    break;
  case 0x1c:
    *(int *)(param_1 + 0x2a8) = param_3;
    break;
  case 0x1d:
    *(int *)(param_1 + 0x2ac) = param_3;
    break;
  case 0x1e:
    *(int *)(param_1 + 0x2b0) = param_3;
    break;
  case 0x1f:
    *(int *)(param_1 + 0x2b4) = param_3;
    break;
  case 0x20:
    *(int *)(param_1 + 0x2b8) = param_3;
    break;
  case 0x21:
    *(int *)(param_1 + 700) = param_3;
    break;
  case 0x22:
    *(int *)(param_1 + 0x2c0) = param_3;
    break;
  case 0x23:
    *(int *)(param_1 + 0x2c4) = param_3;
    break;
  case 0x24:
    *(int *)(param_1 + 0x2c8) = param_3;
    break;
  case 0x25:
    *(int *)(param_1 + 0x2cc) = param_3;
    break;
  case 0x26:
    *(int *)(param_1 + 0x2d0) = param_3;
    break;
  case 0x27:
    *(int *)(param_1 + 0x2d4) = param_3;
    break;
  case 0x28:
    *(int *)(param_1 + 0x298) = param_3;
    break;
  case 0x29:
    *(int *)(param_1 + 0x2d8) = param_3;
    break;
  case 0x2a:
    *(int *)(param_1 + 0x2dc) = param_3;
    break;
  case 0x2b:
    *(int *)(param_1 + 0x2e0) = param_3;
    break;
  case 0x2c:
    *(int *)(param_1 + 0x2e4) = param_3;
    break;
  case 0x2d:
    *(int *)(param_1 + 0x2e8) = param_3;
    break;
  case 0x2e:
    *(int *)(param_1 + 0x2ec) = param_3;
    break;
  default:
    if (2 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d2134d8);
    }
  }
  if (5 < DAT_14edc6208) {
    lVar3 = FUN_1481e2a90();
    if ((lVar3 == 0) &&
       (cVar2 = FUN_140f8e6d0(&UNK_14c1b5c88,&UNK_14d167280,0x94f,unaff_retaddr,&UNK_14bf24094),
       cVar2 != '\0')) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    FUN_141691f30(lVar3,auStackX_20,param_2);
    FUN_1411de7e0(auStackX_20,&puStack_38);
    puVar5 = &UNK_14bf24094;
    if (iStack_30 != 0) {
      puVar5 = puStack_38;
    }
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d213550,puVar5,param_3);
    if (puStack_38 != (undefined *)0x0) {
      FUN_140e289f0();
    }
  }
  FUN_1481e86d0(param_1 + 0x28,0);
  return;
}

