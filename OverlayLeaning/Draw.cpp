#include "Draw.h"



	



int Draw::init(HWND hWnd)
{
	D3DPRESENT_PARAMETERS params;

		if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &object)))
		{
			exit(1);
		}

		ZeroMemory(&params, sizeof(params));
		

		params.BackBufferWidth = width;
		params.BackBufferHeight = height;
		params.Windowed = true;
		params.hDeviceWindow = hWnd;
		params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		params.BackBufferFormat = D3DFMT_A8R8G8B8;
		params.EnableAutoDepthStencil = TRUE;
		params.AutoDepthStencilFormat = D3DFMT_D16; 

			object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, 0, &device);
		D3DXCreateFont(device, 50, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Comic Sans", &font);


		
	return 0;

	


}

int Draw::render()
{
	if(device == nullptr)
	{
		return 1;
	}
	

	device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
	device->BeginScene();
	if (TargetHWND == GetForegroundWindow()) {

		drawText((char*)"U got Hacked broooooo", width / 10, height / 10, 255, 171, 0, 182);

		device->EndScene();
		device->PresentEx(0, 0, 0, 0, 0);
		
	}
		

}

Draw::Draw()
{
}


Draw::Draw(HWND overlayHWND, HWND targetHWND, int width, int height)
{

	

		this->width = width;
		this->height = height;
		this->TargetHWND = targetHWND;
		init(overlayHWND);
	

}







