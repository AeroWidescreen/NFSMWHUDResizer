#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"
#include <d3d9.h>

float TempHUDSize = 1.0f;
float TempHUDPos = 1.0f;
float HUDScale;
float HUDSize;
float HUDPos;
float FMVScale;

DWORD HUDSizeCodeCaveExit1 = 0x6D1266;
DWORD HUDSizeCodeCaveExit2 = 0x6D127D;
DWORD HUDSizeCodeCaveExit3 = 0x6D142C;
DWORD FMVSizeCodeCaveExit = 0x59A044;
DWORD sub_591460 = 0x591460;

void __declspec(naked) HUDSizeCodeCave()
{
	__asm {
		mov eax, dword ptr ds : [esp]
		cmp eax, 0x6BE714 // HUD Part 1
		je HUDSizeCodeCaveScale
		cmp eax, 0x6D19D2 // HUD Part 2
		je HUDSizeCodeCaveScale
		cmp eax, 0x6E719E // Mirror
		je HUDSizeCodeCaveScale
		cmp eax, 0x570558 // Mouse
		je HUDSizeCodeCaveScale
		push ebp
		mov ebp, esp
		and esp, 0xFFFFFFF0
		jmp HUDSizeCodeCaveExit1

	HUDSizeCodeCaveScale:
		///////////////////////////////
		fld dword ptr ds : [TempHUDSize]
		fmul dword ptr ds : [HUDScale]
		fstp dword ptr ds : [HUDSize]
		fld dword ptr ds : [TempHUDPos]
		fsub dword ptr ds : [HUDSize]
		fstp dword ptr ds : [HUDPos]
		///////////////////////////////
		push ebp
		mov ebp, esp
		and esp, 0xFFFFFFF0
		sub esp, 0xD4
		mov eax, dword ptr ds : [0x982C04]
		mov ecx, dword ptr ds : [ebp + 0x0C]
		push ebx
		xor bl, bl
		test eax, eax
		push esi
		mov esi, dword ptr ds : [ebp + 0x08]

	HUDSizeCodeCaveFullscreenCheck1:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC32DF92C
		//jne HUDSizeCodeCaveFullscreenCheck2
		cmp dword ptr ds : [esi + 0x04], 0xC2AB23D8
		jne HUDSizeCodeCaveFullscreenCheck2
		//cmp dword ptr ds : [esi + 0x10], 0x448040DA
		//jne HUDSizeCodeCaveFullscreenCheck2
		cmp dword ptr ds : [esi + 0x14], 0xC2AB23D8
		jne HUDSizeCodeCaveFullscreenCheck2
		//cmp dword ptr ds : [esi + 0x20], 0x448040DA
		//jne HUDSizeCodeCaveFullscreenCheck2
		cmp dword ptr ds : [esi + 0x24], 0x440D1B85
		jne HUDSizeCodeCaveFullscreenCheck2
		//cmp dword ptr ds : [esi + 0x30], 0xC32DF92C
		//jne HUDSizeCodeCaveFullscreenCheck2
		cmp dword ptr ds : [esi + 0x34], 0x440D1B85
		jne HUDSizeCodeCaveFullscreenCheck2
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck2:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi] , 0xC32EF92C
		//jne HUDSizeCodeCaveFullscreenCheck3
		cmp dword ptr ds : [esi + 0x04] , 0xC2AD23D8
		jne HUDSizeCodeCaveFullscreenCheck3
		//cmp dword ptr ds : [esi + 0x10] , 0x448020DA
		//jne HUDSizeCodeCaveFullscreenCheck3
		cmp dword ptr ds : [esi + 0x14] , 0xC2AD23D8
		jne HUDSizeCodeCaveFullscreenCheck3
		//cmp dword ptr ds : [esi + 0x20] , 0x448020DA
		//jne HUDSizeCodeCaveFullscreenCheck3
		cmp dword ptr ds : [esi + 0x24] , 0x440CDB85
		jne HUDSizeCodeCaveFullscreenCheck3
		//cmp dword ptr ds : [esi + 0x30] , 0xC32EF92C
		//jne HUDSizeCodeCaveFullscreenCheck3
		cmp dword ptr ds : [esi + 0x34] , 0x440CDB85
		jne HUDSizeCodeCaveFullscreenCheck3
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck3:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC3235556
		//jne HUDSizeCodeCaveFullscreenCheck4
		cmp dword ptr ds : [esi + 0x04], 0xC2960000
		jne HUDSizeCodeCaveFullscreenCheck4
		//cmp dword ptr ds : [esi + 0x10], 0x44819555
		//jne HUDSizeCodeCaveFullscreenCheck4
		cmp dword ptr ds : [esi + 0x14], 0xC2960000
		jne HUDSizeCodeCaveFullscreenCheck4
		//cmp dword ptr ds : [esi + 0x20], 0x44819555
		//jne HUDSizeCodeCaveFullscreenCheck4
		cmp dword ptr ds : [esi + 0x24], 0x440FC000
		jne HUDSizeCodeCaveFullscreenCheck4
		//cmp dword ptr ds : [esi + 0x30], 0xC3235556
		//jne HUDSizeCodeCaveFullscreenCheck4
		cmp dword ptr ds : [esi + 0x34], 0x440FC000
		jne HUDSizeCodeCaveFullscreenCheck4
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck4:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC32D5556
		//jne HUDSizeCodeCaveFullscreenCheck5
		cmp dword ptr ds : [esi + 0x04], 0xC1A00000
		jne HUDSizeCodeCaveFullscreenCheck5
		//cmp dword ptr ds : [esi + 0x10], 0x44805555
		//jne HUDSizeCodeCaveFullscreenCheck5
		cmp dword ptr ds : [esi + 0x14], 0xC1A00000
		jne HUDSizeCodeCaveFullscreenCheck5
		//cmp dword ptr ds : [esi + 0x20], 0x44805555
		//jne HUDSizeCodeCaveFullscreenCheck5
		cmp dword ptr ds : [esi + 0x24], 0x43FA0000
		jne HUDSizeCodeCaveFullscreenCheck5
		//cmp dword ptr ds : [esi + 0x30], 0xC32D5556
		//jne HUDSizeCodeCaveFullscreenCheck5
		cmp dword ptr ds : [esi + 0x34], 0x43FA0000
		jne HUDSizeCodeCaveFullscreenCheck5
		test eax, eax
		jmp HUDSizeCodeCaveExit2
	
	HUDSizeCodeCaveFullscreenCheck5:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi] , 0xC333836A
		//jne HUDSizeCodeCaveFullscreenCheck6
		cmp dword ptr ds : [esi + 0x04], 0xC19B9998
		jne HUDSizeCodeCaveFullscreenCheck6
		//cmp dword ptr ds : [esi + 0x10], 0x447F1F26
		//jne HUDSizeCodeCaveFullscreenCheck6
		cmp dword ptr ds : [esi + 0x14], 0xC19B9998
		jne HUDSizeCodeCaveFullscreenCheck6
		//cmp dword ptr ds : [esi + 0x20], 0x447F1F26
		//jne HUDSizeCodeCaveFullscreenCheck6
		cmp dword ptr ds : [esi + 0x24], 0x43FA4666
		jne HUDSizeCodeCaveFullscreenCheck6
		//cmp dword ptr ds : [esi + 0x30], 0xC333836A
		//jne HUDSizeCodeCaveFullscreenCheck6
		cmp dword ptr ds : [esi + 0x34], 0x43FA4666
		jne HUDSizeCodeCaveFullscreenCheck6
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck6:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC32D28D0
		//jne HUDSizeCodeCaveFullscreenCheck7
		cmp dword ptr ds : [esi + 0x04], 0x43510000
		jne HUDSizeCodeCaveFullscreenCheck7
		//cmp dword ptr ds : [esi + 0x10], 0x44805AE6
		//jne HUDSizeCodeCaveFullscreenCheck7
		cmp dword ptr ds : [esi + 0x14], 0x43510000
		jne HUDSizeCodeCaveFullscreenCheck7
		//cmp dword ptr ds : [esi + 0x20], 0x44805AE6
		//jne HUDSizeCodeCaveFullscreenCheck7
		cmp dword ptr ds : [esi + 0x24], 0x437F0000
		jne HUDSizeCodeCaveFullscreenCheck7
		//cmp dword ptr ds : [esi + 0x30], 0xC32D28D0
		//jne HUDSizeCodeCaveFullscreenCheck7
		cmp dword ptr ds : [esi + 0x34], 0x437F0000
		jne HUDSizeCodeCaveFullscreenCheck7
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck7:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC2BAAAAC
		//jne HUDSizeCodeCaveFullscreenCheck8
		cmp dword ptr ds : [esi + 0x04], 0xC1D00000
		jne HUDSizeCodeCaveFullscreenCheck8
		//cmp dword ptr ds : [esi + 0x10], 0x4462AAAA
		//jne HUDSizeCodeCaveFullscreenCheck8
		cmp dword ptr ds : [esi + 0x14], 0xC1D00000
		jne HUDSizeCodeCaveFullscreenCheck8
		//cmp dword ptr ds : [esi + 0x20], 0x4462AAAA
		//jne HUDSizeCodeCaveFullscreenCheck8
		cmp dword ptr ds : [esi + 0x24], 0x43F70000
		jne HUDSizeCodeCaveFullscreenCheck8
		//cmp dword ptr ds : [esi + 0x30], 0xC2BAAAAC
		//jne HUDSizeCodeCaveFullscreenCheck8
		cmp dword ptr ds : [esi + 0x34], 0x43F70000
		jne HUDSizeCodeCaveFullscreenCheck8
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck8:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC22D5558
		//jne HUDSizeCodeCaveFullscreenCheck9
		cmp dword ptr ds : [esi + 0x04], 0xC1D40000
		jne HUDSizeCodeCaveFullscreenCheck9
		//cmp dword ptr ds : [esi + 0x10], 0x44562AAA
		//jne HUDSizeCodeCaveFullscreenCheck9
		cmp dword ptr ds : [esi + 0x14], 0xC1D40000
		jne HUDSizeCodeCaveFullscreenCheck9
		//cmp dword ptr ds : [esi + 0x20], 0x44562AAA
		//jne HUDSizeCodeCaveFullscreenCheck9
		cmp dword ptr ds : [esi + 0x24], 0x43FD4000
		jne HUDSizeCodeCaveFullscreenCheck9
		//cmp dword ptr ds : [esi + 0x30], 0xC22D5558
		//jne HUDSizeCodeCaveFullscreenCheck9
		cmp dword ptr ds : [esi + 0x34], 0x43FD4000
		jne HUDSizeCodeCaveFullscreenCheck9
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck9:
		// Checks for Blacklist Bio Picture
		//cmp dword ptr ds : [esi], 0xC1BAAAB0
		//jne HUDSizeCodeCaveFullscreenCheck10
		cmp dword ptr ds : [esi + 0x04], 0x00000000
		jne HUDSizeCodeCaveFullscreenCheck10
		//cmp dword ptr ds : [esi + 0x10], 0x445B2AAA
		//jne HUDSizeCodeCaveFullscreenCheck10
		cmp dword ptr ds : [esi + 0x14], 0x00000000
		jne HUDSizeCodeCaveFullscreenCheck10
		//cmp dword ptr ds : [esi + 0x20], 0x445B2AAA
		//jne HUDSizeCodeCaveFullscreenCheck10
		cmp dword ptr ds : [esi + 0x24], 0x43F00000
		jne HUDSizeCodeCaveFullscreenCheck10
		//cmp dword ptr ds : [esi + 0x30], 0xC1BAAAB0
		//jne HUDSizeCodeCaveFullscreenCheck10
		cmp dword ptr ds : [esi + 0x34], 0x43F00000
		jne HUDSizeCodeCaveFullscreenCheck10
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck10:
		// Checks for Blacklist Bio Picture Background
		//cmp dword ptr ds : [esi], 0xC1CEAAB0
		//jne HUDSizeCodeCaveFullscreenCheck11
		cmp dword ptr ds : [esi + 0x04], 0xC1880000
		jne HUDSizeCodeCaveFullscreenCheck11
		//cmp dword ptr ds : [esi + 0x10], 0x445BCAAA
		//jne HUDSizeCodeCaveFullscreenCheck11
		cmp dword ptr ds : [esi + 0x14], 0xC1880000
		jne HUDSizeCodeCaveFullscreenCheck11
		//cmp dword ptr ds : [esi + 0x20], 0x445BCAAA
		//jne HUDSizeCodeCaveFullscreenCheck11
		cmp dword ptr ds : [esi + 0x24], 0x43F88000
		jne HUDSizeCodeCaveFullscreenCheck11
		//cmp dword ptr ds : [esi + 0x30], 0xC1CEAAB0
		//jne HUDSizeCodeCaveFullscreenCheck11
		cmp dword ptr ds : [esi + 0x34], 0x43F88000
		jne HUDSizeCodeCaveFullscreenCheck11
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck11:
		// Checks for Post-Race Overlay
		//cmp dword ptr ds : [esi], 0xC2AAAAAC
		//jne HUDSizeCodeCaveFullscreenCheck12
		cmp dword ptr ds : [esi + 0x04], 0xC1800000
		jne HUDSizeCodeCaveFullscreenCheck12
		//cmp dword ptr ds : [esi + 0x10], 0x446AAAAA
		//jne HUDSizeCodeCaveFullscreenCheck12
		cmp dword ptr ds : [esi + 0x14], 0xC1800000
		jne HUDSizeCodeCaveFullscreenCheck12
		//cmp dword ptr ds : [esi + 0x20], 0x446AAAAA
		//jne HUDSizeCodeCaveFullscreenCheck12
		cmp dword ptr ds : [esi + 0x24], 0x43F80000
		jne HUDSizeCodeCaveFullscreenCheck12
		//cmp dword ptr ds : [esi + 0x30], 0xC2AAAAAC
		//jne HUDSizeCodeCaveFullscreenCheck12
		cmp dword ptr ds : [esi + 0x34], 0x43F80000
		jne HUDSizeCodeCaveFullscreenCheck12
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck12:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC3235556
		//jne HUDSizeCodeCaveFullscreenCheck13
		cmp dword ptr ds : [esi + 0x04], 0xC1A00000
		jne HUDSizeCodeCaveFullscreenCheck13
		//cmp dword ptr ds : [esi + 0x10], 0x44819555
		//jne HUDSizeCodeCaveFullscreenCheck13
		cmp dword ptr ds : [esi + 0x14], 0xC1A00000
		jne HUDSizeCodeCaveFullscreenCheck13
		//cmp dword ptr ds : [esi + 0x20], 0x44819555
		//jne HUDSizeCodeCaveFullscreenCheck13
		cmp dword ptr ds : [esi + 0x24], 0x43FA0000
		jne HUDSizeCodeCaveFullscreenCheck13
		//cmp dword ptr ds : [esi + 0x30], 0xC3235556
		//jne HUDSizeCodeCaveFullscreenCheck13
		cmp dword ptr ds : [esi + 0x34], 0x43FA0000
		jne HUDSizeCodeCaveFullscreenCheck13
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck13:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC1C2AAB0
		//jne HUDSizeCodeCaveFullscreenCheck14
		cmp dword ptr ds : [esi + 0x04], 0xC1A00000
		jne HUDSizeCodeCaveFullscreenCheck14
		//cmp dword ptr ds : [esi + 0x10], 0x445AEAAA
		//jne HUDSizeCodeCaveFullscreenCheck14
		cmp dword ptr ds : [esi + 0x14], 0xC1A00000
		jne HUDSizeCodeCaveFullscreenCheck14
		//cmp dword ptr ds : [esi + 0x20], 0x445AEAAA
		//jne HUDSizeCodeCaveFullscreenCheck14
		cmp dword ptr ds : [esi + 0x24], 0x43F70000
		jne HUDSizeCodeCaveFullscreenCheck14
		//cmp dword ptr ds : [esi + 0x30], 0xC1C2AAB0
		//jne HUDSizeCodeCaveFullscreenCheck14
		cmp dword ptr ds : [esi + 0x34], 0x43F70000
		jne HUDSizeCodeCaveFullscreenCheck14
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck14:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC1AEAAB0
		//jne HUDSizeCodeCaveFullscreenCheck15
		cmp dword ptr ds : [esi + 0x04], 0xC23A8000
		jne HUDSizeCodeCaveFullscreenCheck15
		//cmp dword ptr ds : [esi + 0x10], 0x445ECAAA
		//jne HUDSizeCodeCaveFullscreenCheck15
		cmp dword ptr ds : [esi + 0x14], 0xC23A8000
		jne HUDSizeCodeCaveFullscreenCheck15
		//cmp dword ptr ds : [esi + 0x20], 0x445ECAAA
		//jne HUDSizeCodeCaveFullscreenCheck15
		cmp dword ptr ds : [esi + 0x24], 0x4403A800
		jne HUDSizeCodeCaveFullscreenCheck15
		//cmp dword ptr ds : [esi + 0x30], 0xC1AEAAB0
		//jne HUDSizeCodeCaveFullscreenCheck15
		cmp dword ptr ds : [esi + 0x34], 0x4403A800
		jne HUDSizeCodeCaveFullscreenCheck15
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck15:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC3305556
		//jne HUDSizeCodeCaveFullscreenCheck16
		cmp dword ptr ds : [esi + 0x04], 0xC2AA0000
		jne HUDSizeCodeCaveFullscreenCheck16
		//cmp dword ptr ds : [esi + 0x10], 0x447FEAAA
		//jne HUDSizeCodeCaveFullscreenCheck16
		cmp dword ptr ds : [esi + 0x14], 0xC2AA0000
		jne HUDSizeCodeCaveFullscreenCheck16
		//cmp dword ptr ds : [esi + 0x20], 0x447FEAAA
		//jne HUDSizeCodeCaveFullscreenCheck16
		cmp dword ptr ds : [esi + 0x24], 0x440D4000
		jne HUDSizeCodeCaveFullscreenCheck16
		//cmp dword ptr ds : [esi + 0x30], 0xC3305556
		//jne HUDSizeCodeCaveFullscreenCheck16
		cmp dword ptr ds : [esi + 0x34], 0x440D4000
		jne HUDSizeCodeCaveFullscreenCheck16
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck16:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC2BAAAAC
		//jne HUDSizeCodeCaveFullscreenCheck17
		cmp dword ptr ds : [esi + 0x04], 0xC1580000
		jne HUDSizeCodeCaveFullscreenCheck17
		//cmp dword ptr ds : [esi + 0x10], 0x446CAAAA
		//jne HUDSizeCodeCaveFullscreenCheck17
		cmp dword ptr ds : [esi + 0x14], 0xC1580000
		jne HUDSizeCodeCaveFullscreenCheck17
		//cmp dword ptr ds : [esi + 0x20], 0x446CAAAA
		//jne HUDSizeCodeCaveFullscreenCheck17
		cmp dword ptr ds : [esi + 0x24], 0x43F6C000
		jne HUDSizeCodeCaveFullscreenCheck17
		//cmp dword ptr ds : [esi + 0x30], 0xC2BAAAAC
		//jne HUDSizeCodeCaveFullscreenCheck17
		cmp dword ptr ds : [esi + 0x34], 0x43F6C000
		jne HUDSizeCodeCaveFullscreenCheck17
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck17:
		// Checks for Black Overlay
		//cmp dword ptr ds : [esi], 0xC1E2AAB0
		//jne HUDSizeCodeCaveFullscreenCheck18
		cmp dword ptr ds : [esi + 0x04], 0xC2020000
		jne HUDSizeCodeCaveFullscreenCheck18
		//cmp dword ptr ds : [esi + 0x10], 0x445C6AAA
		//jne HUDSizeCodeCaveFullscreenCheck18
		cmp dword ptr ds : [esi + 0x14], 0xC2020000
		jne HUDSizeCodeCaveFullscreenCheck18
		//cmp dword ptr ds : [esi + 0x20], 0x445C6AAA
		//jne HUDSizeCodeCaveFullscreenCheck18
		cmp dword ptr ds : [esi + 0x24], 0x44002000
		jne HUDSizeCodeCaveFullscreenCheck18
		//cmp dword ptr ds : [esi + 0x30], 0xC1E2AAB0
		//jne HUDSizeCodeCaveFullscreenCheck18
		cmp dword ptr ds : [esi + 0x34], 0x44002000
		jne HUDSizeCodeCaveFullscreenCheck18
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck18:
		// Checks for Rap Sheet Background
		//cmp dword ptr ds : [esi], 0xC1BAAAB0
		//jne HUDSizeCodeCaveFullscreenCheck19
		cmp dword ptr ds : [esi + 0x04], 0xC1880000
		jne HUDSizeCodeCaveFullscreenCheck19
		//cmp dword ptr ds : [esi + 0x10], 0x445B2AAA
		//jne HUDSizeCodeCaveFullscreenCheck19
		cmp dword ptr ds : [esi + 0x14], 0xC1880000
		jne HUDSizeCodeCaveFullscreenCheck19
		//cmp dword ptr ds : [esi + 0x20], 0x445B2AAA
		//jne HUDSizeCodeCaveFullscreenCheck19
		cmp dword ptr ds : [esi + 0x24], 0x43F88000
		jne HUDSizeCodeCaveFullscreenCheck19
		//cmp dword ptr ds : [esi + 0x30], 0xC1BAAAB0
		//jne HUDSizeCodeCaveFullscreenCheck19
		cmp dword ptr ds : [esi + 0x34], 0x43F88000
		jne HUDSizeCodeCaveFullscreenCheck19
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck19:
		// Checks for Rap Sheet Background
		//cmp dword ptr ds : [esi], 0xC1EAAAB0
		//jne HUDSizeCodeCaveFullscreenCheck20
		cmp dword ptr ds : [esi + 0x04], 0xC1880000
		jne HUDSizeCodeCaveFullscreenCheck20
		//cmp dword ptr ds : [esi + 0x10], 0x4459AAAA
		//jne HUDSizeCodeCaveFullscreenCheck20
		cmp dword ptr ds : [esi + 0x14], 0xC1880000
		jne HUDSizeCodeCaveFullscreenCheck20
		//cmp dword ptr ds : [esi + 0x20], 0x4459AAAA
		//jne HUDSizeCodeCaveFullscreenCheck20
		cmp dword ptr ds : [esi + 0x24], 0x43F88000
		jne HUDSizeCodeCaveFullscreenCheck20
		//cmp dword ptr ds : [esi + 0x30], 0xC1EAAAB0
		//jne HUDSizeCodeCaveFullscreenCheck20
		cmp dword ptr ds : [esi + 0x34], 0x43F88000
		jne HUDSizeCodeCaveFullscreenCheck20
		test eax, eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveFullscreenCheck20:
		// Checks for Vignette Overlay
		//cmp dword ptr ds : [esi], 0xC1BAAAB0
		//jne HUDSizeCodeCaveNotFullscreen
		cmp dword ptr ds : [esi + 0x04], 0xC1200000
		jne HUDSizeCodeCaveNotFullscreen
		//cmp dword ptr ds : [esi + 0x10], 0x445B2AAA
		//jne HUDSizeCodeCaveNotFullscreen
		cmp dword ptr ds : [esi + 0x14], 0xC1200000
		jne HUDSizeCodeCaveNotFullscreen
		//cmp dword ptr ds : [esi + 0x20], 0x445B2AAA
		//jne HUDSizeCodeCaveNotFullscreen
		cmp dword ptr ds : [esi + 0x24], 0x43F50000
		jne HUDSizeCodeCaveNotFullscreen
		//cmp dword ptr ds : [esi + 0x30], 0xC1BAAAB0
		//jne HUDSizeCodeCaveNotFullscreen
		cmp dword ptr ds : [esi + 0x34], 0x43F50000
		jne	HUDSizeCodeCaveNotFullscreen
		test eax,eax
		jmp HUDSizeCodeCaveExit2

	HUDSizeCodeCaveNotFullscreen:
		push edi
		mov [esp + 0x1F], bl
		mov [esp + 0x1E], bl
		je HUDSizeCodeCaveScaleConditional1
		test ecx, ecx
		je HUDSizeCodeCaveScaleConditional2
		mov eax, dword ptr ds : [ecx + 0x24]
		cmp eax, 0x40CDC515
		je HUDSizeCodeCaveScaleConditional3
		cmp eax, 0x1149C7DA
		jne HUDSizeCodeCaveScaleConditional2

	HUDSizeCodeCaveScaleConditional3:
		mov bl, 0x01
		mov [esp + 0x1F], bl

	HUDSizeCodeCaveScaleConditional2:
		mov al, [esi + 0x91]
		cmp al, 0x72
		je HUDSizeCodeCaveScaleConditional4
		cmp al, 0x73
		jne HUDSizeCodeCaveScaleConditional1

	HUDSizeCodeCaveScaleConditional4:
		mov byte ptr [esp + 0x1E], 0x01

	HUDSizeCodeCaveScaleConditional1:
		fld dword ptr ds : [esi]
		mov al, [esi + 0x90]
		and al, 0x02
		fmul dword ptr ds : [0x8AF9A4] // Width 1
		fmul dword ptr ds : [HUDSize] // Size
		fadd dword ptr ds : [HUDPos] // Pos
		fsub dword ptr ds : [0x89096C]
		fstp dword ptr ds : [esp + 0x20]
		fld dword ptr ds : [esi + 0x04]
		fmul dword ptr ds : [0x8AF9A0] // Height 1
		fmul dword ptr ds : [HUDSize] // Size
		fadd dword ptr ds : [HUDPos] // Pos
		fsub dword ptr ds : [0x89096C]
		fchs
		fstp dword ptr ds : [esp + 0x24]
		je HUDSizeCodeCaveScaleConditional5
		mov edx, dword ptr ds : [esi + 0x08]
		mov dword ptr ds : [esp + 0x28] , edx
		jmp HUDSizeCodeCaveScaleConditional6

	HUDSizeCodeCaveScaleConditional5:
		mov dword ptr ds : [esp + 0x28] , 0x3F800000

	HUDSizeCodeCaveScaleConditional6:
		movzx edi, byte ptr [esi + 0x81]
		fld dword ptr ds : [esi + 0x10]
		fmul dword ptr ds : [0x8AF9A4] // Width 2
		fmul dword ptr ds : [HUDSize] // Size
		fadd dword ptr ds : [HUDPos] // Pos
		xor edx, edx
		mov dh, [esi + 0x83]
		fsub dword ptr ds : [0x89096C]
		fstp dword ptr ds : [esp + 0x40]
		fld dword ptr ds : [esi + 0x14]
		fmul dword ptr ds : [0x8AF9A0] // Height 2
		fmul dword ptr ds : [HUDSize] // Size
		fadd dword ptr ds : [HUDPos] // Pos
		mov dl, [esi + 0x80]
		fsub dword ptr ds : [0x89096C]
		fchs
		fstp dword ptr ds : [esp + 0x44]
		shl edx, 0x08
		or edx, edi
		movzx edi, byte ptr[esi + 0x82]
		shl edx, 0x08
		or edx, edi
		test al, al
		mov dword ptr ds : [esp + 0x2C], edx
		mov edx, dword ptr ds : [esi + 0x40]
		mov dword ptr ds : [esp + 0x30], edx
		mov edx, dword ptr ds : [esi + 0x44]
		mov dword ptr ds : [esp + 0x34], edx
		mov edx, dword ptr ds : [esi + 0x60]
		mov dword ptr ds : [esp + 0x38], edx
		mov edx, dword ptr ds : [esi + 0x64]
		mov dword ptr ds : [esp + 0x3C], edx
		je HUDSizeCodeCaveScaleConditional7
		mov edx, dword ptr ds : [esi + 0x18]
		mov dword ptr ds : [esp + 0x48], edx
		jmp HUDSizeCodeCaveScaleConditional8

	HUDSizeCodeCaveScaleConditional7:
		mov dword ptr ds : [esp + 0x48] , 0x3F800000

	HUDSizeCodeCaveScaleConditional8:
		movzx edi, byte ptr [esi + 0x85]
		fld dword ptr ds : [esi + 0x20]
		fmul dword ptr ds : [0x8AF9A4] // Width 3
		fmul dword ptr ds : [HUDSize] // Size
		fadd dword ptr ds : [HUDPos] // Pos
		xor edx, edx
		mov dh, [esi + 0x87]
		fsub dword ptr ds : [0x89096C]
		fstp dword ptr ds : [esp + 0x60]
		fld dword ptr ds : [esi + 0x24]
		fmul dword ptr ds : [0x8AF9A0] // Height 3
		fmul dword ptr ds : [HUDSize] // Size
		fadd dword ptr ds : [HUDPos] // Pos
		mov dl, [esi + 0x84]
		fsub dword ptr ds : [0x89096C]
		fchs
		fstp dword ptr ds : [esp + 0x64]
		shl edx, 0x08
		or edx, edi
		movzx edi, byte ptr ds : [esi + 0x86]
		shl edx, 0x08
		or edx, edi
		test al, al
		mov dword ptr ds : [esp + 0x4C], edx
		mov edx, dword ptr ds : [esi + 0x48]
		mov dword ptr ds : [esp + 0x50], edx
		mov edx, dword ptr ds : [esi + 0x4C]
		mov dword ptr ds : [esp + 0x54], edx
		mov edx, dword ptr ds : [esi + 0x68]
		mov dword ptr ds : [esp + 0x58], edx
		mov edx, dword ptr ds : [esi + 0x6C]
		mov dword ptr ds : [esp + 0x5C], edx
		je HUDSizeCodeCaveScaleConditional9
		mov edx, dword ptr ds : [esi + 0x28]
		mov dword ptr ds : [esp + 0x68], edx
		jmp HUDSizeCodeCaveScaleConditional10

	HUDSizeCodeCaveScaleConditional9:
		mov dword ptr ds : [esp + 0x68] , 0x3F800000

	HUDSizeCodeCaveScaleConditional10:
		movzx edi, byte ptr [esi + 0x89]
		fld dword ptr ds : [esi + 0x30]
		fmul dword ptr ds : [0x8AF9A4] // Width 4
		fmul dword ptr ds : [HUDSize] // Size
		fadd dword ptr ds : [HUDPos] // Pos
		xor edx, edx
		mov dh, [esi + 0x8B]
		fsub dword ptr ds : [0x89096C]
		fstp dword ptr ds : [esp + 0x80]
		fld dword ptr ds : [esi + 0x34]
		fmul dword ptr ds : [0x8AF9A0] // Height 4
		fmul dword ptr ds : [HUDSize] // Size
		fadd dword ptr ds : [HUDPos] // Pos
		jmp HUDSizeCodeCaveExit3
	}
}

