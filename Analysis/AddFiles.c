/* 1481971f0 ?AddFiles@UFileImportManager@@QEAAXAEBV?$TArray@VFString@@V?$TSizedDefaultAllocator@$0CA@@@@@@Z */

/* WARNING: Removing unreachable block (ram,0x0001481975c7) */

void _AddFiles_UFileImportManager__QEAAXAEBV__TArray_VFString__V__TSizedDefaultAllocator__0CA______Z
               (longlong param_1,longlong *param_2)

{
  int iVar1;
  code *pcVar2;
  longlong lVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  undefined *puVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  bool bVar13;
  undefined8 unaff_retaddr;
  undefined1 auStackX_18 [8];
  undefined1 auStackX_20 [8];
  uint uVar14;
  undefined8 *puVar15;
  undefined *puStack_a8;
  int iStack_a0;
  longlong lStack_98;
  int iStack_90;
  longlong lStack_88;
  int iStack_80;
  undefined4 uStack_7c;
  longlong alStack_78 [2];
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined1 uStack_58;
  
  puVar11 = (undefined8 *)*param_2;
  uVar14 = *(uint *)(param_2 + 1);
  uVar8 = (ulonglong)(int)uVar14;
  puVar12 = puVar11 + uVar8 * 2;
  do {
    if ((int)param_2[1] != (int)uVar8) {
      auStackX_18[0] = 0;
      cVar4 = func_0x00014bae4170(auStackX_18);
      if (cVar4 != '\0') {
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
    }
    if (puVar11 == puVar12) {
      return;
    }
    lStack_88 = 0;
    iStack_80 = *(int *)(puVar11 + 1);
    uVar7 = *puVar11;
    if (iStack_80 == 0) {
      uStack_7c = 0;
    }
    else {
      func_0x000140ca39a0(&lStack_88,iStack_80,0);
      func_0x00014b89502e(lStack_88,uVar7);
    }
    func_0x00014105b400(&lStack_98,&lStack_88);
    uVar7 = func_0x00014106ffd0(alStack_78,&lStack_98);
    func_0x000140d2fc80(uVar7,&puStack_a8);
    if (alStack_78[0] != 0) {
      func_0x000140e282f0();
    }
    puVar9 = &UNK_14bce4e94;
    if (iStack_a0 != 0) {
      puVar9 = puStack_a8;
    }
    iVar5 = func_0x000140d80770(puVar9,&UNK_14bf65220);
    if (iVar5 == 0) {
LAB_14819743f:
      puVar10 = *(undefined8 **)(param_1 + 0x28);
      iVar5 = *(int *)(param_1 + 0x30);
      puVar15 = puVar10 + (longlong)iVar5 * 3;
      iVar6 = iStack_90;
      while( true ) {
        if (*(int *)(param_1 + 0x30) != iVar5) {
          auStackX_20[0] = 0;
          cVar4 = func_0x00014bc1cf40(auStackX_20);
          iVar6 = iStack_90;
          if (cVar4 != '\0') {
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
        }
        lVar3 = lStack_98;
        if (puVar10 == puVar15) break;
        iVar1 = *(int *)(puVar10 + 1);
        if (iVar1 == iVar6) {
          if (iVar1 < 2) goto LAB_1481975cd;
          iVar6 = func_0x000140d80770(*puVar10,lStack_98);
          bVar13 = iVar6 == 0;
          iVar6 = iStack_90;
        }
        else {
          bVar13 = iVar1 + iVar6 == 1;
        }
        if (bVar13) goto LAB_1481975cd;
        puVar10 = puVar10 + 3;
      }
      puVar15 = &uStack_68;
      uStack_68 = 0;
      uStack_60 = CONCAT44(uStack_60._4_4_,iVar6);
      if (iVar6 == 0) {
        uStack_60 = 0;
      }
      else {
        func_0x000140ca39a0(&uStack_68,iVar6,0);
        func_0x00014b89502e(uStack_68,lVar3);
      }
      uStack_58 = 1;
      puVar10 = *(undefined8 **)(param_1 + 0x28);
      if (((puVar10 <= &uStack_68) &&
          (&uStack_68 < puVar10 + (longlong)*(int *)(param_1 + 0x34) * 3)) &&
         (cVar4 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                      &UNK_14bce6d80,&uStack_68,puVar10,
                                      (longlong)*(int *)(param_1 + 0x34),
                                      (longlong)*(int *)(param_1 + 0x30),0x18,uVar14,puVar15),
         cVar4 != '\0')) {
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      iVar5 = *(int *)(param_1 + 0x30);
      *(uint *)(param_1 + 0x30) = iVar5 + 1U;
      if (*(uint *)(param_1 + 0x34) < iVar5 + 1U) {
        func_0x00014819c8c0(param_1 + 0x28,iVar5);
      }
      puVar15 = (undefined8 *)(*(longlong *)(param_1 + 0x28) + (longlong)iVar5 * 0x18);
      *puVar15 = 0;
      *puVar15 = uStack_68;
      uStack_68 = 0;
      *(undefined4 *)(puVar15 + 1) = (undefined4)uStack_60;
      *(undefined4 *)((longlong)puVar15 + 0xc) = uStack_60._4_4_;
      uStack_60 = 0;
      *(undefined1 *)(puVar15 + 2) = uStack_58;
LAB_1481975cd:
      if (puStack_a8 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (lStack_98 != 0) {
        func_0x000140e282f0();
      }
      if (lStack_88 != 0) {
        func_0x000140e282f0();
      }
    }
    else {
      puVar9 = &UNK_14bce4e94;
      if (iStack_a0 != 0) {
        puVar9 = puStack_a8;
      }
      iVar5 = func_0x000140d80770(puVar9,&UNK_14bf65238);
      if (iVar5 == 0) goto LAB_14819743f;
      puVar9 = &UNK_14bce4e94;
      if (iStack_a0 != 0) {
        puVar9 = puStack_a8;
      }
      iVar5 = func_0x000140d80770(puVar9,&UNK_14bf65228);
      if (iVar5 == 0) goto LAB_14819743f;
      puVar9 = &UNK_14bce4e94;
      if (iStack_a0 != 0) {
        puVar9 = puStack_a8;
      }
      iVar5 = func_0x000140d80770(puVar9,&UNK_14bd64338);
      if (iVar5 == 0) goto LAB_14819743f;
      puVar9 = &UNK_14bce4e94;
      if (iStack_a0 != 0) {
        puVar9 = puStack_a8;
      }
      iVar5 = func_0x000140d80770(puVar9,&UNK_14cf61ef0);
      if (iVar5 == 0) goto LAB_14819743f;
      puVar9 = &UNK_14bce4e94;
      if (iStack_a0 != 0) {
        puVar9 = puStack_a8;
      }
      iVar5 = func_0x000140d80770(puVar9,L"webp");
      if (iVar5 == 0) goto LAB_14819743f;
      puVar9 = &UNK_14bce4e94;
      if (iStack_a0 != 0) {
        puVar9 = puStack_a8;
      }
      iVar5 = func_0x000140d80770(puVar9,&UNK_14c7eb2c0);
      if (iVar5 == 0) goto LAB_14819743f;
      puVar9 = &UNK_14bce4e94;
      if (iStack_a0 != 0) {
        puVar9 = puStack_a8;
      }
      iVar5 = func_0x000140d80770(puVar9,L"webm");
      if (iVar5 == 0) goto LAB_14819743f;
      puVar9 = &UNK_14bce4e94;
      if (iStack_a0 != 0) {
        puVar9 = puStack_a8;
      }
      iVar5 = func_0x000140d80770(puVar9,&UNK_14c7eb280);
      if (iVar5 == 0) goto LAB_14819743f;
      if (puStack_a8 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (lStack_98 != 0) {
        func_0x000140e282f0();
      }
      if (lStack_88 != 0) {
        func_0x000140e282f0();
      }
    }
    puVar11 = puVar11 + 2;
    uVar8 = (ulonglong)uVar14;
  } while( true );
}




/* Resolved referenced strings:
{
  "14bf65238": "jpg",
  "14c7eb280": "mov",
  "14cf27ac0": "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Array.h",
  "14bf65220": "png",
  "14bd64338": "bmp",
  "14bce6eb8": "Addr < GetData() || Addr >= (GetData() + ArrayMax)",
  "14c7eb2c0": "mp4",
  "14bce6d80": "Attempting to use a container element (%p) which already comes from the container being modified (%p, ArrayMax: %lld, ArrayNum: %lld, SizeofElement: %d)!",
  "14cf61ef0": "gif",
  "14bf65228": "jpeg"
}
*/
