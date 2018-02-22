#include "PCINPUT.H"
#include "DIRECTX.H"
#include "ERROR.H"

long input;
long inputBusy;
BYTE byte_86BB8C[256];
BYTE unk_86BC8C[256];
WORD word_86B9B0[32];

DWORD dword_86BA48;
BOOL __stdcall sub_401FE6(LPCDIDEVICEINSTANCEA a1, LPVOID a2)
{
	return ptr_ctx->dinput->lpVtbl->CreateDeviceEx(
		ptr_ctx->dinput,
		&a1->guidInstance,
		&IID_IDirectInputDevice2A,
		&ptr_ctx->dinput_other,
		0) < 0;
}


BOOL __stdcall sub_402E3C(LPCDIDEVICEOBJECTINSTANCEA a1, LPVOID a2)
{
	int v2; // ecx@1
	DIPROPHEADER v4; // [sp+0h] [bp-18h]@1
	int v5; // [sp+10h] [bp-8h]@1
	int v6; // [sp+14h] [bp-4h]@1

	v4.dwSize = 24;
	v4.dwHeaderSize = 16;
	v2 = a1->dwOfs;
	v4.dwHow = 1;
	v4.dwObj = v2;
	v5 = -1000;
	v6 = 1000;
	return ptr_ctx->dinput_other->lpVtbl->SetProperty(
		ptr_ctx->dinput_other,
		4,
		&v4) >= 0;
}

int sub_402CD4(HWND hWnd, HINSTANCE hInstance)
{
	int v2; // eax@1
	int v3; // eax@2
	int v4; // eax@4
	int v5; // eax@5
	int v6; // eax@7
	int v7; // eax@7
	int v8; // eax@7
	int v9; // eax@7
	LPDIRECTINPUTDEVICEA result; // eax@7
	int v11; // eax@8
	int v12; // eax@8
	int v13; // eax@8
	LPDIRECTINPUTDEVICEA v14; // [sp+64h] [bp-30h]@4
	DIDEVCAPS v15; // [sp+68h] [bp-2Ch]@8
	LPDIRECTINPUTA hinst;
	v2 = DirectInputCreateA(hInstance, 0x700u, &hinst, 0);
	sub_40179E(v2);
	hinst->lpVtbl->QueryInterface(hinst, &IID_IDirectInput2A, &ptr_ctx->dinput);
	if (hinst)
	{
		v3 = hinst->lpVtbl->Release(hinst);
		Log(4, "Released %s @ %x - RefCnt = %d", "DirectInput", hinst, v3);
		hinst = 0;
	}
	else
	{
		Log(1, "%s Attempt To Release NULL Ptr", "DirectInput");
	}
	v4 = ptr_ctx->dinput->lpVtbl->CreateDevice(
		ptr_ctx->dinput,
		&GUID_SysKeyboard,
		&v14,
		0);
	sub_40179E(v4);
	v14->lpVtbl->QueryInterface(v14, &IID_IDirectInputDevice2A, &ptr_ctx->dinput_keyboard);
	if (v14)
	{
		v5 = v14->lpVtbl->Release(v14);
		Log(4, "Released %s @ %x - RefCnt = %d", "Keyboard", v14, v5);
		v14 = 0;
	}
	else
	{
		Log(1, "%s Attempt To Release NULL Ptr", "Keyboard");
	}
	v6 = ptr_ctx->dinput_keyboard->lpVtbl->SetCooperativeLevel(
		ptr_ctx->dinput_keyboard,
		hWnd,
		10);
	sub_40211C(v6);
	v7 = ptr_ctx->dinput_keyboard->lpVtbl->SetDataFormat(
		ptr_ctx->dinput_keyboard,
		&c_dfDIKeyboard);
	sub_40211C(v7);
	v8 = ptr_ctx->dinput_keyboard->lpVtbl->Acquire(ptr_ctx->dinput_keyboard);
	sub_40211C(v8);
	memset(byte_86BB8C, 0, 0x100u);
	memset(&unk_86BC8C[0], 0, 0x100u);
	dword_86BA48 = 0;
	memset(&word_86B9B0[0], 0, 0x40u);
	v9 = ptr_ctx->dinput->lpVtbl->EnumDevices(
		ptr_ctx->dinput,
		4,
		sub_401FE6,
		0,
		1);
	sub_40211C(v9);
	result = ptr_ctx->dinput_other;
	if (result)
	{
		v11 = result->lpVtbl->SetDataFormat(result, &c_dfDIJoystick);
		sub_40211C(v11);
		v12 = ptr_ctx->dinput_other->lpVtbl->SetCooperativeLevel(
			ptr_ctx->dinput_other,
			hWnd,
			5);
		sub_40211C(v12);
		v15.dwSize = 44;
		ptr_ctx->dinput_other->lpVtbl->GetCapabilities(ptr_ctx->dinput_other, &v15);
		ptr_ctx->dinput_other->lpVtbl->EnumObjects(
			ptr_ctx->dinput_other,
			sub_402E3C,
			hWnd,
			3);
		v13 = ptr_ctx->dinput_other->lpVtbl->Acquire(ptr_ctx->dinput_other);
		result = sub_40211C(v13);
	}
	return result;

	S_Warn("[sub_402CD4] - Unimplemented!\n");
	return 1;
}