void __declspec(naked) FMVSizeCodeCave()
{
	__asm {
		fld dword ptr ds : [esp]
		fdiv dword ptr ds : [HUDSize] // Height 1
		fmul dword ptr ds : [FMVScale] // Scale
		fstp dword ptr ds : [esp]
		fld dword ptr ds : [esp + 0x04]
		fdiv dword ptr ds : [HUDSize] // Width 1
		fmul dword ptr ds : [FMVScale] // Scale
		fstp dword ptr ds : [esp + 0x04]
		fld dword ptr ds : [esp + 0x08]
		fdiv dword ptr ds : [HUDSize] // Width 2
		fmul dword ptr ds : [FMVScale] // Scale
		fstp dword ptr ds : [esp + 0x08]
		fld dword ptr ds : [esp + 0x0C]
		fdiv dword ptr ds : [HUDSize] // Height 2
		fmul dword ptr ds : [FMVScale] // Scale
		fstp dword ptr ds : [esp + 0x0C]
		call sub_591460
		jmp FMVSizeCodeCaveExit
	}
}


void Init()
{
	// Read values from .ini
	CIniReader iniReader("NFSMWHUDResizer.ini");

	// General
	HUDScale = iniReader.ReadFloat("GENERAL", "HUDScale", 0.92f);
	FMVScale = iniReader.ReadFloat("GENERAL", "FMVScale", 1.0f);

	{
		injector::MakeJMP(0x6D1260, HUDSizeCodeCave, true);
		injector::MakeJMP(0x59A03F, FMVSizeCodeCave, true);
	}
}
	

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x7C4040) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
			Init();

		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use v1.3 English speed.exe (5,75 MB (6.029.312 bytes)).", "NFSMW HUD Resizer", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;

}