/* 1481d5740 ?IsPackLocked@UCHPackStoreController@@QEBA_NAEBVFString@@@Z */

bool _IsPackLocked_UCHPackStoreController__QEBA_NAEBVFString___Z
               (undefined8 param_1,undefined8 *param_2)

{
  char cVar1;
  undefined *puVar2;
  undefined *puVar3;
  
  cVar1 = _IsPackUnlocked_UCHPackStoreController__QEBA_NAEBVFString___Z();
  if (2 < DAT_14eab53c8) {
    if (*(int *)(param_2 + 1) == 0) {
      puVar2 = &UNK_14bce4e94;
    }
    else {
      puVar2 = (undefined *)*param_2;
    }
    puVar3 = &UNK_14ca022f0;
    if (cVar1 == '\0') {
      puVar3 = &UNK_14ca022e8;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7db98,puVar2,puVar3);
  }
  return cVar1 == '\0';
}




/* Resolved referenced strings:
{
  "14ca022e8": "YES"
}
*/
