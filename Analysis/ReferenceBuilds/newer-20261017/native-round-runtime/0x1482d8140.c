// Selected newer-build routine; caller-supplied label: CalculateRecommendedShopInterval_URoundManager
// Address: 0x1482d8140
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label:
   CalculateRecommendedShopInterval_URoundManager */

int FUN_1482d8140(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 < 1) {
    param_1 = 1;
  }
  iVar1 = 1;
  if (3 < param_1) {
    iVar1 = (int)ROUND(SQRT((float)param_1) + SQRT((float)param_1) + _DAT_14bf3cd28) >> 1;
    iVar2 = 4;
    if (iVar1 < 4) {
      iVar2 = iVar1;
    }
    iVar1 = 1;
    if (1 < iVar2) {
      iVar1 = iVar2;
    }
  }
  return iVar1;
}

