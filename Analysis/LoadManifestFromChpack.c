/* 1481921f0 ?LoadManifestFromChpack@UCHPackManager@@QEAA_NAEBVFString@@AEAUFCHPackManifest@@@Z */

undefined1
_LoadManifestFromChpack_UCHPackManager__QEAA_NAEBVFString__AEAUFCHPackManifest___Z
          (undefined8 param_1,undefined8 *param_2,undefined8 param_3)

{
  char cVar1;
  undefined1 uVar2;
  undefined *puVar3;
  longlong alStack_18 [2];
  
  alStack_18[0] = 0;
  alStack_18[1] = 0;
  cVar1 = _ExtractManifestFromChpack_UCHPackManager__AEAA_NAEBVFString__AEAV2__Z
                    (param_1,param_2,alStack_18);
  if (cVar1 == '\0') {
    if (1 < DAT_14eab53c8) {
      if (*(int *)(param_2 + 1) == 0) {
        puVar3 = &UNK_14bce4e94;
      }
      else {
        puVar3 = (undefined *)*param_2;
      }
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62df0,puVar3);
    }
    uVar2 = 0;
  }
  else {
    uVar2 = _ParseManifestJson_UCHPackManager__AEAA_NAEBVFString__AEAUFCHPackManifest___Z
                      (param_1,alStack_18,param_3);
  }
  if (alStack_18[0] != 0) {
    func_0x000140e282f0();
  }
  return uVar2;
}




/* Resolved referenced strings:
{}
*/
