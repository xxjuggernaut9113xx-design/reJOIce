// Selected newer-build routine; caller-supplied label: UpdateChallengeProgress_UProgressionManager
// Address: 0x148318270
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: UpdateChallengeProgress_UProgressionManager
    */

void FUN_148318270(longlong param_1,ulonglong param_2,char param_3,int param_4)

{
  code *pcVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  char cVar7;
  char cVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  longlong lVar12;
  longlong lVar13;
  ulonglong uVar14;
  uint uVar15;
  ulonglong uVar16;
  longlong lVar17;
  uint uVar18;
  ulonglong uVar19;
  ulonglong uVar20;
  float fVar21;
  undefined8 unaff_retaddr;
  int iStackX_14;
  
  lVar12 = FUN_1482e71e0();
  if (lVar12 != 0) {
    uVar16 = 0;
    iStackX_14 = (int)(param_2 >> 0x20);
    if (*(char *)(lVar12 + 0x68) == '\0') {
      iVar9 = func_0x0001411c35b0(param_2 & 0xffffffff);
      if (*(int *)(param_1 + 0xf8) != *(int *)(param_1 + 0x124)) {
        lVar17 = param_1 + 0x128;
        if (*(longlong *)(param_1 + 0x130) != 0) {
          lVar17 = *(longlong *)(param_1 + 0x130);
        }
        iVar9 = *(int *)(lVar17 + (ulonglong)(*(int *)(param_1 + 0x138) - 1U & iStackX_14 + iVar9) *
                                  4);
        if (iVar9 != -1) {
          lVar17 = *(longlong *)(param_1 + 0xf0);
          do {
            lVar13 = (longlong)iVar9 * 0x40;
            if (*(ulonglong *)(lVar13 + lVar17) == param_2) {
              uVar14 = lVar17 + lVar13 + 8;
              if (lVar17 + lVar13 == 0) {
                uVar14 = uVar16;
              }
              goto LAB_1483183db;
            }
            iVar9 = *(int *)(lVar13 + 0x38 + lVar17);
          } while (iVar9 != -1);
        }
      }
      uVar14 = 0;
LAB_1483183db:
      fVar6 = _DAT_14bf56a6c;
      fVar5 = _DAT_14bf3cd28;
      if (uVar14 != 0) {
        cVar8 = *(char *)(uVar14 + 0x18);
        bVar2 = false;
        bVar4 = false;
        bVar3 = false;
        uVar19 = uVar16;
        uVar20 = uVar16;
        if (0 < *(int *)(uVar14 + 0x10)) {
          do {
            uVar15 = (uint)uVar16;
            uVar18 = ~uVar15 >> 0x1f;
            uVar10 = 0;
            if ((int)uVar15 < *(int *)(uVar14 + 0x10)) {
              uVar10 = uVar18;
            }
            if ((uVar10 == 0) &&
               (cVar7 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                      &UNK_14bf260f0,(longlong)(int)uVar15,
                                      (longlong)*(int *)(uVar14 + 0x10)), bVar2 = bVar3,
               cVar7 != '\0')) {
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            lVar17 = *(longlong *)(uVar14 + 8);
            if (*(char *)(uVar20 + lVar17) == param_3) {
              if (*(char *)(lVar12 + 0x68) == '\0') {
                switch(param_3) {
                case '\0':
                  iVar9 = *(int *)(param_1 + 0x230);
                  break;
                case '\x01':
                  iVar9 = *(int *)(param_1 + 0x234);
                  break;
                case '\x02':
                  iVar9 = *(int *)(param_1 + 0x238);
                  break;
                case '\x03':
                  iVar9 = *(int *)(param_1 + 0x23c);
                  break;
                case '\x04':
                  iVar9 = *(int *)(param_1 + 0x240);
                  break;
                default:
LAB_1483186fb:
                  iVar9 = *(int *)(uVar20 + 0xc + lVar17) + param_4;
                  break;
                case '\x06':
                  iVar9 = *(int *)(param_1 + 0x244);
                  break;
                case '\a':
                  iVar9 = *(int *)(param_1 + 0x248);
                  break;
                case '\b':
                  iVar9 = *(int *)(param_1 + 0x24c);
                  break;
                case '\n':
                  iVar9 = *(int *)(param_1 + 0x250);
                  break;
                case '\v':
                  iVar9 = *(int *)(param_1 + 0x254);
                  break;
                case '\f':
                  iVar9 = FUN_1482e9f20(param_1);
                  break;
                case '\x10':
                  iVar9 = *(int *)(param_1 + 0x294);
                  break;
                case '\x11':
                  iVar9 = *(int *)(param_1 + 0x280);
                  break;
                case '\x12':
                  iVar9 = *(int *)(param_1 + 0x284);
                  break;
                case '\x13':
                  iVar9 = *(int *)(param_1 + 0x290);
                  break;
                case '\x17':
                  iVar9 = *(int *)(param_1 + 0x288);
                  break;
                case '\x18':
                  iVar9 = FUN_1482e9f20(param_1);
                  if (iVar9 < 1) {
                    iVar9 = 0;
                  }
                  else {
                    iVar11 = *(int *)(param_1 + 0x288);
                    if (iVar11 < 0) {
                      iVar11 = 0;
                    }
                    fVar21 = ((float)iVar11 / (float)iVar9) * fVar6;
                    iVar9 = (int)ROUND((fVar21 + fVar21) - fVar5) >> 1;
                    iVar11 = 100;
                    if (iVar9 < 100) {
                      iVar11 = iVar9;
                    }
                    iVar9 = 0;
                    if (0 < iVar11) {
                      iVar9 = iVar11;
                    }
                  }
                  break;
                case '\x19':
                  iVar9 = *(int *)(param_1 + 0x29c);
                  break;
                case '\x1a':
                  iVar9 = *(int *)(param_1 + 0x2a0);
                  break;
                case '\x1b':
                  iVar9 = *(int *)(param_1 + 0x2a4);
                  break;
                case '\x1c':
                  iVar9 = *(int *)(param_1 + 0x2a8);
                  break;
                case '\x1d':
                  iVar9 = *(int *)(param_1 + 0x2ac);
                  break;
                case '\x1e':
                  iVar9 = *(int *)(param_1 + 0x2b0);
                  break;
                case '\x1f':
                  iVar9 = *(int *)(param_1 + 0x2b4);
                  break;
                case ' ':
                  iVar9 = *(int *)(param_1 + 0x2b8);
                  break;
                case '!':
                  iVar9 = *(int *)(param_1 + 700);
                  break;
                case '\"':
                  iVar9 = *(int *)(param_1 + 0x2c0);
                  break;
                case '#':
                  iVar9 = *(int *)(param_1 + 0x2c4);
                  break;
                case '$':
                  iVar9 = *(int *)(param_1 + 0x2c8);
                  break;
                case '%':
                  iVar9 = *(int *)(param_1 + 0x2cc);
                  break;
                case '&':
                  iVar9 = *(int *)(param_1 + 0x2d0);
                  break;
                case '\'':
                  iVar9 = *(int *)(param_1 + 0x2d4);
                  break;
                case '(':
                  iVar9 = *(int *)(param_1 + 0x298);
                  break;
                case ')':
                  iVar9 = *(int *)(param_1 + 0x2d8);
                  break;
                case '*':
                  iVar9 = *(int *)(param_1 + 0x2dc);
                  break;
                case '+':
                  iVar9 = *(int *)(param_1 + 0x2e0);
                  break;
                case ',':
                  iVar9 = *(int *)(param_1 + 0x2e4);
                  break;
                case '-':
                  iVar9 = *(int *)(param_1 + 0x2e8);
                  break;
                case '.':
                  iVar9 = *(int *)(param_1 + 0x2ec);
                }
              }
              else {
                if (1 < (byte)(param_3 - 0x2aU)) goto LAB_1483186fb;
                iVar9 = param_4;
                if (param_4 < *(int *)(uVar20 + 0xc + lVar17)) {
                  iVar9 = *(int *)(uVar20 + 0xc + lVar17);
                }
              }
              *(int *)(uVar20 + 0xc + lVar17) = iVar9;
              bVar4 = true;
              bVar2 = bVar3;
              if ((-1 < (int)uVar15) && ((int)uVar15 < *(int *)(uVar14 + 0x28))) {
                uVar10 = 0;
                if ((int)uVar15 < *(int *)(uVar14 + 0x28)) {
                  uVar10 = uVar18;
                }
                if ((uVar10 == 0) &&
                   (cVar7 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                          &UNK_14bf260f0,(longlong)(int)uVar15,
                                          (longlong)*(int *)(uVar14 + 0x28)), cVar7 != '\0')) {
                  pcVar1 = (code *)swi(3);
                  (*pcVar1)();
                  return;
                }
                iVar9 = *(int *)(uVar20 + 0xc + lVar17);
                if (*(int *)(*(longlong *)(uVar14 + 0x20) + uVar19) < iVar9) {
                  uVar10 = 0;
                  if ((int)uVar15 < *(int *)(uVar14 + 0x28)) {
                    uVar10 = uVar18;
                  }
                  if ((uVar10 == 0) &&
                     (cVar7 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                            &UNK_14bf260f0,(longlong)(int)uVar15,
                                            (longlong)*(int *)(uVar14 + 0x28)), cVar7 != '\0')) {
                    pcVar1 = (code *)swi(3);
                    (*pcVar1)();
                    return;
                  }
                  bVar3 = true;
                  *(int *)(*(longlong *)(uVar14 + 0x20) + uVar19) = iVar9;
                  bVar2 = true;
                }
              }
            }
            uVar16 = (ulonglong)(uVar15 + 1);
            uVar19 = uVar19 + 4;
            uVar20 = uVar20 + 0x10;
          } while ((int)(uVar15 + 1) < *(int *)(uVar14 + 0x10));
          if (bVar2) {
            FUN_14830f490(param_1);
          }
          if (((bVar4) && (cVar8 == '\0')) && (cVar8 = FUN_1482d4ee0(param_1,uVar14), cVar8 != '\0')
             ) {
            FUN_1482db240(param_1,param_2);
          }
        }
        FUN_1481e86d0(param_1 + 0x28,param_2);
      }
    }
    else {
      iVar9 = func_0x0001411c35b0(param_2 & 0xffffffff);
      if (*(int *)(param_1 + 0xa8) != *(int *)(param_1 + 0xd4)) {
        lVar17 = param_1 + 0xd8;
        if (*(longlong *)(param_1 + 0xe0) != 0) {
          lVar17 = *(longlong *)(param_1 + 0xe0);
        }
        iVar9 = *(int *)(lVar17 + (ulonglong)(*(int *)(param_1 + 0xe8) - 1U & iStackX_14 + iVar9) *
                                  4);
        if (iVar9 != -1) {
          lVar17 = *(longlong *)(param_1 + 0xa0);
          do {
            lVar13 = (longlong)iVar9 * 0x40;
            if (*(ulonglong *)(lVar13 + lVar17) == param_2) {
              if (lVar17 + lVar13 == 0) {
                return;
              }
              uVar14 = lVar17 + lVar13 + 8;
              goto LAB_1483183db;
            }
            iVar9 = *(int *)(lVar13 + 0x38 + lVar17);
          } while (iVar9 != -1);
        }
      }
    }
  }
  return;
}

