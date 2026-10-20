// Selected newer-build routine; caller-supplied label: CanSelectRewardCategory
// Address: 0x1482d1490
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: CanSelectRewardCategory */

undefined8 FUN_1482d1490(undefined8 *param_1,byte param_2)

{
  char *pcVar1;
  longlong lVar2;
  longlong *plVar3;
  code *pcVar4;
  longlong lVar5;
  char cVar6;
  char cVar7;
  ulonglong uVar8;
  undefined8 uVar9;
  undefined8 *puVar10;
  undefined7 uVar12;
  undefined8 *puVar11;
  longlong lVar13;
  char *pcVar14;
  undefined1 auStackX_10 [8];
  undefined1 auStackX_18 [8];
  uint uStackX_20;
  
  if (param_2 != 0) {
    uVar12 = (undefined7)
             ((ulonglong)
              (IMAGE_DOS_HEADER_140000000.e_magic +
              *(uint *)(&UNK_1482d163c + (ulonglong)param_2 * 4)) >> 8);
    switch(param_2) {
    default:
      uVar9 = 0;
      break;
    case 2:
      uVar9 = CONCAT71(uVar12,1);
      break;
    case 3:
      uVar9 = CONCAT71(uVar12,3);
      break;
    case 4:
      uVar9 = CONCAT71(uVar12,2);
      break;
    case 5:
      uVar9 = CONCAT71(uVar12,5);
    }
    cVar6 = FUN_1482d2ce0(*param_1,uVar9);
    if (cVar6 == '\0') {
      if ((param_2 == 1) || (param_2 == 2)) {
        return 1;
      }
      if (param_2 == 3) {
        puVar11 = (undefined8 *)param_1[3];
        puVar10 = (undefined8 *)param_1[2];
      }
      else {
        if (param_2 != 4) {
          if (param_2 != 5) {
            return 0;
          }
          puVar11 = (undefined8 *)param_1[5];
          puVar10 = (undefined8 *)param_1[6];
          uStackX_20 = *(uint *)(puVar10 + 1);
          uVar8 = (ulonglong)(int)uStackX_20;
          pcVar14 = (char *)*puVar10;
          pcVar1 = pcVar14 + uVar8;
          do {
            if (*(int *)(puVar10 + 1) != (int)uVar8) {
              auStackX_10[0] = 0;
              cVar6 = FUN_14be5bb00(auStackX_10);
              if (cVar6 != '\0') {
                pcVar4 = (code *)swi(3);
                uVar9 = (*pcVar4)();
                return uVar9;
              }
            }
            if (pcVar14 == pcVar1) {
              return 0;
            }
            cVar6 = *pcVar14;
            if (cVar6 != '\x16') {
              plVar3 = *(longlong **)*puVar11;
              lVar13 = *plVar3;
              lVar5 = plVar3[1];
              lVar2 = lVar13 + (longlong)(int)lVar5 * 8;
              while( true ) {
                if ((int)plVar3[1] != (int)lVar5) {
                  auStackX_18[0] = 0;
                  cVar7 = FUN_14be5bf10(auStackX_18);
                  if (cVar7 != '\0') {
                    pcVar4 = (code *)swi(3);
                    uVar9 = (*pcVar4)();
                    return uVar9;
                  }
                }
                if (lVar13 == lVar2) {
                  return 1;
                }
                if (*(char *)(lVar13 + 2) == cVar6) break;
                lVar13 = lVar13 + 8;
              }
            }
            uVar8 = (ulonglong)uStackX_20;
            pcVar14 = pcVar14 + 1;
          } while( true );
        }
        puVar11 = (undefined8 *)param_1[4];
        puVar10 = (undefined8 *)param_1[2];
      }
      uStackX_20 = *(uint *)(puVar11 + 1);
      uVar8 = (ulonglong)(int)uStackX_20;
      pcVar14 = (char *)*puVar11;
      pcVar1 = pcVar14 + uVar8;
      do {
        if (*(int *)(puVar11 + 1) != (int)uVar8) {
          auStackX_10[0] = 0;
          cVar6 = FUN_14be5bab0(auStackX_10);
          if (cVar6 != '\0') {
            pcVar4 = (code *)swi(3);
            uVar9 = (*pcVar4)();
            return uVar9;
          }
        }
        if (pcVar14 == pcVar1) {
          return 0;
        }
        cVar6 = *pcVar14;
        if (cVar6 != '\b') {
          plVar3 = *(longlong **)*puVar10;
          lVar13 = *plVar3;
          lVar5 = plVar3[1];
          lVar2 = lVar13 + (longlong)(int)lVar5 * 8;
          while( true ) {
            if ((int)plVar3[1] != (int)lVar5) {
              auStackX_18[0] = 0;
              cVar7 = FUN_14be5bf10(auStackX_18);
              if (cVar7 != '\0') {
                pcVar4 = (code *)swi(3);
                uVar9 = (*pcVar4)();
                return uVar9;
              }
            }
            if (lVar13 == lVar2) {
              return 1;
            }
            if (*(char *)(lVar13 + 1) == cVar6) break;
            lVar13 = lVar13 + 8;
          }
        }
        uVar8 = (ulonglong)uStackX_20;
        pcVar14 = pcVar14 + 1;
      } while( true );
    }
  }
  return 0;
}

